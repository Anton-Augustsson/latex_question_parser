#pragma once

#include <type_traits>
#include <string>
#include "../constants/macros.hpp"


template<typename T>
bool compare_answer(T correct, T user)
{
    return correct == user;
}

template<>
bool compare_answer<std::string>(std::string correct, std::string user)
{
    return correct.compare(user) == 0;
}

template <typename T>
class Asker
{
private:
    std::string question;
    T correct_answer;
    T user_answer;    
public:
    Asker(T asker_correct_answer, std::string asker_question) : correct_answer(asker_correct_answer) {
        question = asker_question;
    }
    Asker(T asker_correct_answer) : correct_answer(asker_correct_answer) {
        question = "Your answer: ";
    }
    Asker() {
        question = undefine_str;

    }

    void askForAnswer(){
        if (question.compare(undefine_str) == 0)
            return;

        std::cout << question;
        std::cin >> user_answer;
    }
    bool compareAnswer(){
        if (question.compare(undefine_str) == 0)
            false;

        bool result = compare_answer<T>(correct_answer, user_answer);
        return result;
    }

    void showResult(){
        if (question.compare(undefine_str) == 0)
            return;

        std::cout << "Correct: " << correct_answer << ", Your answer: " << user_answer << '\n';
    }
};