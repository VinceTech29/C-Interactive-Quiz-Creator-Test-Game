#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

struct Question {
    string questionText;
    vector<string> options;
    char correctAnswer; // A, B, C, D
};

int main() {
    vector<Question> quiz;
    int numQuestions;

    cout << "===== QUIZ CREATOR =====\n";
    cout << "How many questions? ";
    cin >> numQuestions;
    cin.ignore();

    // =========================
    // CREATE QUESTIONS
    // =========================
    for (int i = 0; i < numQuestions; i++) {
        Question q;
        q.options.resize(4);

        cout << "\n--- Question " << i + 1 << " ---\n";

        cout << "Enter question: ";
        getline(cin, q.questionText);

        cout << "Option A: ";
        getline(cin, q.options[0]);

        cout << "Option B: ";
        getline(cin, q.options[1]);

        cout << "Option C: ";
        getline(cin, q.options[2]);

        cout << "Option D: ";
        getline(cin, q.options[3]);

        cout << "Correct answer (A/B/C/D): ";
        cin >> q.correctAnswer;
        q.correctAnswer = toupper(q.correctAnswer);
        cin.ignore();

        quiz.push_back(q);
    }

    // =========================
    // RANDOMIZE QUESTIONS
    // =========================
    random_device rd;
    mt19937 g(rd());
    shuffle(quiz.begin(), quiz.end(), g);

    cout << "\n=================================\n";
    cout << "          TEST START\n";
    cout << "=================================\n";

    int score = 0;

    // =========================
    // TEST MODE
    // =========================
    for (int i = 0; i < quiz.size(); i++) {
        cout << "\nQuestion " << i + 1 << ": "
             << quiz[i].questionText << "\n";

        cout << "A. " << quiz[i].options[0] << "\n";
        cout << "B. " << quiz[i].options[1] << "\n";
        cout << "C. " << quiz[i].options[2] << "\n";
        cout << "D. " << quiz[i].options[3] << "\n";

        char userAnswer;
        cout << "Your answer (A/B/C/D): ";
        cin >> userAnswer;
        userAnswer = toupper(userAnswer);

        if (userAnswer == quiz[i].correctAnswer) {
            cout << "✅ Correct!\n";
            score++;
        } else {
            cout << "❌ Wrong! Correct answer was "
                 << quiz[i].correctAnswer << "\n";
        }
    }

    // =========================
    // FINAL SCORE
    // =========================
    cout << "\n=================================\n";
    cout << "FINAL SCORE: " << score
         << " / " << quiz.size() << "\n";

    double percent = (double)score / quiz.size() * 100;
    cout << "Percentage: " << percent << "%\n";

    if (percent == 100)
        cout << "🏆 Perfect Score!\n";
    else if (percent >= 60)
        cout << "👏 Good Job!\n";
    else
        cout << "📚 Study More!\n";

    return 0;
}
