namespace ask
{
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
            bool result;
            if (std::is_same<T, std::string>::correct_answer) {
                result = correct_answer.compare(user_answer);
            }
            else {
                result = (user_answer == correct_answer);
            }
            return result;
        }

        void showResult(){
            std::cout << "Correct: " << correct_answer << ", Your answer: " << user_answer << '\n';
        }
    };
}