#pragma once

#include <string>
#include "../constants/constants.hpp"

class Item {
  private:
    std::string text;
    std::string indent;
    answer_t answer;

  public:
    Item(std::string item_text, answer_t item_answer) {
      text = item_text;
      answer = item_answer;
    }

    Item(std::string item_text) {
      text = item_text;
    }

    Item() {
      text = "";
    }

    void print() {
      std::cout << indent;
      std::cout << "* ";
      std::cout << text << '\n';
    }

    void increase_indent(std::string ind) {
      indent = ind;
      indent += "\t";
    }

    void setAnswer(answer_t new_answer){
      answer = new_answer;
    }

    std::string get_text()
    {
      return text;
    }

    int compare(Item *itemObj) {
      return text.compare((*itemObj).get_text());
    }

    answer_t getAnswer() {
      return answer;
    }
};