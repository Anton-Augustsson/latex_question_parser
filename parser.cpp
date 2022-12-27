// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <tuple>
#include <variant>
#include <cctype>
#include <algorithm>
#include <assert.h>
#include <stdio.h>

const std::string begin_cmd =  "begin{itemize}";
const std::string end_cmd =  "end{itemize}";
const std::string item_cmd =  "item";

class Item {
  private:
    std::string text;

  public:
    Item(std::string item_text) {
      text = item_text;
    }

    Item() {
      text = "";
    }

    void print() {
      std::cout << text << '\n';
    }
};

// https://gieseanw.wordpress.com/2017/05/03/a-true-heterogeneous-container-in-c/
struct PrintVisitor
{
  template <class T>
  void operator()(T&& _in){ _in.print(); }
};

class Itemize {
  private:
    std::vector<std::variant<Itemize, Item>> items_list;

  public:
    void print() {
      
      std::cout << "Begin Itemize:" << '\n';
      for(auto& i : items_list) {
        std::visit(PrintVisitor{}, i);
      }
      std::cout << "End Itemize:" << '\n';
    }

    void add(std::variant<Itemize, Item> obj) {
      items_list.push_back(obj);
    }
};

std::string get_command(std::string i) {
  std::string tmp;
  
	tmp = i.substr(0, i.find(" "));  // Get the first word in sentence
  tmp.erase(std::remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());  // Remove all whitespace
  tmp.erase(tmp.begin());  // Remove first char "\"

  return tmp;
}

std::string get_text(std::string line) {
  size_t position;  // position of the command in string

  position = line.find(item_cmd);  // Find when whitespace ends
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
    if (cmd.compare(item_cmd) == 0) { break; }
    else if (cmd.compare(begin_cmd) == 0) { break; }
    else if (cmd.compare(end_cmd) == 0) { break; }

    // No need to remove \item it will only be a \t os something
    item_text += " " + line;
  }
    
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
      if ( cmd.compare(item_cmd) == 0 ) {
        std::tie(cur_idx, itemObj) = item(vtr, cur_idx);
        cur_idx--;
        itemizeObj.add(itemObj);
      }
      // Add the new itemize object in current itemize object
      else if ( cmd.compare(begin_cmd) == 0 ) {
        std::tie(cur_idx, subItemizeObj) = begin_itemize(vtr, cur_idx);
        itemizeObj.add(subItemizeObj);
      }
      else if ( cmd.compare(end_cmd) == 0 ) {
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

	  if ( tmp.compare(end_cmd) == 0 ) { 
      count--; 
      assert (count >= 0);
      if ( count == 0 ) {
        vtr.push_back("\\" + end_cmd);
        (*all_itemize).push_back(vtr);
        vtr = {};
      }
    }
    if ( count > 0 ) { vtr.push_back(line); }
    if ( tmp.compare(begin_cmd) == 0 ) { 
      if ( count == 0 ) {
        vtr.push_back("\\" + begin_cmd);
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
    (*data).push_back(itemizeObj);
  }
}

void tui(std::vector<Itemize> *data) {
  char ans;
  char all = 'a';
  char first = 'f';
  char next = 'n';
  char quit = 'q';

  while (ans != all && ans != first && ans != quit) {
    std::cout << "Show all[a]" << '\n';
    std::cout << "Show first[f]" << '\n';
    std::cout << "";
    std::cin >> ans;
  }

  if (ans == all) {
    for (Itemize i: (*data)) {
      std::cout << "New Itemize" << '\n';
      i.print();
    }
    return;
  }
  else if (ans == first) {
    for (int i = 0; i < (*data).size(); i++) {
      (*data)[i].print();
      while (ans != next && ans != quit) {
        std::cout << "Show next[n]" << '\n';;
        std::cout << "Quit[q]" << '\n';;
        std::cin >> ans;
      }
      if (ans == quit) {
        return;
      }
    }
  }
  else {
    return;
  }
}

int main () {
  std::vector<std::vector<std::string>> all_itemize = {};
  std::vector<Itemize> data = {};
  std::ifstream myfile ("test.tex");

  if (myfile.is_open())
  {
    read(&myfile, &all_itemize);
    myfile.close();
  }
  else std::cout << "Unable to open file"; 

  get_data(&all_itemize, &data);
  tui(&data);

  return 0;
}
