#include <iostream>
#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

template <typename T>
class SortingAlgorithms
{
private:
    static int partition(vector<T> &arr, int low, int high)
    {
        T pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (arr[j] <= pivot)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    static void merge(vector<T> &arr, int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<T> L(n1), R(n2);

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
                arr[k++] = L[i++];
            else
                arr[k++] = R[j++];
        }

        while (i < n1)
            arr[k++] = L[i++];
        while (j < n2)
            arr[k++] = R[j++];
    }

    static void heapify(vector<T> &arr, int n, int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;
        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

public:
    static void jumpSort(vector<T> &arr)
    {
        int n = arr.size();
        for (int gap = n / 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i++)
            {
                T temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
        }
    }

    static void bubbleSort(vector<T> &arr)
    {
        int n = arr.size();
        bool swapped;
        for (int i = 0; i < n - 1; i++)
        {
            swapped = false;
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped)
                break;
        }
    }

    static void insertionSort(vector<T> &arr)
    {
        int n = arr.size();
        for (int i = 1; i < n; i++)
        {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    static void heapSort(vector<T> &arr)
    {
        int n = arr.size();
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);
        for (int i = n - 1; i > 0; i--)
        {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

    static void quickSort(vector<T> &arr, int low, int high)
    {
        if (low < high)
        {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    static void mergeSort(vector<T> &arr, int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    static T findMaxValue(vector<T> &arr)
    {
        int n = arr.size();
        if (n == 0)
        {
            throw runtime_error("Array is empty");
        }

        // Build a max-heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // The maximum value is at the root of the heap (index 0)
        return arr[0];
    }
};

// Generator functions for different types
vector<int> generateRandomArray(int size)
{
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);
    for (int i = 0; i < size; i++)
        arr[i] = dis(gen);
    return arr;
}

vector<double> generateRandomDoubleArray(int size)
{
    vector<double> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(1.0, 10000.0);
    for (int i = 0; i < size; i++)
        arr[i] = dis(gen);
    return arr;
}

vector<string> generateRandomStringArray(int size)
{
    vector<string> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> len_dis(3, 10);
    uniform_int_distribution<> char_dis(97, 122); // a-z

    for (int i = 0; i < size; i++)
    {
        int len = len_dis(gen);
        string str;
        for (int j = 0; j < len; j++)
        {
            str += static_cast<char>(char_dis(gen));
        }
        arr[i] = str;
    }
    return arr;
}

template <typename T>
bool isSorted(const vector<T> &arr)
{
    for (size_t i = 1; i < arr.size(); i++)
        if (arr[i] < arr[i - 1])
            return false;
    return true;
}

template <typename T>
void printPerformance(const vector<T> &original, const string &type_name)
{
    vector<pair<string, vector<T>>> algorithms;
    int size = original.size();

    algorithms.push_back({"Bubble Sort", original});
    algorithms.push_back({"Insertion Sort", original});
    algorithms.push_back({"Jump Sort", original});
    algorithms.push_back({"Heap Sort", original});
    algorithms.push_back({"Quick Sort", original});
    algorithms.push_back({"Merge Sort", original});

    cout << "\nSorting Performance Comparison for " << type_name << "\n";
    cout << "Array Size: " << size << " elements\n";
    cout << string(60, '-') << "\n";
    cout << left << setw(20) << "Algorithm"
         << right << setw(20) << "Time (ms)"
         << right << setw(20) << "Verified\n";
    cout << string(60, '-') << "\n";

    for (auto &algo : algorithms)
    {
        auto start = high_resolution_clock::now();

        if (algo.first == "Bubble Sort")
            SortingAlgorithms<T>::bubbleSort(algo.second);
        else if (algo.first == "Insertion Sort")
            SortingAlgorithms<T>::insertionSort(algo.second);
        else if (algo.first == "Jump Sort")
            SortingAlgorithms<T>::jumpSort(algo.second);
        else if (algo.first == "Heap Sort")
            SortingAlgorithms<T>::heapSort(algo.second);
        else if (algo.first == "Quick Sort")
            SortingAlgorithms<T>::quickSort(algo.second, 0, size - 1);
        else if (algo.first == "Merge Sort")
            SortingAlgorithms<T>::mergeSort(algo.second, 0, size - 1);

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        double ms = duration.count() / 1000.0;

        bool sorted = isSorted(algo.second);
        cout << left << setw(20) << algo.first
             << right << fixed << setprecision(3) << setw(20) << ms
             << right << setw(20) << (sorted ? "Yes" : "No") << "\n";
    }
    cout << string(60, '-') << "\n";
}
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int binarySearch(const vector<int>& arr, int item, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == item)
            return mid + 1;
        else if (arr[mid] < item)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}
void insertionSortWithBinarySearch(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int pos = binarySearch(arr, key, 0, i - 1);
        for (int j = i - 1; j >= pos; --j) {
            arr[j + 1] = arr[j];
        }
        arr[pos] = key;
    }
}
vector<int> generateRandomList(int size) {
    vector<int> list(size);
    for (int i = 0; i < size; ++i) {
        list[i] = rand() % 1000;
    }
    return list;
}
void measurePerformance() {
    const int SIZE = 1000;
    vector<int> list1 = generateRandomList(SIZE);
    vector<int> list2 = list1; // Copy of the original list

    auto start = high_resolution_clock::now();
    insertionSort(list1);
    auto end = high_resolution_clock::now();
    auto durationInsertionSort = duration_cast<milliseconds>(end - start).count();
    cout << "Standard Insertion Sort Time: " << durationInsertionSort << " ms" << endl;

    start = high_resolution_clock::now();
    insertionSortWithBinarySearch(list2);
    end = high_resolution_clock::now();
    auto durationBinarySearchSort = duration_cast<milliseconds>(end - start).count();
    cout << "Insertion Sort with Binary Search Time: " << durationBinarySearchSort << " ms" << endl;
}


void Problem1()
{
    printPerformance(generateRandomArray(1000), "Integer");
}

void Problem2()
{
    vector<int> sizes = {100, 1000, 10000};
    for (int size : sizes)
    {
        printPerformance(generateRandomArray(size), "Integer");
    }
}

void Problem3()
{
    int size = 100;
    printPerformance(generateRandomDoubleArray(size), "Double");
    printPerformance(generateRandomStringArray(size), "String");
}

void Problem5() {
    srand(time(0));
    measurePerformance();
}

void Problem6(){
    vector<int> arr = {10, 45, 2, 78, 34, 99, 23};
    int maxValue = SortingAlgorithms<int>::findMaxValue(arr);
    cout << "Maximum value in the array: " << maxValue << endl;

}
template <typename T>
void hybridSort(vector<T>& arr, int left, int right) {
    int size = right - left + 1;
    if (size <= 10) {
    SortingAlgorithms<T>::insertionSort(arr);
    }
    else {
    SortingAlgorithms<T>::mergeSort(arr, left, right);
    }

}
void Problem7() {
    vector<int> sizes = {10, 100, 1000, 10000};

for (int size : sizes) {
    cout << "Array Size: " << size << endl;
    vector<int> arr1 = generateRandomArray(size);
    vector<int> arr2 = arr1;
    auto start = high_resolution_clock::now();
    SortingAlgorithms<int>::mergeSort(arr1, 0, size - 1);
    auto end = high_resolution_clock::now();
    auto durationMergeSort = duration_cast<milliseconds>(end - start).count();
    cout << "Merge Sort Time: " << durationMergeSort << " ms" << endl;
    start = high_resolution_clock::now();
    hybridSort(arr2, 0, size - 1);
    end = high_resolution_clock::now();
    auto durationHybridSort = duration_cast<milliseconds>(end - start).count();
    cout << "Hybrid Sort Time: " << durationHybridSort << " ms" << endl;

        cout << string(30, '-') << endl;
    }
}

struct StockRecord {
    tm timestamp;
    string company;
    double stockPrice;
    double percentageChange;
};


bool operator<(const tm& a, const tm& b) {
    if (a.tm_year != b.tm_year) return a.tm_year < b.tm_year;
    if (a.tm_mon != b.tm_mon) return a.tm_mon < b.tm_mon;
    if (a.tm_mday != b.tm_mday) return a.tm_mday < b.tm_mday;
    if (a.tm_hour != b.tm_hour) return a.tm_hour < b.tm_hour;
    if (a.tm_min != b.tm_min) return a.tm_min < b.tm_min;
    return a.tm_sec < b.tm_sec;
}

class StockDataset {
private:
    vector<StockRecord> records;
    tm parseTimestamp(const string& dateTime) {
        tm tm = {};
        istringstream ss(dateTime);
        ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
        return tm;
    }

    string formatTimestamp(const tm& timestamp) const {
        ostringstream oss;
        oss << put_time(&timestamp, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

public:
    void loadFromFile(const string& filePath) {
        ifstream file(filePath);
        if (!file.is_open()) {
            cerr << "Failed to open file: " << filePath << endl;
            return;
        }
        string line;
        getline(file, line);
        while (getline(file, line)) {
            istringstream ss(line);
            string timestamp, company, stockPrice, percentageChange;
            getline(ss, timestamp, ',');
            getline(ss, company, ',');
            getline(ss, stockPrice, ',');
            getline(ss, percentageChange, ',');

            records.push_back({
                parseTimestamp(timestamp),
                company,
                stod(stockPrice),
                stod(percentageChange.substr(0, percentageChange.size() - 1)) // Remove % sign
            });
        }
        file.close();
    }

    void printDataset() const {
        for (const auto& record : records) {
            cout << formatTimestamp(record.timestamp) << ", "
                 << record.company << ", "
                 << record.stockPrice << ", "
                 << record.percentageChange << "%" << endl;
        }
    }
    void quickSortTimestamp(int left, int right) {
        if (left >= right) return;
        auto pivot = records[right].timestamp;
        int partitionIndex = left;
        for (int i = left; i < right; ++i) {
            if (records[i].timestamp < pivot) {
                swap(records[i], records[partitionIndex]);
                partitionIndex++;
            }
        }
        swap(records[partitionIndex], records[right]);
        quickSortTimestamp(left, partitionIndex - 1);
        quickSortTimestamp(partitionIndex + 1, right);
    }

    void bubbleSortStockPrice() {
        for (size_t i = 0; i < records.size(); ++i) {
            for (size_t j = 0; j < records.size() - i - 1; ++j) {
                if (records[j].stockPrice > records[j + 1].stockPrice) {
                    swap(records[j], records[j + 1]);
                }
            }
        }
    }

    void insertionSortPercentageChange() {
        for (size_t i = 1; i < records.size(); ++i) {
            StockRecord key = records[i];
            int j = i - 1;

            while (j >= 0 && records[j].percentageChange > key.percentageChange) {
                records[j + 1] = records[j];
                j--;
            }
            records[j + 1] = key;
        }
    }

    void mergeSortStockPrice(int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSortStockPrice(left, mid);
        mergeSortStockPrice(mid + 1, right);

        vector<StockRecord> temp;
        int i = left, j = mid + 1;
        while (i <= mid && j <= right) {
            if (records[i].stockPrice <= records[j].stockPrice) {
                temp.push_back(records[i++]);
            } else {
                temp.push_back(records[j++]);
            }
        }
        while (i <= mid) temp.push_back(records[i++]);
        while (j <= right) temp.push_back(records[j++]);

        for (size_t k = 0; k < temp.size(); ++k) {
            records[left + k] = temp[k];
        }
    }
    void displayMenuProblem12() {
        int choice;
        do {
            cout << "\n--- Sorting Menu ---\n";
            cout << "1. Quick Sort (Timestamp)\n";
            cout << "2. Bubble Sort (Stock Price)\n";
            cout << "3. Insertion Sort (Percentage Change)\n";
            cout << "4. Merge Sort (Stock Price)\n";
            cout << "5. Print Dataset\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    quickSortTimestamp(0, records.size() - 1);
                    cout << "Sorted by Timestamp using Quick Sort.\n";
                    break;
                case 2:
                    bubbleSortStockPrice();
                    cout << "Sorted by Stock Price using Bubble Sort.\n";
                    break;
                case 3:
                    insertionSortPercentageChange();
                    cout << "Sorted by Percentage Change using Insertion Sort.\n";
                    break;
                case 4:
                    mergeSortStockPrice(0, records.size() - 1);
                    cout << "Sorted by Stock Price using Merge Sort.\n";
                    break;
                case 5:
                    printDataset();
                    break;
                case 6:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 6);
    }
};
class HybridSorter
{
private:
    // Insertion Sort for small subarrays
    template <typename T>
    void insertionSort(vector<T> &arr, int left, int right)
    {
        for (int i = left + 1; i <= right; i++)
        {
            T key = arr[i];
            int j = i - 1;

            // Move elements of arr[left..i-1] that are greater than key
            // to one position ahead of their current position
            while (j >= left && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // Partition function for Quick Sort
    template <typename T>
    int partition(vector<T> &arr, int low, int high)
    {
        // Choose the rightmost element as pivot
        T pivot = arr[high];

        // Index of smaller element
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++)
        {
            // If current element is smaller than or equal to pivot
            if (arr[j] <= pivot)
            {
                // Increment index of smaller element
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    // Recursive Quick Sort with Insertion Sort for small subarrays
    template <typename T>
    void hybridQuickSort(vector<T> &arr, int low, int high, int threshold = 10)
    {
        // Use Insertion Sort for small subarrays
        if (high - low + 1 <= threshold)
        {
            insertionSort(arr, low, high);
            return;
        }

        // If the subarray is larger than threshold, use Quick Sort
        if (low < high)
        {
            // Partition the array
            int pi = partition(arr, low, high);

            // Recursively sort elements before and after partition
            hybridQuickSort(arr, low, pi - 1, threshold);
            hybridQuickSort(arr, pi + 1, high, threshold);
        }
    }

public:
    // Public method to perform hybrid sort
    template <typename T>
    void sort(vector<T> &arr)
    {
        if (arr.empty())
        {
            return;
        }

        // Call the hybrid quick sort with default threshold
        hybridQuickSort(arr, 0, arr.size() - 1);
    }

    // Overloaded method to allow custom threshold
    template <typename T>
    void sort(vector<T> &arr, int threshold)
    {
        if (arr.empty())
        {
            return;
        }

        hybridQuickSort(arr, 0, arr.size() - 1, threshold);
    }
};


template <typename T>
vector<T> generateRandomVector(int size, T min, T max)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);

    vector<T> vec(size);
    for (int i = 0; i < size; ++i)
    {
        vec[i] = distrib(gen);
    }
    return vec;
}


void Problem8()
{

    vector<int> sizes = {100, 1000, 10000, 100000};

    for (int size : sizes)
    {
        cout << "\nPerformance for vector size: " << size << endl;


        auto vec1 = generateRandomVector<int>(size, 1, 1000000);
        auto vec2 = vec1;


        auto start = high_resolution_clock::now();
        HybridSorter hybridSorter;
        hybridSorter.sort(vec1);
        auto end = high_resolution_clock::now();
        auto hybridDuration = duration_cast<microseconds>(end - start);


        start = high_resolution_clock::now();
        sort(vec2.begin(), vec2.end());
        end = high_resolution_clock::now();
        auto stdSortDuration = duration_cast<microseconds>(end - start);


        cout << "Hybrid Sort time: " << hybridDuration.count() << " microseconds" << endl;
        cout << "Std Quick Sort time:    " << stdSortDuration.count() << " microseconds" << endl;


        if (vec1 != vec2)
        {
            cout << "Error: Sorting results do not match!" << endl;
        }
    }
}

class GeometricPoint
{
public:
    double x, y;

    GeometricPoint(double x = 0, double y = 0) : x(x), y(y) {}


    double calculateRadialDistance() const
    {
        return sqrt(x * x + y * y);
    }
};

class AdvancedSorter
{
public:

    template <typename T>
    static void performBubbleSort(vector<T> &arr)
    {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    template <typename T>
    static void performInsertionSort(vector<T> &arr)
    {
        int n = arr.size();
        for (int i = 1; i < n; i++)
        {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

    static void performMergeSort(vector<int> &arr)
    {
        if (arr.size() <= 1)
            return;
        vector<int> left(arr.begin(), arr.begin() + arr.size() / 2);
        vector<int> right(arr.begin() + arr.size() / 2, arr.end());
        performMergeSort(left);
        performMergeSort(right);
        merge(arr, left, right);
    }

    static void merge(vector<int> &arr, vector<int> &left, vector<int> &right)
    {
        int i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size())
        {
            if (left[i] < right[j])
            {
                arr[k++] = left[i++];
            }
            else
            {
                arr[k++] = right[j++];
            }
        }
        while (i < left.size())
        {
            arr[k++] = left[i++];
        }
        while (j < right.size())
        {
            arr[k++] = right[j++];
        }
    }


    template <typename T>
    static void performHeapSort(vector<T> &arr)
    {
        make_heap(arr.begin(), arr.end());
        sort_heap(arr.begin(), arr.end());
    }

    template <typename T>
    static void performQuickSort(vector<T> &arr)
    {
        quickSort(arr, 0, arr.size() - 1);
    }

    template <typename T>
    static void quickSort(vector<T> &arr, int low, int high)
    {
        if (low < high)
        {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    template <typename T>
    static int partition(vector<T> &arr, int low, int high)
    {
        T pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++)
        {
            if (arr[j] < pivot)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    template <typename T, typename Func>
    static long measureSortingPerformance(vector<T> &data, Func sortFunc)
    {
        auto start = chrono::high_resolution_clock::now();
        sortFunc(data);
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
};

void Problem9()
{
    const int DATA_SIZE = 1000;
    const int NUM_RUNS = 10;

    random_device rd;
    mt19937 gen(rd());

    vector<int> insertionData(DATA_SIZE);
    vector<int> jumpData(DATA_SIZE);
    vector<int> mergeData(DATA_SIZE);
    vector<int> heapData(DATA_SIZE);
    vector<int> quickData(DATA_SIZE);

    for (int i = 0; i < DATA_SIZE; i++)
    {
        int value = uniform_int_distribution<>(0, 10000)(gen);
        insertionData[i] = value;
        jumpData[i] = value;
        mergeData[i] = value;
        heapData[i] = value;
        quickData[i] = value;
    }

    cout << "Insertion Sort: " << AdvancedSorter::measureSortingPerformance(insertionData, AdvancedSorter::performInsertionSort<int>) << " micro-secs\n";
    cout << "Merge Sort: " << AdvancedSorter::measureSortingPerformance(mergeData, AdvancedSorter::performMergeSort) << " micro-secs\n";
    cout << "Heap Sort: " << AdvancedSorter::measureSortingPerformance(heapData, AdvancedSorter::performHeapSort<int>) << " micro-secs\n";
    cout << "Quick Sort: " << AdvancedSorter::measureSortingPerformance(quickData, AdvancedSorter::performQuickSort<int>) << " micro-secs\n\n";

    cout << "\nMulti-Dimensional Point Sorting Performance (by radial distance, in microseconds):\n";

    for (int run = 0; run < NUM_RUNS; run++)
    {
        vector<GeometricPoint> pointData(DATA_SIZE);
        for (GeometricPoint &p : pointData)
        {
            p = GeometricPoint(
                uniform_real_distribution<>(-10000, 10000)(gen),
                uniform_real_distribution<>(-10000, 10000)(gen));
        }

        auto sortByRadialDistance = [](vector<GeometricPoint> &points)
        {
            sort(points.begin(), points.end(), [](const GeometricPoint &a, const GeometricPoint &b)
                 { return a.calculateRadialDistance() < b.calculateRadialDistance(); });
        };

        cout << "Radial Distance Sort: " << AdvancedSorter::measureSortingPerformance(pointData, sortByRadialDistance) << " micro-secs\n";
    }
}

class Song
{
public:
    string title;
    string artist;
    string album;
    int durationSeconds;

    Song(const string &_title, const string &_artist, const string &_album, int _durationSeconds)
        : title(_title), artist(_artist), album(_album), durationSeconds(_durationSeconds) {}

    string getDurationString() const
    {
        int minutes = durationSeconds / 60;
        int seconds = durationSeconds % 60;

        return to_string(minutes) + ":" +
               (seconds < 10 ? "0" : "") + to_string(seconds);
    }
};

class Playlist
{
private:
    vector<Song> songs;


    void heapify(vector<Song> &arr, int n, int i, bool (*compareFunc)(const Song &, const Song &))
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && compareFunc(arr[left], arr[largest]))
        {
            largest = left;
        }

        if (right < n && compareFunc(arr[right], arr[largest]))
        {
            largest = right;
        }

        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest, compareFunc);
        }
    }


    void heapSort(vector<Song> &arr, bool (*compareFunc)(const Song &, const Song &))
    {
        int n = arr.size();


        for (int i = n / 2 - 1; i >= 0; i--)
        {
            heapify(arr, n, i, compareFunc);
        }


        for (int i = n - 1; i > 0; i--)
        {

            swap(arr[0], arr[i]);


            heapify(arr, i, 0, compareFunc);
        }
    }


    static bool compareByArtist(const Song &a, const Song &b)
    {
        return a.artist > b.artist;
    }

    static bool compareByTitle(const Song &a, const Song &b)
    {
        return a.title > b.title;
    }

    static bool compareByDuration(const Song &a, const Song &b)
    {
        return a.durationSeconds > b.durationSeconds;
    }

public:

    void addSong(const string &title, const string &artist, const string &album, int durationSeconds)
    {
        songs.emplace_back(title, artist, album, durationSeconds);
    }

    void removeSong(const string &title)
    {
        auto it = remove_if(songs.begin(), songs.end(),
                            [&title](const Song &song)
                            { return song.title == title; });

        if (it != songs.end())
        {
            songs.erase(it, songs.end());
            cout << "Song '" << title << "' removed from playlist." << endl;
        }
        else
        {
            cout << "Song '" << title << "' not found in playlist." << endl;
        }
    }


    void sortPlaylist(int sortOption)
    {
        if (songs.empty())
        {
            cout << "Playlist is empty." << endl;
            return;
        }

        switch (sortOption)
        {
        case 1:
            heapSort(songs, compareByArtist);
            cout << "Playlist sorted by Artist (descending)." << endl;
            break;
        case 2:
            heapSort(songs, compareByTitle);
            cout << "Playlist sorted by Title (descending)." << endl;
            break;
        case 3:
            heapSort(songs, compareByDuration);
            cout << "Playlist sorted by Duration (descending)." << endl;
            break;
        default:
            cout << "Invalid sorting option." << endl;
            return;
        }
    }


    void displayPlaylist() const
    {
        if (songs.empty())
        {
            cout << "Playlist is empty." << endl;
            return;
        }

        cout << left << setw(30) << "Title"
             << setw(25) << "Artist"
             << setw(25) << "Album"
             << "Duration" << endl;
        cout << string(85, '-') << endl;

        for (const auto &song : songs)
        {
            cout << left << setw(30) << song.title
                 << setw(25) << song.artist
                 << setw(25) << song.album
                 << song.getDurationString() << endl;
        }
    }

    void testPlaylist()
    {
        addSong("Bohemian Rhapsody", "Queen", "A Night at the Opera", 354);
        addSong("Hotel California", "Eagles", "Hotel California", 390);
        addSong("Stairway to Heaven", "Led Zeppelin", "Led Zeppelin IV", 482);
        addSong("Imagine", "John Lennon", "Imagine", 183);
        addSong("Like a Rolling Stone", "Bob Dylan", "Highway 61 Revisited", 374);


        cout << "Original Playlist:" << endl;
        displayPlaylist();
        cout << endl;

        cout << "Sorting by Artist:" << endl;
        sortPlaylist(1);
        displayPlaylist();
        cout << endl;

        cout << "Sorting by Title:" << endl;
        sortPlaylist(2);
        displayPlaylist();
        cout << endl;


        removeSong("Imagine");


        cout << "Updated Playlist:" << endl;
        displayPlaylist();
    }
};

void Problem10()
{
    Playlist playlist;
    playlist.testPlaylist();
}

class Route
{
public:
    string origin;
    string destination;
    double distance;
    double travelTime;
    vector<string> waypoints;


    Route(const string &_origin, const string &_destination,
          double _distance, double _travelTime,
          const vector<string> &_waypoints = {})
        : origin(_origin),
          destination(_destination),
          distance(_distance),
          travelTime(_travelTime),
          waypoints(_waypoints) {}


    string formatTravelTime() const
    {
        int hours = static_cast<int>(travelTime);
        int minutes = static_cast<int>((travelTime - hours) * 60);

        string timeStr;
        if (hours > 0)
        {
            timeStr += to_string(hours) + " hr ";
        }
        if (minutes > 0)
        {
            timeStr += to_string(minutes) + " min";
        }
        return timeStr.empty() ? "0 min" : timeStr;
    }
};


class RouteOptimizer
{
private:
    vector<Route> routes;

    void heapify(vector<Route> &arr, int n, int i, bool (*compareFunc)(const Route &, const Route &))
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && compareFunc(arr[left], arr[largest]))
        {
            largest = left;
        }
        if (right < n && compareFunc(arr[right], arr[largest]))
        {
            largest = right;
        }
        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest, compareFunc);
        }
    }

    void heapSort(vector<Route> &arr, bool (*compareFunc)(const Route &, const Route &))
    {
        int n = arr.size();

        for (int i = n / 2 - 1; i >= 0; i--)
        {
            heapify(arr, n, i, compareFunc);
        }

        for (int i = n - 1; i > 0; i--)
        {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0, compareFunc);
        }
    }

    static bool compareByDistance(const Route &a, const Route &b)
    {
        return a.distance > b.distance;
    }

    static bool compareByTravelTime(const Route &a, const Route &b)
    {
        return a.travelTime > b.travelTime;
    }

public:

    void addRoute(const string &origin, const string &destination,
                  double distance, double travelTime,
                  const vector<string> &waypoints = {})
    {
        routes.emplace_back(origin, destination, distance, travelTime, waypoints);
    }
    void removeRoute(const string &origin, const string &destination)
    {
        auto it = remove_if(routes.begin(), routes.end(),
                            [&origin, &destination](const Route &route)
                            {
                                return route.origin == origin && route.destination == destination;
                            });

        if (it != routes.end())
        {
            routes.erase(it, routes.end());
            cout << "Route from " << origin << " to " << destination << " removed." << endl;
        }
        else
        {
            cout << "Route not found." << endl;
        }
    }

    void sortRoutes(int sortOption)
    {
        if (routes.empty())
        {
            cout << "No routes available." << endl;
            return;
        }

        switch (sortOption)
        {
        case 1:
            heapSort(routes, compareByDistance);
            cout << "Routes sorted by Distance (descending)." << endl;
            break;
        case 2:
            heapSort(routes, compareByTravelTime);
            cout << "Routes sorted by Travel Time (descending)." << endl;
            break;
        default:
            cout << "Invalid sorting option." << endl;
            return;
        }
    }

    void displayRoutes() const
    {
        if (routes.empty())
        {
            cout << "No routes available." << endl;
            return;
        }

        cout << left
             << setw(20) << "Origin"
             << setw(20) << "Destination"
             << setw(15) << "Distance (km)"
             << setw(20) << "Travel Time"
             << "Waypoints" << endl;
        cout << string(90, '-') << endl;

        for (const auto &route : routes)
        {

            string waypointsStr;
            if (route.waypoints.empty())
            {
                waypointsStr = "None";
            }
            else
            {
                for (size_t i = 0; i < route.waypoints.size(); ++i)
                {
                    waypointsStr += route.waypoints[i];
                    if (i < route.waypoints.size() - 1)
                    {
                        waypointsStr += ", ";
                    }
                }
            }

            cout << left
                 << setw(20) << route.origin
                 << setw(20) << route.destination
                 << setw(15) << fixed << setprecision(2) << route.distance
                 << setw(20) << route.formatTravelTime()
                 << waypointsStr << endl;
        }
    }

    Route findOptimalRoute(bool prioritizeDistance = true) const
    {
        if (routes.empty())
        {
            throw runtime_error("No routes available");
        }

        auto compareFunc = prioritizeDistance ? [](const Route &a, const Route &b)
        { return a.distance < b.distance; }   : [](const Route &a, const Route &b)
        { return a.travelTime < b.travelTime; };

        return *min_element(routes.begin(), routes.end(), compareFunc);
    }


    void testRouteOptimizer()
    {

        addRoute("New York", "Boston", 350.5, 4.5);
        addRoute("San Francisco", "Los Angeles", 615.7, 6.2, {"San Jose", "Monterey"});
        addRoute("Chicago", "Detroit", 450.3, 5.0);
        addRoute("Miami", "Orlando", 380.2, 4.0, {"Fort Lauderdale"});
        addRoute("Seattle", "Portland", 280.6, 3.5);

        cout << "Original Routes:" << endl;
        displayRoutes();
        cout << endl;

        cout << "Sorting by Distance:" << endl;
        sortRoutes(1);
        displayRoutes();
        cout << endl;

        cout << "Sorting by Travel Time:" << endl;
        sortRoutes(2);
        displayRoutes();
        cout << endl;
        try
        {
            Route optimalByDistance = findOptimalRoute(true);
            cout << "Most Optimal Route by Distance:" << endl;
            cout << "From " << optimalByDistance.origin
                 << " to " << optimalByDistance.destination
                 << " (Distance: " << optimalByDistance.distance << " km)" << endl;

            Route optimalByTime = findOptimalRoute(false);
            cout << "Most Optimal Route by Travel Time:" << endl;
            cout << "From " << optimalByTime.origin
                 << " to " << optimalByTime.destination
                 << " (Travel Time: " << optimalByTime.formatTravelTime() << ")" << endl;
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
        removeRoute("Chicago", "Detroit");
        cout << "\nRoutes after removal:" << endl;
        displayRoutes();
    }
};

void Problem11()
{
    RouteOptimizer routeOptimizer;
    routeOptimizer.testRouteOptimizer();
}

void Problem12()
{
    StockDataset dataset;
    string filePath;
    cout << "Enter the CSV file path: ";
    getline(cin, filePath);
    dataset.loadFromFile(filePath);
    dataset.displayMenuProblem12();
}


int main(){
    Problem7();
}
