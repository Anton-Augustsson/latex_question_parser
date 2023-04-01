#include "../parser/parser.hpp"
#include <stdio.h>
#include <string>
#include <iostream>

bool all_itemizes_are_equal(std::vector<std::vector<std::string>> all_itemize, std::vector<std::vector<std::string>> correct_all_itemize) {
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

int unit_test_all_itemizes_are_equal() {
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

int unit_test_foo() {
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

int test_suit_parser()
{
	int succeeded = 0;
	int tests = 0;
	succeeded += unit_test_all_itemizes_are_equal(); tests++;
	succeeded += unit_test_foo(); tests++;
	std::cout << "Number of successful tests: " << succeeded << "/" << tests << std::endl;
	return 1;
}

int main()
{
	test_suit_parser();
    return 0;
}