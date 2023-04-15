#pragma once

#include <string>
#include <iostream>
#include "asker.hpp"
#include "../constants/macros.hpp"


/*
    An item can have a answer, which can be of different classes.
    Those classes are defined in this document. All answer classes
    uses asker which can have various types. It is done in this way 
    since all method's does more or less the same operations, so to
    reduce repeated code I use a template.

    If you want to make the program interpret an item as an question
    write:
        %pragma ans <class-name> <answer>
*/
namespace ans
{
    /*
        Multiple choice provide different choices which the user 
        can select by entering a number. There is a correct answer.

        Latex example:
        \begin{itemize}
            \item Write anything you want before pragma and it's item.
                  It is important that you use \begin{choices}...
            %pragma ans MultipleChoice 2
            \item What is the first three numbers in pi?
            \begin{choices}
                \choice $1.23$
                \choice $3.14$ 
                \choice $5.12$ 
            \end{choices}
            \item Write anything you want after it
        \end{itemize}

        TODO: support multiple correct answers
    */
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

    /*
        Definition does not have a correct answer. When you give an answer 
        in the quiz you can compare you answer with the one that was specified 
        in the latex code.

        Latex example:
        \begin{itemize}
            \item It is important that you use ":" as this is the 
                  symbol for defitions.
            %pragma ans Definition
            \item Pi: 3.14
            \item Write anything you want after it
        \end{itemize}
    */
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
        Definition() 
        {
            subject = undefine_str;
        }

        void show() { 
            if (subject.compare(undefine_str) == 0)
                return;

            std::cout << subject << " " << def << '\n'; 
        }
        void ask() { asker.askForAnswer(); }
        bool compare(){ return asker.compareAnswer(); }
        void showResult() { asker.showResult(); }
    };

    /*
        SingleAnswer defines a question and one answer.

        Latex example:
        \begin{itemize}
            \item It is important that you use "?" since it is what separate the 
                  answer from the question.
            %pragma ans SingleAnswer 3.14
            \item What are the three first numbers in Pi? 3.14
            \item Write anything you want after it
        \end{itemize}
    */
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
        SingleAnswer() 
        {
            question = undefine_str;
        }

        void show() { 
            if (question.compare(undefine_str) == 0)
                return;
            std::cout << answer << '\n'; 
        }
        void ask() { asker.askForAnswer(); }
        bool compare(){ return asker.compareAnswer(); }
        void showResult() { asker.showResult(); }
    };
}