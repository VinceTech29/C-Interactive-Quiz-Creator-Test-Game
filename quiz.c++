#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

struct Question {
    string questionText;
    vector<string> options;
    int correctAnswer;
};

int main() {
    vector<Question> quiz;
    int numQuestions;

    cout << "===== QUIZ CREATOR =====\n";
    cout << "Enter number of questions: ";
    cin >> numQuestions;
    cin.ignore();

    // =============================
    // CREATE QUIZ
    // =============================
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

        cout << "Correct answer (0=A, 1=B, 2=C, 3=D): ";
        cin >> q.correctAnswer;
        cin.ignore();

        quiz.push_back(q);
    }

    // =============================
    // RANDOMIZE QUESTIONS
    // =============================
    random_device rd;
    mt19937 g(rd());
    shuffle(quiz.begin(), quiz.end(), g);

    cout << "\n=================================\n";
    cout << "      QUIZ STARTING NOW!\n";
    cout << "=================================\n";

    int score = 0;

    // =============================
    // TEST MODE
    // =============================
    for (int i = 0; i < quiz.size(); i++) {
        cout << "\nQuestion " << i + 1 << ": " << quiz[i].questionText << "\n";

        cout << "A. " << quiz[i].options[0] << "\n";
        cout << "B. " << quiz[i].options[1] << "\n";
        cout << "C. " << quiz[i].options[2] << "\n";
        cout << "D. " << quiz[i].options[3] << "\n";

        int answer;
        cout << "Your answer (0=A, 1=B, 2=C, 3=D): ";
        cin >> answer;

        if (answer == quiz[i].correctAnswer) {
            cout << "✅ Correct!\n";
            score++;
        } else {
            cout << "❌ Wrong! Correct answer was: "
                 << char('A' + quiz[i].correctAnswer) << "\n";
        }
    }

    // =============================
    // FINAL RESULT
    // =============================
    cout << "\n=================================\n";
    cout << "         FINAL RESULT\n";
    cout << "=================================\n";
    cout << "Score: " << score << " / " << quiz.size() << "\n";

    double percentage = (double)score / quiz.size() * 100;
    cout << "Percentage: " << percentage << "%\n";

    if (percentage == 100)
        cout << "🏆 Excellent!\n";
    else if (percentage >= 60)
        cout << "👏 Good Job!\n";
    else
        cout << "📚 Keep Studying!\n";

    return 0;
}
