Data Sturcture Project

#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For formatting
#include <limits>  // Add this header for numeric_limits

using namespace std;
// Employee class to store employee details
class Employee {
public:
    int id;
    string name;
    string department;
    double salary;
    string address;
    int experience;
    string dateOfJoining;

    Employee(int id, string name, string department, double salary, string address, int experience, string dateOfJoining)
        : id(id), name(name), department(department), salary(salary), address(address), experience(experience), dateOfJoining(dateOfJoining) {}
};

// Employee Management System class
class EmployeeManagementSystem {
private:
    vector<Employee> employees;
    string hrPassword;
    string employeePassword;

    // Helper function to find employee by ID
    int findEmployeeById(int id) {
        for (int i = 0; i < employees.size(); i++) {
            if (employees[i].id == id)
                return i;
        }
        return -1; // Not found
    }

    // Preload 50 employees
    void preloadEmployees() {
    vector<string> Names = {"Aarav", "Vivaan", "Reyansh", "Aditya", "Ishaan", "Kabir", "Arjun", 
                                  "Vihaan", "Dhruv", "Krishna", "Riya", "Ananya", "Isha", "Pooja", 
                                  "Nisha", "Sneha", "Aarti", "Priya", "Aditi", "Kavya", "Anushka", 
                                  "Meera", "Diya", "Sana", "Neha", "Radhika", "Tanya", "Simran", 
                                  "Harsh", "Aryan", "Raghav", "Siddharth", "Shivam", "Abhinav", 
                                  "Varun", "Akash", "Om", "Raj", "Kunal", "Rohit", "Nikhil", 
                                  "Nitesh", "Gaurav", "Saurabh", "Abhishek", "Manish", "Shubham", 
                                  "Rahul", "Ankit", "Vivek", "Sanjay"};

    vector<string> departments = {"Finance", "R&D", "IT", "Sales", "Marketing"};

    int currentYear = 2025; // Replace with actual current year if dynamically calculated

    for (int i = 1; i <= 50; i++) {
        int joiningYear = 2020 + (i % 5); // Generate joining year between 2020-2024
        string joiningDate = "01/01/" + to_string(joiningYear);
        int experience = currentYear - joiningYear; // Calculate experience based on joining year

        employees.push_back(Employee(
            i,
            Names[i - 1],
            departments[(i - 1) % 5], // Rotate through departments
            50000 + i * 1000,           // Base salary increment
            "Address" + to_string(i),
            experience >= 0 ? experience : 0, // Ensure non-negative experience
            joiningDate
        ));
    }
}

public:
    EmployeeManagementSystem() {
        hrPassword = "hr123";          // Default HR password
        employeePassword = "emp123";  // Default Employee password
        preloadEmployees();           // Preload employees
    }
// Authorization for HR
bool authorizeHR() {
    const string hrName = "Priya"; // Predefined HR name
    const int hrId = 1001;           // Predefined HR ID

    string name;
    int id;
    string password;

    cout << "Enter HR Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter HR ID: ";
    cin >> id;

    cout << "Enter HR Password: ";
    cin >> password;

    if (name != hrName) {
        cout << "Invalid HR Name.\n";
        return false;
    }

    if (id != hrId) {
        cout << "Invalid HR ID.\n";
        return false;
    }

    if (password != hrPassword) {
        cout << "Incorrect HR Password.\n";
        return false;
    }

    cout << "HR Authorization successful.\n";
    return true;
}

    // Authorization for Employee
    bool authorizeEmployee() {
        string name;
        int id;
        string password;
        cout << "Enter Employee Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Employee ID: ";
        cin >> id;
        cout << "Enter Employee Password: ";
        cin >> password;
        return password == employeePassword;
    }

// HR Functions
bool isValidNameOrDepartment(const string& input) {
    for (char ch : input) {
        if (!isalpha(ch)) {
            return false; // Return false if any character is not an alphabet
        }
    }
    return true; // All characters are alphabets
}

// HR Functions
void addEmployee() {
    if (employees.size() >= 50) {
        cout << "Employee limit reached for preloaded employees. Adding new employees will require unique details.\n";
    }

    int id, experience, salary;
    string name, department, address, dateOfJoining;

    // Validate Employee ID input
    cout << "Enter Employee ID: ";
    while (!(cin >> id)) {
        cout << "Invalid input! Employee ID should be an integer. Please try again: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
    }

    if (findEmployeeById(id) != -1) {
        cout << "Employee with ID " << id << " already exists!\n";
        return;
    }

    // Validate Name input (only letters)
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    while (!isValidNameOrDepartment(name)) {
        cout << "Invalid Name! Please enter only letters (A-Z or a-z): ";
        getline(cin, name);
    }

    // Validate Department input (only letters)
    cout << "Enter Department: ";
    getline(cin, department);
    while (!isValidNameOrDepartment(department)) {
        cout << "Invalid Department! Please enter only letters (A-Z or a-z): ";
        getline(cin, department);
    }

    // Validate Salary input (integer)
    cout << "Enter Salary: ";
    while (!(cin >> salary)) {
        cout << "Invalid input! Salary should be an integer. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Validate Address input (alphanumeric, no restrictions)
    cout << "Enter Address: ";
    cin.ignore();
    getline(cin, address); // No validation here, accept all characters

    // Validate Experience input (integer)
    cout << "Enter Experience (in years): ";
    while (!(cin >> experience)) {
        cout << "Invalid input! Experience should be an integer. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Validate Date of Joining input (string, no specific validation here)
    cout << "Enter Date of Joining (DD/MM/YYYY): ";
    cin.ignore();
    getline(cin, dateOfJoining); // Accept the date as a string

    // Check for unique name or address (example of additional uniqueness check)
    for (const auto& emp : employees) {
        if (emp.name == name && emp.address == address) {
            cout << "Employee with the same name and address already exists. Please provide unique details.\n";
            return;
        }
    }

    employees.push_back(Employee(id, name, department, salary, address, experience, dateOfJoining));
    cout << "Employee added successfully!\n";
}
    // Delete an employee
void deleteEmployee() {
    int id;
    
    // Validate Employee ID input (integer only)
    cout << "Enter Employee ID to delete: ";
    while (!(cin >> id)) {
        cout << "Invalid input! Employee ID should be an integer. Please try again: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
    }

    int index = findEmployeeById(id);
    if (index == -1) {
        cout << "Employee with ID " << id << " not found!\n";
        return;
    }

    employees.erase(employees.begin() + index);
    cout << "Employee deleted successfully!\n";
}

// View all employees
void viewAllEmployees() {
    if (employees.empty()) {
        cout << "No employees to display!\n";
        return;
    }

    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Department"
         << setw(10) << "Salary (₹)" << setw(15) << "Experience" << setw(15) << "Joining Date" << endl;
    cout << string(80, '-') << endl;

    double totalSalary = 0; // For calculating total salary

    for (const auto& emp : employees) {
        cout << left << setw(10) << emp.id << setw(20) << emp.name << setw(15) << emp.department
             << "₹" << setw(9) << emp.salary << setw(15) << emp.experience << setw(15) << emp.dateOfJoining << endl;

        totalSalary += emp.salary; // Add each employee's salary
    }

    cout << string(80, '-') << endl;
    cout << "Total Salary Paid to All Employees: ₹" << totalSalary << endl;
}
// Search an employee by ID
void searchEmployee() {
    int id;
    
    // Validate Employee ID input (integer only)
    cout << "Enter Employee ID to search: ";
    while (!(cin >> id)) {
        cout << "Invalid input! Employee ID should be an integer. Please try again: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
    }

    int index = findEmployeeById(id);
    if (index == -1) {
        cout << "Employee with ID " << id << " not found!\n";
        return;
    }

    const auto& emp = employees[index];
    cout << "Employee Details:\n";
    cout << "ID: " << emp.id << "\nName: " << emp.name << "\nDepartment: " << emp.department
         << "\nSalary: " << emp.salary << "\nAddress: " << emp.address
         << "\nExperience: " << emp.experience << " years\nDate of Joining: " << emp.dateOfJoining << endl;
}


bool isAlphabetic(const string& str) {
    for (char c : str) {
        if (!isalpha(c)) {
            return false; // If any character is not alphabetic, return false
        }
    }
    return true;
}

bool isValidIntegerInput(int& input) {
    // To ensure that the input is valid integer
    if (!(cin >> input)) {
        cout << "Invalid input! Please enter an integer value.\n";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        return false;
    }
    return true;
}

// Modify employee details
void modifyEmployee() {
    int id;

    // Validate Employee ID input (integer only)
    cout << "Enter Employee ID to modify: ";
    while (!isValidIntegerInput(id)) {
        cout << "Please try again: ";
    }

    int index = findEmployeeById(id);
    if (index == -1) {
        cout << "Employee with ID " << id << " not found!\n";
        return;
    }

    cout << "Modify Details for Employee ID " << id << ":\n";
    cout << "1. Department\n2. Salary\n3. Address\n4. Experience\n"; // Exclude Name and Date of Joining
    int choice;
    cout << "Enter your choice: ";
    while (!isValidIntegerInput(choice)) {
        cout << "Invalid input! Please enter a valid choice: ";
    }

    switch (choice) {
    case 1: { // Modify Department
        string newDepartment;
        cout << "Enter new Department (alphabetic only): ";
        cin.ignore(); // To clear the input buffer before using getline
        getline(cin, newDepartment);

        // Validate if the department contains only alphabetic characters
        if (isAlphabetic(newDepartment)) {
            employees[index].department = newDepartment;
        } else {
            cout << "Invalid input! Department must only contain alphabetic characters.\n";
        }
        break;
    }
    case 2: { // Modify Salary
        int newSalary;
        cout << "Enter new Salary (integer only): ";
        while (!isValidIntegerInput(newSalary)) {
            cout << "Please enter a valid salary: ";
        }
        employees[index].salary = newSalary;
        break;
    }
    case 3: { // Modify Address (alphanumeric allowed)
        string newAddress;
        cout << "Enter new Address: ";
        cin.ignore();
        getline(cin, newAddress);
        employees[index].address = newAddress;
        break;
    }
    case 4: { // Modify Experience
        int newExperience;
        cout << "Enter new Experience (in years, integer only): ";
        while (!isValidIntegerInput(newExperience)) {
            cout << "Please enter a valid experience: ";
        }
        employees[index].experience = newExperience;
        break;
    }
    default:
        cout << "Invalid choice! Modification failed.\n";
        return;
    }

    cout << "Employee details updated successfully!\n";
}
    // Employee Functions

    // View own details
    void viewOwnDetails() {
        int id;
        cout << "Enter your Employee ID: ";
        cin >> id;

        int index = findEmployeeById(id);
        if (index == -1) {
            cout << "Employee with ID " << id << " not found!\n";
            return;
        }

        const auto& emp = employees[index];
        cout << "Your Details:\n";
        cout << "ID: " << emp.id << "\nName: " << emp.name << "\nDepartment: " << emp.department
             << "\nSalary: " << emp.salary << "\nAddress: " << emp.address
             << "\nExperience: " << emp.experience << " years\nDate of Joining: " << emp.dateOfJoining << endl;
    }

    // Check salary
    void checkSalary() {
        int id;
        cout << "Enter your Employee ID: ";
        cin >> id;

        int index = findEmployeeById(id);
        if (index == -1) {
            cout << "Employee with ID " << id << " not found!\n";
            return;
        }

        const auto& emp = employees[index];
        cout << "Your Salary: " << emp.salary << "\n";
    }

    // Update own details
    void updateOwnDetails() {
        int id;
        cout << "Enter your Employee ID: ";
        cin >> id;

        int index = findEmployeeById(id);
        if (index == -1) {
            cout << "Employee with ID " << id << " not found!\n";
            return;
        }

        cout << "Update Your Details:\n";
        cout << "1. Address\n2. Experience\n";
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter new Address: ";
            cin.ignore();
            getline(cin, employees[index].address);
            break;
        }
        case 2: {
            cout << "Enter new Experience (in years): ";
            cin >> employees[index].experience;
            break;
        }
        default:
            cout << "Invalid choice!\n";
            return;
        }

        cout << "Your details updated successfully!\n";
    }
};

int main() {
    EmployeeManagementSystem ems;

    int profileChoice;
    do {
        cout << "\nSelect Profile:\n1. HR\n2. Employee\n3. Exit\nEnter your choice: ";
        cin >> profileChoice;

        if (profileChoice == 1) {
            if (!ems.authorizeHR()) {
                cout << "Authorization failed! Returning to profile selection...\n";
                continue; // back to profile selection
            }

            int choice;
            do {
                cout << "\nHR Menu:\n";
                cout << "1. Add Employee\n2. Delete Employee\n3. View All Employees\n4. Search Employee\n5. Modify Employee\n6. Logout\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    ems.addEmployee();
                    break;
                case 2:
                    ems.deleteEmployee();
                    break;
                case 3:
                    ems.viewAllEmployees();
                    break;
                case 4:
                    ems.searchEmployee();
                    break;
                case 5:
                    ems.modifyEmployee();
                    break;
                case 6:
                    cout << "Logging out HR. Returning to profile selection...\n";
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
                }
            } while (choice != 6);

        } else if (profileChoice == 2) {
            if (!ems.authorizeEmployee()) {
                cout << "Authorization failed! Returning to profile selection...\n";
                continue; // back to profile selection
            }

            int choice;
            do {
                cout << "\nEmployee Menu:\n";
                cout << "1. View Own Details\n2. Check Salary\n3. Update Address/Experience\n4. Logout\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    ems.viewOwnDetails();
                    break;
                case 2:
                    ems.checkSalary();
                    break;
                case 3:
                    ems.updateOwnDetails();
                    break;
                case 4:
                    cout << "Logging out Employee. Returning to profile selection...\n";
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
                }
            } while (choice != 4);

        } else if (profileChoice == 3) {
            cout << "Exiting the program. Goodbye!\n";
        } else {
            cout << "Invalid profile choice! Please try again.\n";
        }

    } while (profileChoice != 3);

    return 0;
}
