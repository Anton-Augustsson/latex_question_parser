#pragma once

#include <variant>
#include "../ans/ans.hpp"


namespace constant
{
  // Itemize
  const std::string begin_cmd =  "begin{itemize}";
  const std::string end_cmd =  "end{itemize}";

  // Item
  const std::string item_cmd =  "item";

  // ans
  const std::string multi_pragma = "pragma ans MultipleChoice ";
  const std::string def_pragma = "pragma ans Definition";
  const std::string single_pragma = "pragma ans SingleAnswer "; 
  const std::string undefined_str = "undefined";
}

typedef std::variant<ans::Definition, ans::SingleAnswer> answer_t;