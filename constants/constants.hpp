// constants.hpp
#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

#include <variant>
#include "../ans/ans.hpp"


namespace constants
{
  const std::string begin_cmd =  "begin{itemize}";
  const std::string end_cmd =  "end{itemize}";
  const std::string item_cmd =  "item";
}

typedef std::variant<ans::Definition, ans::SingleAnswer> answer_t;

#endif