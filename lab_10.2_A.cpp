#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h>

using namespace std;

enum Specialnist { IT, PHYSICS, MATHEMATICS, ENGINEERING };

string specialnistStr[] = { "IT", "Physics", "Mathematics", "Engineering" };

struct Student {
    string prizv;
    int kurs;
    Specialnist spec;
    int fizyka;
    int matematika;
    int informatyka;
};

void Create(Student* students, const int N);
void Print(const Student* students, const int N);
void Sort(Student* students, const int N);
int* IndexSort(Student* students, const int N);
void PrintIndexSorted(Student* students, int* index, const int N);
int BinSearch(Student* students, const int N, const string& prizv, const Specialnist spec, const int prof_bal);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "������ ������� ��������: ";
    cin >> N;

    Student* students = new Student[N];
    int* index = nullptr;

    int menuItem;
    do {
        cout << "\n����:\n";
        cout << "1 - �������� �����\n";
        cout << "2 - ���� ������� ��������\n";
        cout << "3 - Գ����� �������������\n";
        cout << "4 - �������� �������������\n";
        cout << "5 - �������� �����\n";
        cout << "0 - �����\n";
        cout << "������� ��: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(students, N);
            break;
        case 2:
            Print(students, N);
            break;
        case 3:
            Sort(students, N);
            cout << "��� ������� ������������.\n";
            break;
        case 4:
            delete[] index;
            index = IndexSort(students, N);
            PrintIndexSorted(students, index, N);
            break;
        case 5: {
            string prizv;
            int spec, prof_bal;
            cout << "������ �������: ";
            cin.ignore();
            getline(cin, prizv);
            cout << "������ ������������ (0 - IT, 1 - Physics, 2 - Mathematics, 3 - Engineering): ";
            cin >> spec;
            cout << "������ ������ � ����������� ��������: ";
            cin >> prof_bal;

            int result = BinSearch(students, N, prizv, (Specialnist)spec, prof_bal);
            if (result != -1) {
                cout << "������� ��������� � �������: " << result + 1 << endl;
            }
            else {
                cout << "�������� �� ��������.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "������������ ����!\n";
        }
    } while (menuItem != 0);

    delete[] students;
    delete[] index;
    return 0;
}

void Create(Student* students, const int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":\n";

        cin.ignore();
        cout << "�������: ";
        getline(cin, students[i].prizv);

        cout << "���� (1-4): ";
        cin >> students[i].kurs;

        cout << "������������ (0 - IT, 1 - Physics, 2 - Mathematics, 3 - Engineering): ";
        cin >> spec;
        students[i].spec = (Specialnist)spec;

        cout << "������ � ������: ";
        cin >> students[i].fizyka;

        cout << "������ � ����������: ";
        cin >> students[i].matematika;

        cout << "������ � �����������: ";
        cin >> students[i].informatyka;

        cout << endl;
    }
}

void Print(const Student* students, const int N) {
    cout << "==================================================================================" << endl;
    cout << "| � | �������       | ���� | ������������  | Գ���� | ���������� | ����������� |" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << i + 1 << " "
            << "| " << setw(15) << left << students[i].prizv
            << "| " << setw(4) << right << students[i].kurs << " "
            << "| " << setw(13) << left << specialnistStr[students[i].spec]
            << "| " << setw(7) << right << students[i].fizyka
            << "| " << setw(11) << right << students[i].matematika
            << "| " << setw(11) << right << students[i].informatyka << " |" << endl;
    }
    cout << "==================================================================================" << endl;
}

void Sort(Student* students, const int N) {
    sort(students, students + N, [](const Student& a, const Student& b) {
        // 1. �� ������������
        if (specialnistStr[a.spec] != specialnistStr[b.spec])
            return specialnistStr[a.spec] < specialnistStr[b.spec];

        // 2. �� ���������� ���������
        int prof_a = (a.spec == IT) ? a.informatyka :
            (a.spec == PHYSICS) ? a.fizyka : a.matematika;
        int prof_b = (b.spec == IT) ? b.informatyka :
            (b.spec == PHYSICS) ? b.fizyka : b.matematika;
        if (prof_a != prof_b)
            return prof_a < prof_b;

        // 3. �� �������� (�� ����������)
        return a.prizv < b.prizv;
    });
}

int* IndexSort(Student* students, const int N) {
    int* index = new int[N];
    for (int i = 0; i < N; i++)
        index[i] = i;

    sort(index, index + N, [students](int a, int b) {
        // 1. �� ������������
        if (specialnistStr[students[a].spec] != specialnistStr[students[b].spec])
            return specialnistStr[students[a].spec] < specialnistStr[students[b].spec];

        // 2. �� ���������� ���������
        int prof_a = (students[a].spec == IT) ? students[a].informatyka :
            (students[a].spec == PHYSICS) ? students[a].fizyka : students[a].matematika;
        int prof_b = (students[b].spec == IT) ? students[b].informatyka :
            (students[b].spec == PHYSICS) ? students[b].fizyka : students[b].matematika;
        if (prof_a != prof_b)
            return prof_a < prof_b;

        // 3. �� �������� (�� ����������)
        return students[a].prizv < students[b].prizv;
        });

    return index;
}


void PrintIndexSorted(Student* students, int* index, const int N) {
    cout << "=======================================================================================" << endl;
    cout << "| � | �������       | ���� | ������������  | Գ���� | ���������� | ����������� |" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        int idx = index[i];
        cout << "| " << setw(2) << right << i + 1 << " "
            << "| " << setw(15) << left << students[idx].prizv
            << "| " << setw(4) << right << students[idx].kurs << " "
            << "| " << setw(13) << left << specialnistStr[students[idx].spec]
            << "| " << setw(7) << right << students[idx].fizyka
            << "| " << setw(11) << right << students[idx].matematika
            << "| " << setw(11) << right << students[idx].informatyka << " |" << endl;
    }
    cout << "=======================================================================================" << endl;
}

int BinSearch(Student* students, const int N, const string& prizv, const Specialnist spec, const int prof_bal) {
    int left = 0, right = N - 1, mid;
    while (left <= right) {
        mid = (left + right) / 2;

        if (students[mid].spec == spec && students[mid].informatyka == prof_bal && students[mid].prizv == prizv) {
            return mid;
        }

        if (students[mid].spec < spec || (students[mid].spec == spec && students[mid].informatyka < prof_bal) ||
            (students[mid].spec == spec && students[mid].informatyka == prof_bal && students[mid].prizv < prizv)) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}
