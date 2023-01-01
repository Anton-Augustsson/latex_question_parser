#include <fstream>
#include <string>
#include <vector>

#include "ans/ans.hpp"
#include "constants/constants.hpp"
#include "itemize/item.hpp"
#include "itemize/itemize.hpp"
#include "parser/parser.hpp"
#include "tui/tui.hpp"


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
