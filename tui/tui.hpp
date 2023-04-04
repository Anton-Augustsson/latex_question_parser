#pragma once

#include "../itemize/itemize.hpp"


struct ShowVisitor
{
  template <class T>
  void operator()(T&& _in){ _in.show(); }
};

struct AskVisitor
{
  template <class T>
  void operator()(T&& _in){ _in.ask(); }
};

struct ShowResultVisitor 
{ 
  template <class T>
  void operator()(T&& _in){ _in.showResult(); }
};

struct CompareVisitor 
{ 
  template <class T>
  bool operator()(T&& _in){ return _in.compare(); }
};

void tui_ask(Itemize *itemize_obj){
  for (int i = 0; i < itemize_obj->get_size(); i++)
  {
    try {
      Item item = std::get<Item>(itemize_obj->get_item(i));
      answer_t answer = item.getAnswer();
      std::visit(AskVisitor{}, answer);
      item.setAnswer(answer);
      itemize_obj->set_item(i, item);
    }
    catch (std::bad_variant_access const& ex) {
      continue; 
    }
  }
}

void tui_result(Itemize *itemize_obj){
  std::vector<std::variant<Itemize, Item>> *items_list;
  items_list = itemize_obj->get_items_list();
  int score = 0;
  bool comp_res;
  for(std::variant<Itemize, Item> j : (*items_list)){
    try {
      Item item = std::get<Item>(j);
      answer_t answer = item.getAnswer();
      std::visit(ShowResultVisitor{}, answer);
      comp_res = std::visit(CompareVisitor{}, answer);
      if (comp_res == true) { score++; }
    }
    catch (std::bad_variant_access const& ex) {
      continue; 
    }
  }
  std::cout << "Your score: " << score << std::endl;
}

void tui_quiz(std::vector<Itemize> *data) {
  for (Itemize i : (*data)) {
    tui_ask(&i);
    tui_result(&i);
  }
}


void tui(std::vector<Itemize> *data) {
  char ans;
  char all = 'a';
  char quiz = 'z';
  char first = 'f';
  char next = 'n';
  char quit = 'q';

  while (ans != all && ans != first && ans != quit && ans != quiz) {
    std::cout << "Show all[a]" << '\n';
    std::cout << "Show first[f]" << '\n';
    std::cout << "Start quiz[z]" << '\n';
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
        std::cout << "Show next[n]" << '\n';
        std::cout << "Quit[q]" << '\n';
        std::cin >> ans;
      }
      if (ans == quit) {
        return;
      }
    }
  }
  else if (ans == quiz) {
    tui_quiz(data);
  }
  else {
    return;
  }
}