// itemize.hpp
#ifndef ITEMIZE_HPP_
#define ITEMIZE_HPP_

#include <vector>
#include <string>
#include <variant>
#include "item.hpp"

struct ItemAnswerAskVisitor
{
  template <class T>
  void operator()(T&& _in){ _in.ask(); }
};


// https://gieseanw.wordpress.com/2017/05/03/a-true-heterogeneous-container-in-c/
struct PrintVisitor
{
  template <class T>
  void operator()(T&& _in){ _in.print(); }
};
struct IncreaseIndentVisitor
{
  std::string indent;
  template <class T>
  void operator()(T&& _in){ _in.increase_indent(indent); }
};


class Itemize {
  private:
    std::vector<std::variant<Itemize, Item>> items_list;
    std::string indent;

  public:
    void print() {
      for(auto& i : items_list) {
        std::visit(IncreaseIndentVisitor{indent}, i);
        std::visit(PrintVisitor{}, i);
      }
    }

    void add(std::variant<Itemize, Item> obj) {
      items_list.push_back(obj);
    }

    void increase_indent(std::string ind) {
      indent = ind;
      indent += "\t";
    }

    std::vector<std::variant<Itemize, Item>> *get_items_list() {
      return &items_list;
    }

    void set_items_list(std::vector<std::variant<Itemize, Item>> itemize_items_list) {
      items_list = itemize_items_list;
    }

    std::variant<Itemize, Item> get_item(int idx) {
      return items_list[idx];
    }

    void set_item(int idx, std::variant<Itemize, Item> item) {
      // Warning this offers no protection you need to know the proper idx
      items_list[idx] = item;
    }

    int get_size() {
      return items_list.size();
    }
};

#endif