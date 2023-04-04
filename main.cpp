#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <string.h>

#include "ans/ans.hpp"
#include "constants/constants.hpp"
#include "itemize/item.hpp"
#include "itemize/itemize.hpp"
#include "parser/parser.hpp"
#include "tui/tui.hpp"


/*
  When calling the program

  Use f to specify the file you want to run:
  $ a.out f file.tex

  Use t for raw latex text:
  $ a.out t "\begin{itemize}
	              \item bdsfasdf 7
	              asdfdsf 8
                %pragma ans Definition
	              \item dfasfew: 9
             \end{itemize}"
*/
int main(int argc, char *argv[]) 
{
  if ( !(argc == 3 || argc == 4) )
  {
    std::cout << "Usage normal: $ a.out f file.tex"; 
    std::cout << "Usage silent: $ a.out f file.tex s"; 
    return -1;
  }

  std::vector<std::vector<std::string>> all_itemize = {};
  std::vector<Itemize> data = {};
 
  if (strcmp(argv[1], "f") == 0) {
    std::ifstream myfile (argv[2]);
    
    if (myfile.is_open())
    {
      read(&myfile, &all_itemize);
      myfile.close();
    }
    else std::cout << "Unable to open file";
  }
  else if (strcmp(argv[1], "t") == 0) {
    read_text(argv[2], &all_itemize);
  }
  else {
    return 0;
  }

  get_data(&all_itemize, &data);

  if ( !(argc == 4 && strcmp(argv[3], "s") == 0) )
  {
    tui(&data);
  }

  return 0;
}
