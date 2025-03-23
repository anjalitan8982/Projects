#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <regex>
#include <chrono>  // For system clock and current date
#include <iomanip> // For formatting date output
#include <map>     // For grouping students by room number
using namespace std;

// Student Structure
struct Student {
    string name;
    string id;
    string email;
    string phone;
    string password;
    string department;
    string gender;
    int year;

    int roomType; // 1: Single, 2: Double, 3: Triple
    string roommateDept;
    int roommateYear; // Changed to int
    bool wantsCooler;
    bool randomAllocation;
    string specialRequests;
    string joiningDate;
    int roomNumber; // New field for room number
};

vector<Student> students = {
    {"Alice Johnson", "S001", "alice@example.com", "9876543210", "pass123", "Engineering", "Female", 2, 1, "Management", 2, true, false, "Near window", "2025-01-10"},
    {"Bob Smith", "S002", "bob@example.com", "9876543211", "pass234", "Design", "Male", 3, 2, "Law", 3, false, true, "Quiet environment", "2025-01-12"},
    {"Charlie Brown", "S003", "charlie@example.com", "9876543212", "pass345", "Management", "Male", 1, 3, "Engineering", 1, true, false, "Allergic to dust", "2025-01-15"},
    {"David White", "S004", "david@example.com", "9876543213", "pass456", "Law", "Male", 2, 1, "Design", 2, false, true, "Prefers morning study", "2025-01-20"},
    {"Emma Davis", "S005", "emma@example.com", "9876543214", "pass567", "Other", "Female", 3, 2, "Management", 3, true, false, "Vegan diet", "2025-01-22"},
    {"Frank Wilson", "S006", "frank@example.com", "9876543215", "pass678", "Engineering", "Male", 2, 3, "Design", 2, false, false, "Near library", "2025-02-01"},
    {"Grace Lee", "S007", "grace@example.com", "9876543216", "pass789", "Design", "Female", 3, 1, "Law", 1, true, true, "Quiet room", "2025-02-05"},
    {"Henry Brown", "S008", "henry@example.com", "9876543217", "pass890", "Management", "Male", 1, 2, "Engineering", 3, false, false, "No special requests", "2025-02-10"},
    {"Isabella Clark", "S009", "isabella@example.com", "9876543218", "pass901", "Law", "Female", 2, 3, "Design", 2, true, true, "Near cafeteria", "2025-02-15"},
    {"Jack Evans", "S010", "jack@example.com", "9876543219", "pass012", "Other", "Male", 3, 1, "Management", 1, false, false, "Allergic to peanuts", "2025-02-20"},
    {"Katherine Hall", "S011", "katherine@example.com", "9876543220", "pass123", "Engineering", "Female", 2, 2, "Law", 2, true, false, "Near gym", "2025-03-01"},
    {"Liam Lewis", "S012", "liam@example.com", "9876543221", "pass234", "Design", "Male", 1, 3, "Engineering", 3, false, true, "No special requests", "2025-03-05"},
    {"Mia Walker", "S013", "mia@example.com", "9876543222", "pass345", "Management", "Female", 3, 1, "Design", 1, true, false, "Near window", "2025-03-10"},
    {"Noah Young", "S014", "noah@example.com", "9876543223", "pass456", "Law", "Male", 2, 2, "Management", 2, false, true, "Quiet environment", "2025-03-15"},
    {"Olivia Allen", "S015", "olivia@example.com", "9876543224", "pass567", "Other", "Female", 1, 3, "Engineering", 3, true, false, "Vegan diet", "2025-03-20"},
    {"Parker Scott", "S016", "parker@example.com", "9876543225", "pass678", "Engineering", "Male", 2, 1, "Design", 1, false, false, "Near library", "2025-04-01"},
    {"Quinn Adams", "S017", "quinn@example.com", "9876543226", "pass789", "Design", "Female", 3, 2, "Law", 2, true, true, "Quiet room", "2025-04-05"},
    {"Ryan Green", "S018", "ryan@example.com", "9876543227", "pass890", "Management", "Male", 1, 3, "Engineering", 3, false, false, "No special requests", "2025-04-10"},
    {"Sophia King", "S019", "sophia@example.com", "9876543228", "pass901", "Law", "Female", 2, 1, "Design", 1, true, true, "Near cafeteria", "2025-04-15"},
    {"Thomas Wright", "S020", "thomas@example.com", "9876543229", "pass012", "Other", "Male", 3, 2, "Management", 2, false, false, "Allergic to peanuts", "2025-04-20"},
    {"Uma Harris", "S021", "uma@example.com", "9876543230", "pass123", "Engineering", "Female", 1, 3, "Law", 3, true, false, "Near gym", "2025-05-01"},
    {"Victor Martinez", "S022", "victor@example.com", "9876543231", "pass234", "Design", "Male", 2, 1, "Engineering", 1, false, true, "No special requests", "2025-05-05"},
    {"Wendy Nelson", "S023", "wendy@example.com", "9876543232", "pass345", "Management", "Female", 3, 2, "Design", 2, true, false, "Near window", "2025-05-10"},
    {"Xander Carter", "S024", "xander@example.com", "9876543233", "pass456", "Law", "Male", 1, 3, "Management", 3, false, true, "Quiet environment", "2025-05-15"},
    {"Yara Perez", "S025", "yara@example.com", "9876543234", "pass567", "Other", "Female", 2, 1, "Engineering", 1, true, false, "Vegan diet", "2025-05-20"},
    {"Zane Roberts", "S026", "zane@example.com", "9876543235", "pass678", "Engineering", "Male", 3, 2, "Design", 2, false, false, "Near library", "2025-06-01"},
    {"Ava Turner", "S027", "ava@example.com", "9876543236", "pass789", "Design", "Female", 1, 3, "Law", 3, true, true, "Quiet room", "2025-06-05"},
    {"Benjamin Phillips", "S028", "benjamin@example.com", "9876543237", "pass890", "Management", "Male", 2, 1, "Engineering", 1, false, false, "No special requests", "2025-06-10"},
    {"Chloe Campbell", "S029", "chloe@example.com", "9876543238", "pass901", "Law", "Female", 3, 2, "Design", 2, true, true, "Near cafeteria", "2025-06-15"},
    {"Daniel Parker", "S030", "daniel@example.com", "9876543239", "pass012", "Other", "Male", 1, 3, "Management", 3, false, false, "Allergic to peanuts", "2025-06-20"},
    {"Ella Evans", "S031", "ella@example.com", "9876543240", "pass123", "Engineering", "Female", 2, 1, "Law", 1, true, false, "Near gym", "2025-07-01"},
    {"Finn Mitchell", "S032", "finn@example.com", "9876543241", "pass234", "Design", "Male", 3, 2, "Engineering", 2, false, true, "No special requests", "2025-07-05"},
    {"Grace Roberts", "S033", "grace@example.com", "9876543242", "pass345", "Management", "Female", 1, 3, "Design", 3, true, false, "Near window", "2025-07-10"},
    {"Henry Turner", "S034", "henry@example.com", "9876543243", "pass456", "Law", "Male", 2, 1, "Management", 1, false, true, "Quiet environment", "2025-07-15"},
    {"Isla Phillips", "S035", "isla@example.com", "9876543244", "pass567", "Other", "Female", 3, 2, "Engineering", 2, true, false, "Vegan diet", "2025-07-20"},
    {"Jack Campbell", "S036", "jack@example.com", "9876543245", "pass678", "Engineering", "Male", 1, 3, "Design", 3, false, false, "Near library", "2025-08-01"},
    {"Katie Parker", "S037", "katie@example.com", "9876543246", "pass789", "Design", "Female", 2, 1, "Law", 1, true, true, "Quiet room", "2025-08-05"},
    {"Liam Evans", "S038", "liam@example.com", "9876543247", "pass890", "Management", "Male", 3, 2, "Engineering", 2, false, false, "No special requests", "2025-08-10"},
    {"Mia Mitchell", "S039", "mia@example.com", "9876543248", "pass901", "Law", "Female", 1, 3, "Design", 3, true, true, "Near cafeteria", "2025-08-15"},
    {"Noah Roberts", "S040", "noah@example.com", "9876543249", "pass012", "Other", "Male", 2, 1, "Management", 1, false, false, "Allergic to peanuts", "2025-08-20"},
    {"Olivia Turner", "S041", "olivia@example.com", "9876543250", "pass123", "Engineering", "Female", 3, 2, "Law", 2, true, false, "Near gym", "2025-09-01"},
    {"Parker Phillips", "S042", "parker@example.com", "9876543251", "pass234", "Design", "Male", 1, 3, "Engineering", 3, false, true, "No special requests", "2025-09-05"},
    {"Quinn Campbell", "S043", "quinn@example.com", "9876543252", "pass345", "Management", "Female", 2, 1, "Design", 1, true, false, "Near window", "2025-09-10"},
    {"Ryan Parker", "S044", "ryan@example.com", "9876543253", "pass456", "Law", "Male", 3, 2, "Management", 2, false, true, "Quiet environment", "2025-09-15"},
    {"Sophia Evans", "S045", "sophia@example.com", "9876543254", "pass567", "Other", "Female", 1, 3, "Engineering", 3, true, false, "Vegan diet", "2025-09-20"},
    {"Thomas Mitchell", "S046", "thomas@example.com", "9876543255", "pass678", "Engineering", "Male", 2, 1, "Design", 1, false, false, "Near library", "2025-10-01"},
    {"Uma Roberts", "S047", "uma@example.com", "9876543256", "pass789", "Design", "Female", 3, 2, "Law", 2, true, true, "Quiet room", "2025-10-05"},
    {"Victor Turner", "S048", "victor@example.com", "9876543257", "pass890", "Management", "Male", 1, 3, "Engineering", 3, false, false, "No special requests", "2025-10-10"},
    {"Wendy Phillips", "S049", "wendy@example.com", "9876543258", "pass901", "Law", "Female", 2, 1, "Design", 1, true, true, "Near cafeteria", "2025-10-15"},
    {"Xander Campbell", "S050", "xander@example.com", "9876543259", "pass012", "Other", "Male", 3, 2, "Management", 2, false, false, "Allergic to peanuts", "2025-10-20"}
};

// 🌟 **Admin Panel Class**
class AdminPanel {
private:
    vector<Student>* students;
    bool isAdmin = false;

public:
    AdminPanel(vector<Student>& studentList) {
        students = &studentList;
    }

    void adminLogin() {
        string user, pass;
        cout << "\nEnter Admin Username: ";
        cin >> user;
        cout << "Enter Password: ";
        cin >> pass;

        if (user == "admin" && pass == "admin123") {
            isAdmin = true;
            cout << "\n✅ Admin Login Successful!\n";
            adminMenu();
        } else {
            cout << "❌ Invalid Admin Credentials!\n";
        }
    }

    void adminMenu() {
        int choice;
        do {
            cout << "\n--- Admin Menu ---\n";
            cout << "1. View All Students\n2. Allocate Rooms\n3. View Room Allocations\n4. View Chart\n5. View Vacancy Chart\n6. Logout\nEnter choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "❌ Invalid input! Please enter a number.\n";
                continue;
            }

            switch (choice) {
                case 1:
                    viewAllStudents();
                    break;
                case 2:
                    allocateRooms();
                    break;
                case 3:
                    viewRoomAllocations();
                    break;
                case 4:
                    viewChart();
                    break;
                case 5:
                    vacancyChart();
                    break;
                case 6:
                    logout();
                    return;
                default:
                    cout << "❌ Invalid Choice! Try Again.\n";
            }
        } while (choice != 6);
    }

    void viewAllStudents() {
        if (!isAdmin) {
            cout << "⚠️ Only Admin Can View This!\n";
            return;
        }

        cout << "\n--- All Students ---\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Department" << setw(10) << "Year" << endl;
        cout << "-----------------------------------------------------\n";

        for (auto &s : *students) {
            cout << left << setw(10) << s.id << setw(20) << s.name << setw(15) << s.department << setw(10) << s.year << endl;
        }
    }

    void allocateRooms() {
    if (!isAdmin) {
        cout << "⚠️ Only Admin Can Allocate Rooms!\n";
        return;
    }

    // Sort students based on room type first, then by name (or admission number)
    sort(students->begin(), students->end(), [](const Student &a, const Student &b) {
        if (a.roomType == b.roomType) 
            return a.name < b.name; // Secondary sorting by name
        return a.roomType < b.roomType; // Primary sorting by room type
    });

    // Initialize room counters and occupancy trackers
    int singleRoomCounter = 1;
    int doubleRoomCounter = 101;
    int tripleRoomCounter = 201;
    map<int, int> roomOccupancy; // Track number of students per room

    // Allocate rooms based on sorted list
    for (auto &s : *students) {
        if (s.roomType == 1) { // Single room
            s.roomNumber = singleRoomCounter++;
        } else if (s.roomType == 2) { // Double room
            if (roomOccupancy[doubleRoomCounter] < 2) {
                s.roomNumber = doubleRoomCounter;
                roomOccupancy[doubleRoomCounter]++;
            } else {
                doubleRoomCounter++;
                s.roomNumber = doubleRoomCounter;
                roomOccupancy[doubleRoomCounter] = 1;
            }
        } else if (s.roomType == 3) { // Triple room
            if (roomOccupancy[tripleRoomCounter] < 3) {
                s.roomNumber = tripleRoomCounter;
                roomOccupancy[tripleRoomCounter]++;
            } else {
                tripleRoomCounter++;
                s.roomNumber = tripleRoomCounter;
                roomOccupancy[tripleRoomCounter] = 1;
            }
        }
    }

    cout << "\n✅ Rooms Allocated Successfully (Sorted Allocation)!\n";
}

    void viewRoomAllocations() {
    if (!isAdmin) {
        cout << "⚠️ Only Admin Can View Room Allocations!\n";
        return;
    }

    cout << "\n--- Room Allocations ---\n";

    // Create a map to group students by room number
    map<int, vector<Student*>> roomMap;

    // Populate the map with students grouped by room number
    for (auto &s : *students) {
        if (s.roomNumber != 0) { // Only consider students with allocated rooms
            roomMap[s.roomNumber].push_back(&s);
        }
    }

    // Display students grouped by room number
    for (auto &room : roomMap) {
        cout << "\n=== Room No. " << room.first << " ===\n";
        cout << left << setw(20) << "Name" << setw(15) << "Department" << setw(10) << "Year" << endl;
        cout << "-----------------------------------------------------\n";

        for (auto &student : room.second) {
            cout << left << setw(20) << student->name << setw(15) << student->department << setw(10) << student->year << endl;
        }
    }
}

    void viewChart() {
        if (!isAdmin) {
            cout << "⚠️ Only Admin Can View This!\n";
            return;
        }

        cout << "\n--- Hostel Allocation Chart ---\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Room" 
             << setw(10) << "Room No." << setw(20) << "Roommate Dept." << setw(10) << "Year" << endl;
        cout << "---------------------------------------------------------------\n";

        for (auto &s : *students) {
            cout << left << setw(10) << s.id << setw(20) << s.name << setw(10) << s.roomType 
                 << setw(10) << s.roomNumber << setw(20) << s.roommateDept << setw(10) << s.roommateYear << endl;
        }
    }

    void vacancyChart() {
        if (!isAdmin) {
            cout << "⚠️ Only Admin Can View This!\n";
            return;
        }

        // Initialize counters for each room type
        int singleRooms = 0, doubleRooms = 0, tripleRooms = 0;

        // Count the number of students in each room type
        for (auto &s : *students) {
            if (s.roomType == 1) singleRooms++;
            else if (s.roomType == 2) doubleRooms++;
            else if (s.roomType == 3) tripleRooms++;
        }

        // Total rooms available (assuming fixed numbers)
        const int TOTAL_SINGLE_ROOMS = 30;
        const int TOTAL_DOUBLE_ROOMS = 50;
        const int TOTAL_TRIPLE_ROOMS = 20;

        // Calculate available rooms
        int availableSingleRooms = TOTAL_SINGLE_ROOMS - singleRooms;
        int availableDoubleRooms = TOTAL_DOUBLE_ROOMS - doubleRooms;
        int availableTripleRooms = TOTAL_TRIPLE_ROOMS - tripleRooms;

        // Display the vacancy chart
        cout << "\n--- Vacancy Chart ---\n";
        cout << left << setw(15) << "Room Type" << setw(15) << "Total Rooms" << setw(15) << "Occupied" << setw(15) << "Available" << endl;
        cout << "---------------------------------------------------------------\n";
        cout << left << setw(15) << "Single" << setw(15) << TOTAL_SINGLE_ROOMS << setw(15) << singleRooms << setw(15) << availableSingleRooms << endl;
        cout << left << setw(15) << "Double" << setw(15) << TOTAL_DOUBLE_ROOMS << setw(15) << doubleRooms << setw(15) << availableDoubleRooms << endl;
        cout << left << setw(15) << "Triple" << setw(15) << TOTAL_TRIPLE_ROOMS << setw(15) << tripleRooms << setw(15) << availableTripleRooms << endl;
    }

    void logout() {
        if (isAdmin) {
            cout << "\n🔓 Admin Logged out successfully.\n";
            isAdmin = false;
        }
    }
};

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void setJoiningDate(Student &student) {
    string date;
    regex datePattern(R"(\d{4}-\d{2}-\d{2})"); // Format: YYYY-MM-DD

    // Get today's date
    auto now = chrono::system_clock::now();
    time_t today_time = chrono::system_clock::to_time_t(now);
    tm today_tm = *localtime(&today_time);

    cout << "Enter Joining Date (YYYY-MM-DD, e.g., 2025-12-31): ";
    while (true) {
        cin >> date;

        if (regex_match(date, datePattern)) {
            // Parse the entered date
            tm entered_tm = {};
            istringstream dateStream(date);
            dateStream >> get_time(&entered_tm, "%Y-%m-%d");

            if (dateStream.fail()) {
                cout << "Invalid date! Please enter a valid date in YYYY-MM-DD format (e.g., 2025-12-31): ";
                continue;
            }

            // Convert both dates to time_t for comparison
            time_t entered_time = mktime(&entered_tm);
            time_t today_time = mktime(&today_tm);

            // Check if the entered date is in the past
            if (entered_time < today_time) {
                cout << "The date cannot be in the past! Please enter a future date (e.g., 2025-12-31): ";
            } else {
                student.joiningDate = date;
                cout << "Joining date set successfully!\n";
                break;
            }
        } else {
            cout << "Invalid format! Please enter the date in YYYY-MM-DD format (e.g., 2025-12-31): ";
        }
    }
}

void studentPortal();
void adminPortal();

int main() {
    int choice;
    do {
        cout << "\n===== Hostel Room Allocation System =====\n";
        cout << "1. Student Login\n2. Admin Login\n3. Exit\nEnter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            clearInputBuffer();
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                clearInputBuffer();
                studentPortal();
                break;
            case 2:
                clearInputBuffer();
                adminPortal();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}

void studentPortal() {
    string studentID, password;
    int attempts = 3;

    while (attempts > 0) {
        cout << "Enter your Student ID: ";
        cin >> studentID;
        cout << "Enter Password: ";
        cin >> password;

        for (auto &student : students) {
            if (student.id == studentID && student.password == password) {
                cout << "\nWelcome, " << student.name << "!\n";
                int choice;
                do {
                    cout << "\n===== Student Portal =====\n";
                    cout << "1. View Student Profile\n2. Set Preferences\n3. Set Joining Date\n4. View Preferences\n5. Logout\nEnter your choice: ";
                    cin >> choice;

                    if (cin.fail()) {
                        clearInputBuffer();
                        cout << "Invalid input! Please enter a number.\n";
                        continue;
                    }

                    switch (choice) {
                        case 1:
                            cout << "\n===== Student Profile =====\n";
                            cout << "Name: " << student.name << "\n";
                            cout << "Student ID: " << student.id << "\n";
                            cout << "Email: " << student.email << "\n";
                            cout << "Phone: " << student.phone << "\n";
                            cout << "Department: " << student.department << "\n";
                            cout << "Room Number: " << (student.roomNumber ? to_string(student.roomNumber) : "Not Allocated") << "\n";
                            break;
                        case 2:
                            cout << "Enter Room Type (1: Single, 2: Double, 3: Triple): ";
                            while (!(cin >> student.roomType) || student.roomType < 1 || student.roomType > 3) {
                                clearInputBuffer();
                                cout << "Invalid input! Please enter 1, 2, or 3: ";
                            }
                            cout << "Enter Roommate's Department: ";
                            cin >> student.roommateDept;
                            cout << "Enter Roommate's Year (1-4): ";
                            while (!(cin >> student.roommateYear) || student.roommateYear < 1 || student.roommateYear > 4) {
                                clearInputBuffer();
                                cout << "Invalid input! Please enter a year between 1 and 4: ";
                            }
                            cout << "Enter Special Requests: ";
                            cin.ignore();
                            getline(cin, student.specialRequests);
                            cout << "Random Selection (1: Yes, 0: No): ";
                            while (!(cin >> student.randomAllocation) || (student.randomAllocation != 0 && student.randomAllocation != 1)) {
                                clearInputBuffer();
                                cout << "Invalid input! Please enter 0 or 1: ";
                            }
                            cout << "Cooler Preference (1: Yes, 0: No): ";
                            while (!(cin >> student.wantsCooler) || (student.wantsCooler != 0 && student.wantsCooler != 1)) {
                                clearInputBuffer();
                                cout << "Invalid input! Please enter 0 or 1: ";
                            }
                            break;
                        case 3:
                            setJoiningDate(student);
                            break;
                        case 4:
                            cout << "\n===== Preferences =====\n";
                            cout << "Room Type: " << student.roomType << "\n";
                            cout << "Roommate Department: " << student.roommateDept << "\n";
                            cout << "Roommate Year: " << student.roommateYear << "\n";
                            cout << "Wants Cooler: " << (student.wantsCooler ? "Yes" : "No") << "\n";
                            cout << "Random Allocation: " << (student.randomAllocation ? "Yes" : "No") << "\n";
                            cout << "Special Requests: " << student.specialRequests << "\n";
                            cout << "Joining Date: " << student.joiningDate << "\n";
                            cout << "Room Number: " << (student.roomNumber ? to_string(student.roomNumber) : "Not Allocated") << "\n";
                            break;
                        case 5:
                            cout << "Logging out...\n";
                            return;
                        default:
                            cout << "Invalid choice! Please enter a number between 1 and 5.\n";
                    }
                } while (choice != 5);
                return;
            }
        }
        attempts--;
        cout << "Invalid ID or Password! Attempts remaining: " << attempts << "\n";
    }
    cout << "Too many failed attempts. Returning to main menu.\n";
}

void adminPortal() {
    AdminPanel admin(students);
    admin.adminLogin();
}