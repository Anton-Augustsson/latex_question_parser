#include <string>
#include <iostream>
#include "asker.hpp"

namespace ans
{
    class Answer {
    public:
        virtual void show(){
            std::cout << "Answer undefined" << '\n';
        }
        virtual void ask(){
            std::cout << "Nothing to ask" << '\n';
        }
        virtual void showResult(){
            std::cout << "Nothing to ask" << '\n';
        }
    };

    class Definition: public Answer {
    private:
        std::string subject;
        std::string def;
        ask::Asker<std::string> asker;

    public:
        Definition(std::string definition_subject, std::string definition_def) {
            subject = definition_subject;
            def = definition_def;
            asker = ask::Asker<std::string>(subject, def);
        }
        Definition() {
            asker = ask::Asker<std::string>("undefined");
        }

        void show() { std::cout << subject << " " << def << '\n'; }
        void ask() { asker.askForAnswer(); }
        void showResult() { asker.showResult(); }
    };

    class SingleAnswer: public Answer {
    private:
        std::string question;
        int answer;
        ask::Asker<int> asker;

    public:
        void show() { std::cout << answer << '\n'; }
        void ask() { asker.askForAnswer(); }
        void showResult() { asker.showResult(); }
    };
}