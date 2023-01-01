// ans.hpp
#ifndef ANS_HPP_
#define ANS_HPP_

#include <string>
#include <iostream>
#include "asker.hpp"

namespace ans
{
    class Definition {
    private:
        std::string subject;
        std::string def;
        ask::Asker<std::string> asker;

    public:
        Definition(std::string definition_subject, std::string definition_def) {
            subject = definition_subject;
            def = definition_def;
            asker = ask::Asker<std::string>(def, (subject + ": "));
        }
        Definition() {
            asker = ask::Asker<std::string>("undefined");
        }

        void show() { std::cout << subject << " " << def << '\n'; }
        void ask() { asker.askForAnswer(); }
        //bool compare(){ return asker.compareAnswer(); }
        void showResult() { asker.showResult(); }
    };

    class SingleAnswer {
    private:
        std::string question;
        int answer;
        ask::Asker<int> asker;

    public:
        void show() { std::cout << answer << '\n'; }
        void ask() { asker.askForAnswer(); }
        //bool compare(){ return asker.compareAnswer(); }
        void showResult() { asker.showResult(); }
    };
}

#endif