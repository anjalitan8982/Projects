#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

// Define a structure to store student details
struct Student {
    string name;
    float height;
};

// Function to handle input validation for floating-point numbers
float getValidFloatInput(const string& prompt) {
    float input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail() || input <= 0) {  // Added non-negative check
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a valid positive number.\n";
        } else {
            break;
        }
    }
    return input;
}

// Linear Search function
int linearSearch(const vector<Student>& students, float heightThreshold) {
    int iterations = 0;
    bool found = false;
    for (int i = 0; i < students.size(); ++i) {
        iterations++;
        if (students[i].height > heightThreshold) {
            cout << students[i].name << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No students found with height greater than " << heightThreshold << " feet.\n";
    }
    return iterations;
}

// Binary Search function (requires sorted list)
int binarySearch(const vector<Student>& students, float heightThreshold) {
    int left = 0, right = students.size() - 1;
    int iterations = 0;
    int firstIndex = -1;

    while (left <= right) {
        iterations++;
        int mid = left + (right - left) / 2;
        if (students[mid].height > heightThreshold) {
            firstIndex = mid; // Possible answer, but check left part for earlier
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (firstIndex != -1) {
        for (int i = firstIndex; i < students.size(); ++i) {
            cout << students[i].name << endl;
        }
    } else {
        cout << "No students found with height greater than " << heightThreshold << " feet.\n";
    }
    return iterations;
}

// Function to sort students by height
bool compareHeight(const Student& s1, const Student& s2) {
    return s1.height < s2.height;
}

int main() {
    vector<Student> students;
    int n;

    cout << "Enter number of students: ";
    while (true) {
        cin >> n;
        if (cin.fail() || n <= 0) {  // Added positive integer check
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a valid positive integer.\n";
        } else {
            break;
        }
    }

    // Collect student details
    for (int i = 0; i < n; ++i) {
        Student student;
        cout << "\nEnter name of student " << i + 1 << ": ";
        cin >> student.name;
        student.height = getValidFloatInput("Enter height (in feet) of " + student.name + ": ");
        students.push_back(student);
    }

    // Apply Linear Search
    float heightThreshold = 5.0;
    cout << "\nPerforming Linear Search...\n";
    cout << "Students taller than " << heightThreshold << " feet:\n";
    int linearSearchIterations = linearSearch(students, heightThreshold);
    cout << "Linear Search completed in " << linearSearchIterations << " iterations.\n";

    // Apply Binary Search after sorting
    sort(students.begin(), students.end(), compareHeight);
    cout << "\nPerforming Binary Search...\n";
    cout << "Students taller than " << heightThreshold << " feet:\n";
    int binarySearchIterations = binarySearch(students, heightThreshold);
    cout << "Binary Search completed in " << binarySearchIterations << " iterations.\n";

    return 0;
}
