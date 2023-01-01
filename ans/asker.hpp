#include <type_traits>

template<typename T>
bool compare_answer(T correct, T user){
    return correct == user;
}

template<>
bool compare_answer<std::string>(std::string correct, std::string user){
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
    Asker() {}
    void askForAnswer(){
        std::cout << question;
        std::cin >> user_answer;
    }
    bool compareAnswer(){
        bool result = compare_answer<T>(correct_answer, user_answer);
        return result;
    }

    void showResult(){
        std::cout << "Correct: " << correct_answer << ", Your answer: " << user_answer << '\n';
    }
};
