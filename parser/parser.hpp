#include <tuple>
#include <string>
#include <vector>
#include <fstream>
#include <assert.h>
#include <algorithm>

#include "../constants/constants.hpp"
#include "../itemize/item.hpp"
#include "../itemize/itemize.hpp"

std::string get_command(std::string i) {
    std::string tmp;
  
    tmp = i.substr(0, i.find(" "));  // Get the first word in sentence
    tmp.erase(std::remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());  // Remove all whitespace
    tmp.erase(tmp.begin());  // Remove first char "\"

    return tmp;
}

std::string get_text(std::string line) {
  size_t position;  // position of the command in string

  position = line.find(constants::item_cmd);  // Find when whitespace ends
  line = line.substr(position);  // Remove whitespace before \item
  line.erase(0, 5);  // Remove item string

  return line;
}

std::tuple<int, Item> item(std::vector<std::string> *vtr, int start_idx) {
  int cur_idx;  // current index
  std::string item_text;  // text of the itemObj
  std::string line;  // text of the line
  std::string cmd;  // command of the line

  line = (*vtr)[start_idx];
  line = get_text(line);
  item_text += line;

  for (cur_idx = start_idx+1; cur_idx < (*vtr).size(); cur_idx++) {
    line = (*vtr)[cur_idx];
    cmd = get_command(line);

    // Add text until command is found 
    // FIXME: this is line sensetive \item should be able to be identify on the same line
    if (cmd.compare(constants::item_cmd) == 0) { break; }
    else if (cmd.compare(constants::begin_cmd) == 0) { break; }
    else if (cmd.compare(constants::end_cmd) == 0) { break; }

    // No need to remove \item it will only be a \t os something
    item_text += " " + line;
  }
    
  // Type
  Item itemObj(item_text);

  return std::make_tuple(cur_idx, itemObj);
}

std::tuple<int, Itemize> begin_itemize(std::vector<std::string> *vtr, int start_idx) {
    Itemize itemizeObj;  // New itemize object
    Itemize subItemizeObj;  // if there is itemize within the current
    Item itemObj;  // a item object in itemize
    std::string cmd;  // Command of the line
    int cur_idx; // current index

    for (cur_idx = start_idx+1; cur_idx < (*vtr).size(); cur_idx++) {
      cmd = get_command((*vtr)[cur_idx]);
      
      // Add the new item object in itemize object
      if ( cmd.compare(constants::item_cmd) == 0 ) {
        std::tie(cur_idx, itemObj) = item(vtr, cur_idx);
        cur_idx--;
        itemizeObj.add(itemObj);
      }
      // Add the new itemize object in current itemize object
      else if ( cmd.compare(constants::begin_cmd) == 0 ) {
        std::tie(cur_idx, subItemizeObj) = begin_itemize(vtr, cur_idx);
        itemizeObj.add(subItemizeObj);
      }
      else if ( cmd.compare(constants::end_cmd) == 0 ) {
        return std::make_tuple(cur_idx, itemizeObj);
      }
    }
    return std::make_tuple(cur_idx, itemizeObj);
}

void read(std::ifstream *myfile, std::vector<std::vector<std::string>> *all_itemize) {
  std::vector<std::string> vtr = {};
  std::string tmp;
  std::string line;
  int count = 0;

  while ( std::getline ((*myfile),line) )
  {
    if ( line.compare("") == 0 ) { continue; }  // Empty line
	  tmp = line;
    tmp.erase(tmp.begin());  // Get command

	  if ( tmp.compare(constants::end_cmd) == 0 ) { 
      count--; 
      assert (count >= 0);
      if ( count == 0 ) {
        vtr.push_back("\\" + constants::end_cmd);
        (*all_itemize).push_back(vtr);
        vtr = {};
      }
    }
    if ( count > 0 ) { vtr.push_back(line); }
    if ( tmp.compare(constants::begin_cmd) == 0 ) { 
      if ( count == 0 ) {
        vtr.push_back("\\" + constants::begin_cmd);
      }
      count++;
    }
  }
}

void get_data(std::vector<std::vector<std::string>> *all_itemize, std::vector<Itemize> *data) {
  Itemize itemizeObj;
  int bla;
  for (std::vector<std::string> i : (*all_itemize)) {
    if (i.empty()) { continue; }
    std::tie(bla, itemizeObj) = begin_itemize(&i, 0);
    data->push_back(itemizeObj);
  }
}