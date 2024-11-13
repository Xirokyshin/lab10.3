#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <algorithm>  

using namespace std;

struct Zodiac {
    string surname;
    string name;
    string zodiac_sign;
    int birthday[3]; // [0] - ����, [1] - �����, [2] - ��
};

// ������� ��� ��������� ����
void displayMenu() {
    cout << "\n--- ���� ---\n";
    cout << "1. ������ ��� ��� ������\n";
    cout << "2. ³���������� �� ��������\n";
    cout << "3. �������� �����, ���������� �� ������� ������ ������\n";
    cout << "4. �������� ��� � ����\n";
    cout << "5. ������� ��� � �����\n";
    cout << "6. �����\n";
    cout << "������� �����: ";
}

// ������� ��� ��������� ������
void addPerson(Zodiac*& people, int& size) {
    Zodiac newPerson;
    cout << "������ �������: ";
    cin >> newPerson.surname;
    cout << "������ ��'�: ";
    cin >> newPerson.name;
    cout << "������ ���� ������: ";
    cin >> newPerson.zodiac_sign;
    cout << "������ ���� ���������� (����, �����, ��): ";
    cin >> newPerson.birthday[0] >> newPerson.birthday[1] >> newPerson.birthday[2];

    Zodiac* temp = new Zodiac[size + 1];
    for (int i = 0; i < size; ++i) {
        temp[i] = people[i];
    }
    temp[size] = newPerson;
    delete[] people;
    people = temp;
    size++;
}

// ������� ��� ���������� ������ �� ��������� (� ���������� �������)
void sortBySurname(Zodiac* people, int size) {
    sort(people, people + size, [](const Zodiac& a, const Zodiac& b) {
        return a.surname < b.surname;
        });
    cout << "����� ����������� �� ��������.\n";
}

// ������� ��� ������ �����, ���������� �� ������� ������ ������
void displayByZodiacSign(Zodiac* people, int size, const string& zodiacSign) {
    bool found = false;
    for (int i = 0; i < size; ++i) {
        if (people[i].zodiac_sign == zodiacSign) {
            cout << "�������: " << people[i].surname
                << ", ��'�: " << people[i].name
                << ", ���� ������: " << people[i].zodiac_sign
                << ", ���� ����������: " << people[i].birthday[0] << "."
                << people[i].birthday[1] << "." << people[i].birthday[2] << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "���� �����, ���������� �� ��� ������ ������.\n";
    }
}

// ������� ��� ���������� ������ � ����
void saveToFile(Zodiac* people, int size, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "������� �������� ����� ��� ������.\n";
        return;
    }
    for (int i = 0; i < size; ++i) {
        file << people[i].surname << " "
            << people[i].name << " "
            << people[i].zodiac_sign << " "
            << people[i].birthday[0] << " "
            << people[i].birthday[1] << " "
            << people[i].birthday[2] << "\n";
    }
    file.close();
    cout << "��� ��������� � ����.\n";
}

// ������� ��� ���������� ������ � �����
void loadFromFile(Zodiac*& people, int& size, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "������� �������� ����� ��� ����������.\n";
        return;
    }
    size = 0;
    Zodiac temp[100];
    while (file >> temp[size].surname >> temp[size].name >> temp[size].zodiac_sign
        >> temp[size].birthday[0] >> temp[size].birthday[1] >> temp[size].birthday[2]) {
        size++;
    }
    delete[] people;
    people = new Zodiac[size];
    for (int i = 0; i < size; ++i) {
        people[i] = temp[i];
    }
    file.close();
    cout << "��� ������� � �����.\n";

    // ���� �������� �����
    for (int i = 0; i < size; ++i) {
        cout << "�������: " << people[i].surname
            << ", ��'�: " << people[i].name
            << ", ���� ������: " << people[i].zodiac_sign
            << ", ���� ����������: " << people[i].birthday[0] << "."
            << people[i].birthday[1] << "." << people[i].birthday[2] << "\n";
    }
}

// ������� �������
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Zodiac* people = nullptr;
    int size = 0;
    bool running = true;

    while (running) {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            addPerson(people, size);
            break;
        case 2:
            sortBySurname(people, size);
            break;
        case 3: {
            string zodiacSign;
            cout << "������ ���� ������: ";
            cin >> zodiacSign;
            displayByZodiacSign(people, size, zodiacSign);
            break;
        }
        case 4: {
            string filename;
            cout << "������ ��'� ����� ��� ����������: ";
            cin >> filename;
            saveToFile(people, size, filename);
            break;
        }
        case 5: {
            string filename;
            cout << "������ ��'� ����� ��� ����������: ";
            cin >> filename;
            loadFromFile(people, size, filename);
            break;
        }
        case 6:
            running = false;
            break;
        default:
            cout << "������� ����. ��������� �� ���.\n";
        }
    }

    delete[] people;
    return 0;
}
/*
=============
������
���������
���
12 7 1990
=============
������
�����
���
22 8 1995
=============
*/