#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>

using namespace std;

struct Employee {
    int id;
    int salary;
};

// Function to safely read an integer input
int readInt() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer: ";
        } else {
            return value;
        }
    }
}

// Bubble Sort implementation for employees by salary
void bubbleSort(vector<Employee>& employees, int& comparisons, int& swaps) {
    int n = employees.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparisons++;
            if (employees[j].salary > employees[j + 1].salary) {
                swaps++;
                swap(employees[j], employees[j + 1]);
            }
        }
    }
}

// Selection Sort implementation for employees by salary
void selectionSort(vector<Employee>& employees, int& comparisons, int& swaps) {
    int n = employees.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (employees[j].salary < employees[minIndex].salary) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swaps++;
            swap(employees[i], employees[minIndex]);
        }
    }
}

// Insertion Sort implementation for employees by salary
void insertionSort(vector<Employee>& employees, int& comparisons, int& swaps) {
    int n = employees.size();
    for (int i = 1; i < n; i++) {
        Employee key = employees[i];
        int j = i - 1;
        comparisons++;
        while (j >= 0 && employees[j].salary > key.salary) {
            employees[j + 1] = employees[j];
            swaps++;
            j--;
            comparisons++;
        }
        employees[j + 1] = key;
        if (j != i - 1) swaps++;
    }
}

// Merge function used in Merge Sort
void merge(vector<Employee>& employees, int left, int mid, int right, int& comparisons, int& swaps) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Employee> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = employees[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = employees[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisons++;
        if (leftArr[i].salary <= rightArr[j].salary) {
            employees[k++] = leftArr[i++];
        } else {
            employees[k++] = rightArr[j++];
            swaps++;
        }
    }

    while (i < n1)
        employees[k++] = leftArr[i++];

    while (j < n2)
        employees[k++] = rightArr[j++];
}

// Merge Sort implementation for employees by salary
void mergeSort(vector<Employee>& employees, int left, int right, int& comparisons, int& swaps) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(employees, left, mid, comparisons, swaps);
        mergeSort(employees, mid + 1, right, comparisons, swaps);
        merge(employees, left, mid, right, comparisons, swaps);
    }
}

// Function to measure and print sorting results
void sortAndMeasure(void (*sortFunc)(vector<Employee>&, int&, int&), vector<Employee> employees) {
    int comparisons = 0, swaps = 0;
    auto start = chrono::high_resolution_clock::now();
    sortFunc(employees, comparisons, swaps);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    for (const Employee& emp : employees) {
        cout << emp.id << " ";
    }
    cout << "\nComparisons: " << comparisons << ", Swaps: " << swaps << ", Time: " << duration << " microseconds\n" << endl;
}

// Overloaded function to measure and print Merge Sort results
void sortAndMeasureMerge(void (*sortFunc)(vector<Employee>&, int, int, int&, int&), vector<Employee> employees) {
    int comparisons = 0, swaps = 0;
    auto start = chrono::high_resolution_clock::now();
    sortFunc(employees, 0, employees.size() - 1, comparisons, swaps);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    for (const Employee& emp : employees) {
        cout << emp.id << " ";
    }
    cout << "\nComparisons: " << comparisons << ", Swaps: " << swaps << ", Time: " << duration << " microseconds\n" << endl;
}

int main() {
    int n;
    cout << "Enter the number of employees: ";
    n = readInt();

    vector<int> ids(n), salaries(n);
    cout << "Enter empid of  employees: ";
    for (int i = 0; i < n; i++) {
        ids[i] = readInt();
    }

    cout << "Enter Salaries of employees: ";
    for (int i = 0; i < n; i++) {
        salaries[i] = readInt();
    }

    vector<Employee> employees(n);
    for (int i = 0; i < n; i++) {
        employees[i] = {ids[i], salaries[i]};
    }


    cout << "\nSorting using Bubble Sort:" << endl;
    sortAndMeasure(bubbleSort, employees);

    cout << "\nSorting using Selection Sort:" << endl;
    sortAndMeasure(selectionSort, employees);

    cout << "\nSorting using Insertion Sort:" << endl;
    sortAndMeasure(insertionSort, employees);

    cout << "\nSorting using Merge Sort:" << endl;
    sortAndMeasureMerge(mergeSort, employees);

    return 0;
}
