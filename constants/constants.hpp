// constants.hpp
#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

#include <variant>
#include "../ans/ans.hpp"


namespace constants
{
  // Itemize
  const std::string begin_cmd =  "begin{itemize}";
  const std::string end_cmd =  "end{itemize}";

  // Item
  const std::string item_cmd =  "item";

  // ans
  const std::string multiple_choice_pragma = "pragma ans MultipleChoice ";
  const std::string definition_pragma = "pragma ans Definition";
  const std::string single_answer_pragma = "pragma ans SingleAnswer "; 
}

typedef std::variant<ans::Definition, ans::SingleAnswer> answer_t;

#endif