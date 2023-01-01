// ans.hpp
#ifndef ANS_HPP_
#define ANS_HPP_

#include <string>
#include <iostream>
#include "asker.hpp"

namespace ans
{
    class MultipleChoice {
    private:
        std::string chooses;
        int correct_choice;
        Asker<int> asker;

    public:
        MultipleChoice(std::string multiple_choice_chooses, int multiple_choice_correct_choice) {
            chooses = multiple_choice_chooses;
            correct_choice = multiple_choice_correct_choice;
            asker = Asker<int>(correct_choice, chooses);
        }
        MultipleChoice() {
            asker = Asker<int>(0);
        }

        void show() { std::cout << chooses << " " << correct_choice << '\n'; }
        void ask() { asker.askForAnswer(); }
        bool compare(){ return asker.compareAnswer(); }
        void showResult() { asker.showResult(); }
    };

    class Definition {
    private:
        std::string subject;
        std::string def;
        Asker<std::string> asker;

    public:
        Definition(std::string definition_subject, std::string definition_def) {
            subject = definition_subject;
            def = definition_def;
            asker = Asker<std::string>(def, (subject + ": "));
        }
        Definition() {
            asker = Asker<std::string>("undefined");
        }

        void show() { std::cout << subject << " " << def << '\n'; }
        void ask() { asker.askForAnswer(); }
        bool compare(){ return asker.compareAnswer(); }
        void showResult() { asker.showResult(); }
    };

    class SingleAnswer {
    private:
        std::string question;
        std::string answer;
        Asker<std::string> asker;

    public:
        SingleAnswer(std::string single_answer_question, std::string single_answer_answer) {
            question = single_answer_question;
            answer = single_answer_answer;
            asker = Asker<std::string>(answer, question);
        }
        SingleAnswer() {
            asker = Asker<std::string>("undefined");
        }

        void show() { std::cout << answer << '\n'; }
        void ask() { asker.askForAnswer(); }
        bool compare(){ return asker.compareAnswer(); }
        void showResult() { asker.showResult(); }
    };
}

#endif