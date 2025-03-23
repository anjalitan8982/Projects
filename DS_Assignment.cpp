#include <iostream>
#include <string>
using namespace std;

// Node structure for the circular linked list
struct Node {
    string name;
    Node* next;
};

// Create a circular linked list
Node* createCircularLinkedList(int n) {
    Node* head = nullptr;
    Node* temp = nullptr;
    cout << "Enter the names of the students:" << endl;
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        Node* newNode = new Node();
        newNode->name = name;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
            temp = newNode;
        } else {
            temp->next = newNode;
            temp = newNode;
        }
    }
    temp->next = head; // Make it circular
    return head;
}

// Function to print current circle
void printCircle(Node* head) {
    Node* temp = head;
    if (temp == nullptr) return;
    string start = temp->name;
    do {
        cout << temp->name << " -> ";
        temp = temp->next;
    } while (temp != head);
    cout << "(back to " << start << ")" << endl;
}

// Function to find the monitor (Josephus problem) with iteration output
string findMonitor(Node* head, int step) {
    Node* ptr = head;
    Node* prev = nullptr;
    int iteration = 1;

    while (ptr->next != ptr) { // More than one node left
        cout << "\n--- Iteration " << iteration << " ---" << endl;
        cout << "Current Circle: ";
        printCircle(ptr);

        // Move step-1 times
        for (int i = 1; i < step; i++) {
            prev = ptr;
            ptr = ptr->next;
        }
        cout << "Removing: " << ptr->name << endl;
        prev->next = ptr->next;
        delete ptr;
        ptr = prev->next;
        iteration++;
    }

    cout << "\n--- Final Result ---" << endl;
    cout << "Monitor is: " << ptr->name << endl;
    string monitor = ptr->name;
    delete ptr;
    return monitor;
}

// Main function
int main() {
    int n, step;
    cout << "Enter the number of students: ";
    cin >> n;
    if (n <= 0) {
        cout << "Number of students must be greater than 0!" << endl;
        return 0;
    }

    Node* head = createCircularLinkedList(n);

    cout << "Enter the step value (1 to " << n - 1 << "): ";
    cin >> step;
    if (step < 1 || step >= n) {
        cout << "Step value must be between 1 and " << n - 1 << "!" << endl;
        return 0;
    }

    findMonitor(head, step);

    return 0;
}
