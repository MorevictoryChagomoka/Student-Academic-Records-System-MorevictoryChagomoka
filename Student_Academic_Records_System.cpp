#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// ---------------- STUDENT STRUCT ----------------
struct Student {
    int id;
    string name;
    vector<string> courses;
    vector<float> marks;
};

// Global student list
vector<Student> students;

// ---------------- FIND STUDENT ----------------
int findStudentById(int id) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

// ---------------- ADD STUDENT ----------------
void addStudent() {
    Student s;

    cout << "Enter Student ID: ";
    cin >> s.id;
    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, s.name);

    students.push_back(s);

    cout << "Student added successfully!\n";
}

// ---------------- EDIT STUDENT ----------------
void editStudent() {
    int id;
    cout << "Enter Student ID to edit: ";
    cin >> id;

    int index = findStudentById(id);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    cin.ignore();
    cout << "Enter new name: ";
    getline(cin, students[index].name);

    cout << "Student updated successfully!\n";
}

// ---------------- DELETE STUDENT ----------------
void deleteStudent() {
    int id;
    cout << "Enter Student ID to delete: ";
    cin >> id;

    int index = findStudentById(id);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    students.erase(students.begin() + index);

    cout << "Student deleted successfully!\n";
}

// ---------------- REGISTER COURSE ----------------
void registerCourse() {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    int index = findStudentById(id);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    string course;
    cin.ignore();
    cout << "Enter Course Name: ";
    getline(cin, course);

    students[index].courses.push_back(course);
    students[index].marks.push_back(0);

    cout << "Course registered successfully!\n";
}

// ---------------- ENTER MARKS ----------------
void enterMarks() {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    int index = findStudentById(id);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    for (int i = 0; i < students[index].courses.size(); i++) {
        cout << "Enter marks for " << students[index].courses[i] << ": ";
        cin >> students[index].marks[i];
    }

    cout << "Marks updated successfully!\n";
}

// ---------------- CALCULATE GPA ----------------
float calculateGPA(Student s) {
    if (s.courses.size() == 0) {
        return 0.0;
    }

    float totalPoints = 0;

    for (int i = 0; i < s.marks.size(); i++) {
        float mark = s.marks[i];

        if (mark >= 80) totalPoints += 4.0;
        else if (mark >= 70) totalPoints += 3.0;
        else if (mark >= 60) totalPoints += 2.0;
        else if (mark >= 50) totalPoints += 1.0;
        else totalPoints += 0.0;
    }

    return totalPoints / s.marks.size();
}

// ---------------- GENERATE TRANSCRIPT ----------------
void generateTranscript() {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    int index = findStudentById(id);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    Student s = students[index];

    float gpa = calculateGPA(s);

    string filename = s.name + "_transcript.txt";
    ofstream file(filename);

    file << "----- TRANSCRIPT -----\n";
    file << "Student ID: " << s.id << "\n";
    file << "Name: " << s.name << "\n\n";

    file << "Courses and Marks:\n";
    for (int i = 0; i < s.courses.size(); i++) {
        file << s.courses[i] << " : " << s.marks[i] << "\n";
    }

    file << "\nGPA: " << gpa << "\n";

    file.close();

    cout << "Transcript saved to file: " << filename << endl;
}

// ---------------- MENU ----------------
void menu() {
    int choice;

    do {
        cout << "\n==== STUDENT ACADEMIC RECORD SYSTEM ====\n";
        cout << "1. Add Student\n";
        cout << "2. Edit Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Register Course\n";
        cout << "5. Enter Marks\n";
        cout << "6. Generate Transcript\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: editStudent(); break;
            case 3: deleteStudent(); break;
            case 4: registerCourse(); break;
            case 5: enterMarks(); break;
            case 6: generateTranscript(); break;
            case 0: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 0);
}

// ---------------- MAIN ----------------
int main() {
    menu();
    return 0;
}