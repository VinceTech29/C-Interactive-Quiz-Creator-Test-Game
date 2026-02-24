#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cctype>

using namespace std;

struct Question {
    string questionText;
    vector<pair<char, string>> options;
    char correctAnswer;
};

char getValidOption(const string& prompt) {
    char ans;
    while (true) {
        cout << prompt;
        cin >> ans;
        ans = toupper(ans);
        if (ans >= 'A' && ans <= 'D') break;
        cout << "Invalid input. Please enter A, B, C, or D.\n";
    }
    cin.ignore();
    return ans;
}

vector<Question> createQuiz(int numQuestions) {
    vector<Question> quiz;
    for (int i = 0; i < numQuestions; i++) {
        Question q;
        q.options.resize(4);
        cout << "\n--- Question " << i + 1 << " ---\n";
        cin.ignore();
        cout << "Enter question: ";
        getline(cin, q.questionText);

        char optionLetter = 'A';
        for (int j = 0; j < 4; j++, optionLetter++) {
            cout << "Option " << optionLetter << ": ";
            string opt;
            getline(cin, opt);
            q.options[j] = {optionLetter, opt};
        }

        q.correctAnswer = getValidOption("Correct answer (A/B/C/D): ");
        quiz.push_back(q);
    }
    return quiz;
}

void shuffleQuiz(vector<Question>& quiz) {
    random_device rd;
    mt19937 g(rd());

    for (auto& q : quiz) {
        shuffle(q.options.begin(), q.options.end(), g);
        for (auto& opt : q.options) {
            if (toupper(opt.first) == q.correctAnswer) {
                q.correctAnswer = opt.first;
                break;
            }
        }
    }
    shuffle(quiz.begin(), quiz.end(), g);
}

int takeQuiz(const vector<Question>& quiz) {
    int score = 0;
    for (int i = 0; i < quiz.size(); i++) {
        cout << "\nQuestion " << i + 1 << ": " << quiz[i].questionText << "\n";
        for (const auto& opt : quiz[i].options)
            cout << opt.first << ". " << opt.second << "\n";

        char answer = getValidOption("Your answer (A/B/C/D): ");
        if (answer == quiz[i].correctAnswer) {
            cout << "✅ Correct!\n";
            score++;
        } else {
            string correctText;
            for (auto& opt : quiz[i].options) {
                if (opt.first == quiz[i].correctAnswer) {
                    correctText = opt.second;
                    break;
                }
            }
            cout << "❌ Wrong! Correct answer: " 
                 << quiz[i].correctAnswer << ". " << correctText << "\n";
        }
    }
    return score;
}

void showScore(int score, int total) {
    cout << "\n=================================\n";
    cout << "FINAL SCORE: " << score << " / " << total << "\n";
    double percent = (double)score / total * 100;
    cout << "Percentage: " << percent << "%\n";

    if (percent == 100)
        cout << "🏆 Perfect Score!\n";
    else if (percent >= 60)
        cout << "👏 Good Job!\n";
    else
        cout << "📚 Study More!\n";
}

int main() {
    cout << "===== QUIZ CREATOR =====\n";
    int numQuestions;
    cout << "How many questions? ";
    cin >> numQuestions;

    vector<Question> quiz = createQuiz(numQuestions);
    shuffleQuiz(quiz);

    cout << "\n========== TEST START ==========\n";
    int score = takeQuiz(quiz);
    showScore(score, quiz.size());

    return 0;
}