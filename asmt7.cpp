#include <iostream>
using namespace std;

class StudentRecord {
    int id[20], c[20], n;
    string name[20];
    int age[20], tenthMarks[20], twelfthMarks[20];
    int loc;

public:
    void table();
    void accept();
    void display();
    void search();
    void modify();
    void deleteRecord();
};

void StudentRecord::table() {
    cout << "Enter number of records: ";
    cin >> n;
    cout << "Enter the ID : ";
    for (int i = 0; i < n; i++) {
        cin >> id[i];
        loc = id[i] % 10;
    }
    for (int i = 0; i < 10; i++) {
        c[i] = -2;
    }
}

void StudentRecord::accept() {
    for (int i = 0; i < n; i++) {
        loc = id[i] % 10;
        while (c[loc] != -2) {
            loc = (loc + 1) % 10;
        }
        c[loc] = i;

        cout << "Enter the name of the student: ";
        cin >> name[i];
        cout << "Enter the age of the student: ";
        cin >> age[i];
        cout << "Enter the 10th marks of the student: ";
        cin >> tenthMarks[i];
        cout << "Enter the 12th marks of the student: ";
        cin >> twelfthMarks[i];
    }
}

void StudentRecord::display() {
    cout << "The records are:\n";
    cout << "| ID  | Index | Name   | Age | 10th Marks | 12th Marks | Chain |\n";
    cout << "---------------------------------------------------------------------\n";

    for (int i = 0; i < 10; i++) {
        if (c[i] != -2) {
            int index = c[i];
            int originalLoc = id[index] % 10;
            string chainValue = (originalLoc != i) ? to_string(originalLoc) : "-";

            cout << "| " << id[index] << " | " << index << " | " << name[index]
                 << " | " << age[index] << " | " << tenthMarks[index] << " | "
                 << twelfthMarks[index] << " | " << chainValue << " |\n";
        }
        else {
            cout << "| -  | -     | -      | -   | -          | -          | - |\n";
        }
    }
    cout << "\n";
}

void StudentRecord::search() {
    int k;
    cout << "Enter the Student ID to be searched: ";
    cin >> k;
    loc = k % 10;

    while (c[loc] != -2 && id[c[loc]] != k) {
        loc = (loc + 1) % 10;
        if (loc == k % 10) {
            cout << "Record not found.\n";
            return;
        }
    }
    if (c[loc] == -2) {
        cout << "Record not found.\n";
    } else {
        int index = c[loc];
        cout << "The record is:\n";
        cout << "| ID | Index | Name | Age | 10th Marks | 12th Marks |\n";
        cout << "-----------------------------------------------------\n";
        cout << "| " << id[index] << " | " << index << " | " << name[index] << " | "
             << age[index] << " | " << tenthMarks[index] << " | " << twelfthMarks[index] << " |\n";
    }
    cout << "\n";
}

void StudentRecord::modify() {
    int k;
    cout << "Enter the Student ID to be modified: ";
    cin >> k;
    loc = k % 10;

    while (c[loc] != -2 && id[c[loc]] != k) {
        loc = (loc + 1) % 10;
        if (loc == k % 10) {
            cout << "Record not found.\n";
            return;
        }
    }
    if (c[loc] == -2) {
        cout << "Record not found.\n";
    } else {
        int index = c[loc];
        cout << "Enter the new name of the student: ";
        cin >> name[index];
        cout << "Enter the new age of the student: ";
        cin >> age[index];
        cout << "Enter the new 10th marks of the student: ";
        cin >> tenthMarks[index];
        cout << "Enter the new 12th marks of the student: ";
        cin >> twelfthMarks[index];
    }
}

void StudentRecord::deleteRecord() {
    int k;
    cout << "Enter the Student ID to delete: ";
    cin >> k;
    loc = k % 10;

    while (c[loc] != -2 && id[c[loc]] != k) {
        loc = (loc + 1) % 10;
        if (loc == k % 10) {
            cout << "Record not found.\n";
            return;
        }
    }
    if (c[loc] == -2) {
        cout << "Record not found.\n";
    } else {
        cout << "Record deleted successfully.\n";
        c[loc] = -2; // Mark as empty
    }
}

int main() {
    StudentRecord s;
    int choice;
    do {
        cout << "---Student Scorecard---\n";
        cout << "\n1. Accept the records\n2. Display the records\n3. Search the records\n4. Modify the records\n5. Delete a record\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                s.table();
                s.accept();
                break;
            case 2:
                s.display();
                break;
            case 3:
                s.search();
                break;
            case 4:
                s.modify();
                break;
            case 5:
                s.deleteRecord();
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
                break;
        }
    } while (choice != 6);
    return 0;
}
