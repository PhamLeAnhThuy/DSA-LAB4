#include <bits/stdc++.h>
using namespace std;

struct Student {
    string name;
    int grade;
    int age;

    Student() {}

    Student(string n, int g, int a) {
        name = n;
        grade = g;
        age = a;
    }
};

vector<Student> readCSV(const string& filepath) {
    vector<Student> students;
    ifstream file(filepath);
    string line, word;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        Student student;
        getline(ss, student.name, ',');
        ss >> student.grade;
        ss.ignore();
        ss >> student.age;
        students.push_back(student);
    }
    return students;
}

class SortingAlgorithms {
public:
    static void bubbleSort(vector<Student>& students, const string& field) {
        int n = students.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if ((field == "name" && students[j].name > students[j + 1].name) ||
                    (field == "grade" && students[j].grade > students[j + 1].grade) ||
                    (field == "age" && students[j].age > students[j + 1].age)) {
                    swap(students[j], students[j + 1]);
                }
            }
        }
    }

    static void insertionSort(vector<Student>& students, const string& field) {
        int n = students.size();
        for (int i = 1; i < n; i++) {
            Student key = students[i];
            int j = i - 1;
            while (j >= 0 && ((field == "name" && students[j].name > key.name) ||
                              (field == "grade" && students[j].grade > key.grade) ||
                              (field == "age" && students[j].age > key.age))) {
                students[j + 1] = students[j];
                j--;
            }
            students[j + 1] = key;
        }
    }

    static int partition(vector<Student>& students, int low, int high, const string& field) {
        Student pivot = students[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if ((field == "name" && students[j].name < pivot.name) ||
                (field == "grade" && students[j].grade < pivot.grade) ||
                (field == "age" && students[j].age < pivot.age)) {
                i++;
                swap(students[i], students[j]);
            }
        }
        swap(students[i + 1], students[high]);
        return i + 1;
    }

    static void quickSort(vector<Student>& students, int low, int high, const string& field) {
        if (low < high) {
            int pi = partition(students, low, high, field);
            quickSort(students, low, pi - 1, field);
            quickSort(students, pi + 1, high, field);
        }
    }

    static void merge(vector<Student>& students, int left, int mid, int right, const string& field) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<Student> L(students.begin() + left, students.begin() + left + n1);
        vector<Student> R(students.begin() + mid + 1, students.begin() + mid + 1 + n2);

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if ((field == "name" && L[i].name <= R[j].name) ||
                (field == "grade" && L[i].grade <= R[j].grade) ||
                (field == "age" && L[i].age <= R[j].age)) {
                students[k] = L[i];
                i++;
            } else {
                students[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            students[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            students[k] = R[j];
            j++;
            k++;
        }
    }

    static void mergeSort(vector<Student>& students, int left, int right, const string& field) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(students, left, mid, field);
            mergeSort(students, mid + 1, right, field);
            merge(students, left, mid, right, field);
        }
    }

    static void heapify(vector<Student>& students, int n, int i, const string& field) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && ((field == "name" && students[left].name > students[largest].name) ||
                         (field == "grade" && students[left].grade > students[largest].grade) ||
                         (field == "age" && students[left].age > students[largest].age)))
            largest = left;

        if (right < n && ((field == "name" && students[right].name > students[largest].name) ||
                          (field == "grade" && students[right].grade > students[largest].grade) ||
                          (field == "age" && students[right].age > students[largest].age)))
            largest = right;

        if (largest != i) {
            swap(students[i], students[largest]);
            heapify(students, n, largest, field);
        }
    }

    static void heapSort(vector<Student>& students, const string& field) {
        int n = students.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(students, n, i, field);

        for (int i = n - 1; i > 0; i--) {
            swap(students[0], students[i]);
            heapify(students, i, 0, field);
        }
    }

    static void jumpSort(vector<Student>& students, const string& field) {
        int n = students.size();
        int step = sqrt(n);
        for (int i = 0; i < n; i += step) {
            for (int j = min(i + step, n) - 1; j > i; j--) {
                for (int k = i; k < j; k++) {
                    if ((field == "name" && students[k].name > students[k + 1].name) ||
                        (field == "grade" && students[k].grade > students[k + 1].grade) ||
                        (field == "age" && students[k].age > students[k + 1].age)) {
                        swap(students[k], students[k + 1]);
                    }
                }
            }
        }
    }
};

void displayStudents(const vector<Student>& students, int limit = 5) {
    for (int i = 0; i < min(limit, (int)students.size()); i++) {
        cout << "Name: " << students[i].name << "\n";
        cout << "Grade: " << students[i].grade << "\n";
        cout << "Age: " << students[i].age << "\n";
        cout << "-------------------\n";
    }
}

int main() {
    string filepath = "../dataset/StudentsPerformance.csv";
    vector<Student> students = readCSV(filepath);

    cout << "Original Students:\n";
    displayStudents(students);

    vector<Student> bubbleSortStudents = students;
    vector<Student> insertionSortStudents = students;
    vector<Student> quickSortStudents = students;
    vector<Student> mergeSortStudents = students;
    vector<Student> heapSortStudents = students;
    vector<Student> jumpSortStudents = students;

    cout << "\nBubble Sort by Name:\n";
    SortingAlgorithms::bubbleSort(bubbleSortStudents, "name");
    displayStudents(bubbleSortStudents);

    cout << "\nInsertion Sort by Grade:\n";
    SortingAlgorithms::insertionSort(insertionSortStudents, "grade");
    displayStudents(insertionSortStudents);

    cout << "\nQuick Sort by Age:\n";
    SortingAlgorithms::quickSort(quickSortStudents, 0, quickSortStudents.size() - 1, "age");
    displayStudents(quickSortStudents);

    cout << "\nMerge Sort by Name:\n";
    SortingAlgorithms::mergeSort(mergeSortStudents, 0, mergeSortStudents.size() - 1, "name");
    displayStudents(mergeSortStudents);

    cout << "\nHeap Sort by Grade:\n";
    SortingAlgorithms::heapSort(heapSortStudents, "grade");
    displayStudents(heapSortStudents);

    cout << "\nJump Sort by Age:\n";
    SortingAlgorithms::jumpSort(jumpSortStudents, "age");
    displayStudents(jumpSortStudents);

    return 0;
}
