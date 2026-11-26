#include "student .h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void Create(Student* s, const int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "Student # " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();

        cout << " surname: ";
        getline(cin, s[i].surname);

        do {
            cout << " course (1-6): ";
            cin >> s[i].course;
        } while (s[i].course < 1 || s[i].course > 6);

        do {
            cout << " specialty (0 - CS, 1 - Informatics, 2 - Math & Econ, 3 - Phys & Inf, 4 - Labor Training): ";
            cin >> spec;
        } while (spec < 0 || spec > 4);
        s[i].spec = (Specialnist)spec;

        do {
            cout << " physics grade (2-5): ";
            cin >> s[i].physics;
        } while (s[i].physics < 2 || s[i].physics > 5);

        do {
            cout << " math grade (2-5): ";
            cin >> s[i].math;
        } while (s[i].math < 2 || s[i].math > 5);

        switch (s[i].spec) {
        case CS:
            do {
                cout << " programming grade (2-5): ";
                cin >> s[i].programming;
            } while (s[i].programming < 2 || s[i].programming > 5);
            break;
        case INF:
            do {
                cout << " numerical methods grade (2-5): ";
                cin >> s[i].numerical_methods;
            } while (s[i].numerical_methods < 2 || s[i].numerical_methods > 5);
            break;
        case ME:
        case PI:
        case LT:
            do {
                cout << " pedagogy grade (2-5): ";
                cin >> s[i].pedagogy;
            } while (s[i].pedagogy < 2 || s[i].pedagogy > 5);
            break;
        }
        cout << endl;
    }
}

void Print(const Student* s, const int N) {
    string specStr[] = { "Computer Science", "Informatics", "Math & Economics", "Physics & Informatics", "Labor Training" };

    cout << "=======================================================================================================================" << endl;
    cout << "| #  | Surname       | Crse | Specialty               | Physics | Math       | Program.   | Num. Meth. | Pedagogy   |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << s[i].surname;
        cout << "| " << setw(4) << right << s[i].course << " ";
        cout << "| " << setw(23) << left << specStr[s[i].spec] << " ";
        cout << "| " << setw(7) << right << s[i].physics << " ";
        cout << "| " << setw(10) << right << s[i].math << " ";

        switch (s[i].spec) {
        case CS:
            cout << "| " << setw(10) << right << s[i].programming << " "
                << "| " << setw(10) << right << " " << " "
                << "| " << setw(10) << right << " " << " |" << endl;
            break;
        case INF:
            cout << "| " << setw(10) << right << " " << " "
                << "| " << setw(10) << right << s[i].numerical_methods << " "
                << "| " << setw(10) << right << " " << " |" << endl;
            break;
        case ME:
        case PI:
        case LT:
            cout << "| " << setw(10) << right << " " << " "
                << "| " << setw(10) << right << " " << " "
                << "| " << setw(10) << right << s[i].pedagogy << " |" << endl;
            break;
        }
    }
    cout << "=======================================================================================================================" << endl;
    cout << endl;
}

int GetThirdGrade(const Student& st) {
    switch (st.spec) {
    case CS:  return st.programming;
    case INF: return st.numerical_methods;
    default:  return st.pedagogy;
    }
}

double CalcAvg(const Student& st) {
    return (st.physics + st.math + GetThirdGrade(st)) / 3.0;
}

// 1. Фізичне впорядкування: середній бал (зростання) -> курс (зростання) -> прізвище (спадання)
void Sort(Student* s, const int N) {
    Student tmp;
    const double EPS = 1e-6;
    for (int i0 = 0; i0 < N - 1; i0++) {
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            double avg1 = CalcAvg(s[i1]);
            double avg2 = CalcAvg(s[i1 + 1]);
            bool sameAvg = fabs(avg1 - avg2) < EPS;

            if ((avg1 > avg2 + EPS) ||
                (sameAvg && s[i1].course > s[i1 + 1].course) ||
                (sameAvg && s[i1].course == s[i1 + 1].course && s[i1].surname < s[i1 + 1].surname))
            {
                tmp = s[i1];
                s[i1] = s[i1 + 1];
                s[i1 + 1] = tmp;
            }
        }
    }
}

// 2. Індексне впорядкування: середній бал (зростання) -> курс (зростання) -> прізвище (зростання)
int* IndexSort(const Student* s, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;

    const double EPS = 1e-6;
    int i, j, value;
    for (i = 1; i < N; i++) {
        value = I[i];
        double valAvg = CalcAvg(s[value]);
        for (j = i - 1; j >= 0; j--) {
            double jAvg = CalcAvg(s[I[j]]);
            bool sameAvg = fabs(jAvg - valAvg) < EPS;

            if ((jAvg > valAvg + EPS) ||
                (sameAvg && s[I[j]].course > s[value].course) ||
                (sameAvg && s[I[j]].course == s[value].course && s[I[j]].surname > s[value].surname))
            {
                I[j + 1] = I[j];
            }
            else {
                break;
            }
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(const Student* s, const int* I, const int N) {
    string specStr[] = { "Computer Science", "Informatics", "Math & Economics", "Physics & Informatics", "Labor Training" };

    cout << "=======================================================================================================================" << endl;
    cout << "| #  | Surname       | Crse | Specialty               | Physics | Math       | Program.   | Num. Meth. | Pedagogy   |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << s[I[i]].surname;
        cout << "| " << setw(4) << right << s[I[i]].course << " ";
        cout << "| " << setw(23) << left << specStr[s[I[i]].spec] << " ";
        cout << "| " << setw(7) << right << s[I[i]].physics << " ";
        cout << "| " << setw(10) << right << s[I[i]].math << " ";

        switch (s[I[i]].spec) {
        case CS:
            cout << "| " << setw(10) << right << s[I[i]].programming << " "
                << "| " << setw(10) << right << " " << " "
                << "| " << setw(10) << right << " " << " |" << endl;
            break;
        case INF:
            cout << "| " << setw(10) << right << " " << " "
                << "| " << setw(10) << right << s[I[i]].numerical_methods << " "
                << "| " << setw(10) << right << " " << " |" << endl;
            break;
        case ME:
        case PI:
        case LT:
            cout << "| " << setw(10) << right << " " << " "
                << "| " << setw(10) << right << " " << " "
                << "| " << setw(10) << right << s[I[i]].pedagogy << " |" << endl;
            break;
        }
    }
    cout << "=======================================================================================================================" << endl;
    cout << endl;
}

// 3. Бінарний пошук (по масиву, фізично відсортованому функцією Sort)
int BinSearch(const Student* s, const int N, const string surname, const unsigned course, const double targetAvg) {
    int L = 0, R = N - 1, m;
    const double EPS = 1e-2;
    do {
        m = (L + R) / 2;
        double mAvg = CalcAvg(s[m]);
        bool sameAvg = fabs(mAvg - targetAvg) < EPS;

        if (sameAvg && s[m].course == course && s[m].surname == surname)
            return m;

        if ((mAvg < targetAvg - EPS) ||
            (sameAvg && s[m].course < course) ||
            (sameAvg && s[m].course == course && s[m].surname > surname))
        {
            L = m + 1;
        }
        else {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}