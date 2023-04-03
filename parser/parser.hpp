#include <tuple>
#include <string>
#include <vector>
#include <fstream>
#include <assert.h>
#include <algorithm>

#include "../constants/constants.hpp"
#include "../itemize/item.hpp"
#include "../itemize/itemize.hpp"

/* 
  Get the command, e.g. \item
*/
std::string get_command(std::string i) {
    std::string tmp = i;
    tmp.erase(std::remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());

    if (tmp == "%pragmaansDefinition") {
      return "pragma ans Definition";
    }
    else {
      tmp = i.substr(0, i.find(" "));  // Get the first word in sentence
      tmp.erase(std::remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());  // Remove all whitespace
      tmp.erase(tmp.begin());  // Remove first char "\"
    }

    return tmp;
}

/*
  Get the text after the command 
*/
std::string get_text(std::string line) {
  size_t position;  // position of the command in string

  position = line.find(constants::item_cmd);  // Find when whitespace ends
  line = line.substr(position);  // Remove whitespace before \item
  line.erase(0, 5);  // Remove item string

  return line;
}


std::tuple<int, Item>  parse_definition(std::vector<std::string> *vtr, int start_idx) {
  int cur_idx;  // current index
  std::string item_text;  // text of the itemObj
  std::string line;  // text of the line
  std::string cmd;  // command of the line

  line = (*vtr)[start_idx];
  line = get_text(line);
  item_text += line;

  // FIXME: remove : and space before the definition start
  int separator_idx = line.find(":");
  std::string subject;
  std::string definition;
  
  for (cur_idx = start_idx+1; cur_idx < (*vtr).size(); cur_idx++) {
    
    if (separator_idx < line.length()) {
      subject = line.substr(0, separator_idx);
      definition = line.substr(separator_idx, line.length());
    }

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
    
  // Create the item object
  ans::Definition def = ans::Definition(subject, definition);
  Item itemObj(item_text, def);

  return std::make_tuple(cur_idx, itemObj);
}

std::tuple<int, Item>  parse_no_answer(std::vector<std::string> *vtr, int start_idx) {
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
std::tuple<int, Item>  add_items(std::vector<std::string> *vtr, int start_idx) {
  int cur_idx;  // current index
  Item itemObj;  // a item object in itemize

  if (start_idx > 0 && constants::definition_pragma.compare(get_command((*vtr)[start_idx-1])) == 0) {
    std::tie(cur_idx, itemObj) = parse_definition(vtr, start_idx);
  }
  else {
    std::tie(cur_idx, itemObj) = parse_no_answer(vtr, start_idx);
  }
    
  return std::make_tuple(cur_idx, itemObj);
}


std::tuple<int, Itemize>  add_itemizes(std::vector<std::string> *vtr, int start_idx) {
    Itemize itemizeObj;  // New itemize object
    Itemize subItemizeObj;  // if there is itemize within the current
    Item itemObj;  // a item object in itemize
    std::string cmd;  // Command of the line
    int cur_idx; // current index

    for (cur_idx = start_idx+1; cur_idx < (*vtr).size(); cur_idx++) {
      cmd = get_command((*vtr)[cur_idx]);
      
      // Add the new item object in itemize object
      if ( cmd.compare(constants::item_cmd) == 0 ) {
        std::tie(cur_idx, itemObj) =  add_items(vtr, cur_idx);
        cur_idx--; // TODO: I need it but I dont know why 
        itemizeObj.add(itemObj);
      }
      // Add the new itemize object in current itemize object
      else if ( cmd.compare(constants::begin_cmd) == 0 ) {
        std::tie(cur_idx, subItemizeObj) =  add_itemizes(vtr, cur_idx);
        itemizeObj.add(subItemizeObj);
      }
      else if ( cmd.compare(constants::end_cmd) == 0 ) {
        return std::make_tuple(cur_idx, itemizeObj);
      }
    }
    return std::make_tuple(cur_idx, itemizeObj);
}


std::vector<std::string> add_line(std::string line) {
  std::string tmp;
  std::vector<std::string> vtr_to_add = {}; // Will be added to all_itemize
  static std::vector<std::string> vtr;
  static int count = 0;

  // Get the command of the line
	tmp = line;
  tmp.erase(tmp.begin());

	if ( tmp.compare(constants::end_cmd) == 0 ) { 
    count--; 
    assert (count >= 0);

    // Add \end{itemize} when the root itemize has ended
    if ( count == 0 ) {
      vtr.push_back("\\" + constants::end_cmd);
      vtr_to_add = vtr;
      //(*all_itemize).push_back(vtr);
      vtr = {};
    }
  }
  
  if ( count > 0 ) { vtr.push_back(line); }
  
  if ( tmp.compare(constants::begin_cmd) == 0 ) { 
    // New root \begin{itemize}
    if ( count == 0 ) {
      vtr.push_back("\\" + constants::begin_cmd);
    }

    count++;
  }

  return vtr_to_add;
}


void read_text(std::string text, std::vector<std::vector<std::string>> *all_itemize) {
  std::string line;
  std::vector<std::string> vtr_to_add;

  int separator = text.find("\n");

  // FIXME: it should be possible to not have \n at the end of text
  while ( separator < text.length() )
  {
    line = text.substr(0, separator);
    text = text.substr(separator+1, text.length()); // +1 to remove \n
    separator = text.find("\n");

    // skip if there is an empty line
    if ( line.compare("") == 0 ) { continue; }

    vtr_to_add = add_line(line);
    if ( vtr_to_add.size() > 0 ) {
      (*all_itemize).push_back(vtr_to_add);
    }
  }
}


/*
  Get all lines within a root itemize object. 

  Example:
  \begin{itemize}
    \item blabla
    \begin{itemize}
      \item blabla
    \end{itemize}
    \item blabla
  \end{itemize}

  \begin{itemize}
    \item blabla2
  \end{itemize}

  This will give two elements in all_itemize.
  The second element will have just one element in it, i.e. \item blabla2
*/
void read(std::ifstream *myfile, std::vector<std::vector<std::string>> *all_itemize) {
  std::string line;
  std::vector<std::string> vtr_to_add;

  while ( std::getline ((*myfile),line) )
  {
    // skip if there is an empty line
    if ( line.compare("") == 0 ) { continue; }

    vtr_to_add = add_line(line);
    if ( vtr_to_add.size() > 0 ) {
      (*all_itemize).push_back(vtr_to_add);
    }
  }
}


/*
  Convert all_itemize into an vector of itemize objects which has a hierarchy of 
  items and itemize objects within it.
*/
void get_data(std::vector<std::vector<std::string>> *all_itemize, std::vector<Itemize> *data) {
  Itemize itemizeObj;
  int ignore_idx;

  for (std::vector<std::string> i : (*all_itemize)) {
    // If there is an empty element skip it
    if (i.empty()) { continue; }
    // create the itemize object 

    std::tie(ignore_idx, itemizeObj) =  add_itemizes(&i, 0);
    // Add the new itemize object to data
    data->push_back(itemizeObj);
  }
}