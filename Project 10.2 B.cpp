#include <iostream>
#include "student .h"

using namespace std;

int main() {
    int N;
    do {
        cout << "Enter the number of students N (> 0): ";
        cin >> N;
    } while (N <= 0);

    Student* s = new Student[N];

    int menuItem;
    unsigned course;
    string surname;
    double targetAvg;
    int found;

    do {
        cout << endl << endl;
        cout << "Select an action:" << endl;
        cout << " [1] - enter data from keyboard" << endl;
        cout << " [2] - print data on screen" << endl;
        cout << " [3] - physical sorting (Avg ASC -> Course ASC -> Surname DESC)" << endl;
        cout << " [4] - index sorting and printing (Avg ASC -> Course ASC -> Surname ASC)" << endl;
        cout << " [5] - binary search (by Surname, Course, Average Grade)" << endl;
        cout << " [0] - exit program" << endl << endl;
        cout << "Enter choice: ";
        cin >> menuItem;
        cout << endl;

        switch (menuItem) {
        case 1:
            Create(s, N);
            break;
        case 2:
            Print(s, N);
            break;
        case 3:
            Sort(s, N);
            cout << "Array physically sorted." << endl;
            break;
        case 4: {
            int* I = IndexSort(s, N);
            PrintIndexSorted(s, I, N);
            delete[] I;
            break;
        }
        case 5:
            cout << "Enter search keys (note: array must be sorted with option 3 first):" << endl;
            do {
                cout << " course (1-6): ";
                cin >> course;
            } while (course < 1 || course > 6);

            cout << " average grade: ";
            cin >> targetAvg;

            cin.get();
            cin.sync();
            cout << " surname: ";
            getline(cin, surname);

            if ((found = BinSearch(s, N, surname, course, targetAvg)) != -1)
                cout << "Student found at position " << found + 1 << endl;
            else
                cout << "Student not found (ensure array is sorted using option 3, and all keys match)." << endl;
            break;
        case 0:
            break;
        default:
            cout << "Invalid input! Please enter a menu item number." << endl;
        }
    } while (menuItem != 0);

    delete[] s;
    return 0;
}