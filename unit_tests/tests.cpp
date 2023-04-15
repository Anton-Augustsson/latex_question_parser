#include "../constants/constants.hpp"
#include "../itemize/itemize.hpp"
#include "../itemize/item.hpp"
#include "../parser/parser.hpp"

#include <stdio.h>
#include <string>
#include <iostream>
#include <tuple>

bool all_itemizes_are_equal(std::vector<std::vector<std::string>> all_itemize, std::vector<std::vector<std::string>> correct_all_itemize) 
{
	if (all_itemize.size() != correct_all_itemize.size()) {
		return false;
	}

	for (int i = 0; i < all_itemize.size(); i++)  {
		if (all_itemize[i].size() != correct_all_itemize[i].size()) {
			return false;
		}

		for (int j = 0; j < all_itemize[i].size(); j++) {
			// Check that the all strings are equal to each other
			if (all_itemize[i][j].compare(correct_all_itemize[i][j]) != 0) {
				return false;
			}
		}
	}

	return true;
}

int unit_test_all_itemizes_are_equal() 
{
	std::vector<std::vector<std::string>> all_itemize1 = {{"\\begin{itemize}", "\\item bdsfasdf 7", "asdfdsf 8", 
    "%%pragma ans Definition", "\\item dfafew: 9", "\\end{itemize}"}};
	std::vector<std::vector<std::string>> all_itemize2 = {{"\\begin{itemize}", "\\item bdsfasdf 7", "asdfdsf 8", 
    "%%pragma ans Definition", "\\item dfasfew: 9", "\\end{itemize}"}};

	if (all_itemizes_are_equal(all_itemize1, all_itemize1) && !all_itemizes_are_equal(all_itemize1, all_itemize2)) {
		std::cout << "Succeeded: unit_test_all_itemizes_are_equal" << std::endl;
		return 1;
	}
	else {
		std::cout << "Failed: unit_test_all_itemizes_are_equal" << std::endl;
		return 0;
	}

}

int unit_test_read_text() 
{
    std::vector<std::vector<std::string>> all_itemize = {};
    std::vector<std::vector<std::string>> correct_all_itemize = {{"\\begin{itemize}", "\\item bdsfasdf 7", "asdfdsf 8", 
    "%%pragma ans Definition", "\\item dfasfew: 9", "\\end{itemize}"}};
    std::vector<std::vector<std::string>> wrong_all_itemize = {{"\\begin{itemize}", "\\item bdsfasdf 7", "asdfdsf 8", 
    "%%pragma ans Definition", "\\item dfafew: 9", "\\end{itemize}"}};

	int result = 0;
    read_text("\\begin{itemize}\n\\item bdsfasdf 7\nasdfdsf 8\n%%pragma ans Definition\n\\item dfasfew: 9\n\\end{itemize}\n", &all_itemize);

	if (all_itemizes_are_equal(all_itemize, correct_all_itemize) && !all_itemizes_are_equal(all_itemize, wrong_all_itemize)) {
		std::cout << "Succeeded: unit_test_foo" << std::endl;
		return 1;
	}
	else {
		std::cout << "Failed: unit_test_foo" << std::endl;
		return 0;
	}
}

int unit_test_add_itemizes_basic()
{
    std::vector<std::vector<std::string>> all_itemize = {};
  	std::vector<Itemize> data = {};
    std::vector<std::vector<std::string>> correct_all_itemize = {{"\\begin{itemize}", 
	"\\item bds 7", "\\item sdf 8", "\\end{itemize}"}};
	std::string text = "\\begin{itemize}\n\\item bds 7\n\\item sdf 8\n\\end{itemize}\n";
  	Itemize itemizeObj;
  	Itemize correct_itemizeObj;
  	Item itemObj7("bds 7");
  	Item itemObj8("sdf 8");
  	int ignore_idx;

    read_text(text, &all_itemize);
	if (!all_itemizes_are_equal(all_itemize, correct_all_itemize))
	{
		std::cout << "Failed (read_text): unit_test_foo" << std::endl;
		return 0;
	}

    std::tie(ignore_idx, itemizeObj) =  add_itemizes(&correct_all_itemize[0], 0);

  	correct_itemizeObj.add(itemObj7);
  	correct_itemizeObj.add(itemObj8);

	if (itemizeObj.compare(&correct_itemizeObj) == 0)
	{
		std::cout << "Succeeded: unit_test_itemizes_basic" << std::endl;
		return 1;
	}
	else 
	{
		std::cout << "Failed: unit_test_itemizes_basic" << std::endl;
		return 0;
	}
}

int unit_test_get_data()
{
    std::vector<std::vector<std::string>> all_itemize = {};
  	std::vector<Itemize> data = {};
	std::string text = "\\begin{itemize}\n\\item bdf 1\nasd\n\\item dfas 2\n\\end{itemize}\n"
					   "\\begin{itemize}\n\\item ssf 3\n\\end{itemize}\n";

  	std::vector<Itemize> correct_data = {};
  	Itemize correct_itemizeObj1;
  	Itemize correct_itemizeObj2;
  	Item itemObj1("bdf 1 asd");
  	Item itemObj2("dfas 2");
  	Item itemObj3("ssf 3");
	correct_itemizeObj1.add(itemObj1);
	correct_itemizeObj1.add(itemObj2);
	correct_itemizeObj2.add(itemObj3);
	correct_data.push_back(correct_itemizeObj1);
	correct_data.push_back(correct_itemizeObj2);

    read_text(text, &all_itemize);
	get_data(&all_itemize, &data);

	if (correct_data.size() != data.size())
	{
		std::cout << "Failed (wrong size): unit_test_get_data" << std::endl;
		return 0;
	}

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].compare(&correct_data[i]) != 0)
		{
			std::cout << "Failed: unit_test_get_data" << std::endl;
			return 0;
		}
	}

	std::cout << "Succeeded: unit_test_get_data" << std::endl;
	return 1;
}

int test_suit_parser()
{
	int succeeded = 0;
	int tests = 0;
	succeeded += unit_test_all_itemizes_are_equal(); tests++;
	succeeded += unit_test_read_text(); tests++;
	succeeded += unit_test_add_itemizes_basic(); tests++;
	succeeded += unit_test_get_data(); tests++;
	std::cout << "Number of successful tests: " << succeeded << "/" << tests << std::endl;
	return 1;
}

int main()
{
	test_suit_parser();
    return 0;
}