#include <bits/stdc++.h>

using namespace std;


struct Product {
    string id;
    double maxPrice;
    double minPrice;
    string dateAdded;
    string dateUpdated;
};

vector<Product> readCSV(const string &filePath) {
    vector<Product> products;
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Could not open file: " << filePath << endl;
        return products;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        Product product;
        string maxPrice, minPrice;

        getline(ss, product.id, ',');
        getline(ss, maxPrice, ',');
        getline(ss, minPrice, ',');

        for (int i = 0; i < 11; ++i) getline(ss, line, ',');
        getline(ss, product.dateAdded, ',');
        getline(ss, product.dateUpdated, ',');

        if (maxPrice.empty() || minPrice.empty()) {
            continue;
        }
        product.maxPrice = stod(maxPrice);
        product.minPrice = stod(minPrice);

        products.push_back(product);
    }

    return products;
}
void bubbleSortByMaxPrice(vector<Product> &products) {
    for (size_t i = 0; i < products.size() - 1; ++i) {
        for (size_t j = 0; j < products.size() - i - 1; ++j) {
            if (products[j].maxPrice > products[j + 1].maxPrice) {
                swap(products[j], products[j + 1]);
            }
        }
    }
}
int partitionByDateAdded(vector<Product> &products, int low, int high) {
    string pivot = products[high].dateAdded;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (products[j].dateAdded < pivot) {
            ++i;
            swap(products[i], products[j]);
        }
    }
    swap(products[i + 1], products[high]);
    return i + 1;
}
void quickSortByDateAdded(vector<Product> &products, int low, int high) {
    if (low < high) {
        int pi = partitionByDateAdded(products, low, high);
        quickSortByDateAdded(products, low, pi - 1);
        quickSortByDateAdded(products, pi + 1, high);
    }
}
void merge(vector<Product> &products, int left, int mid, int right) {
    vector<Product> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (products[i].minPrice <= products[j].minPrice) {
            temp[k++] = products[i++];
        } else {
            temp[k++] = products[j++];
        }
    }

    while (i <= mid) temp[k++] = products[i++];
    while (j <= right) temp[k++] = products[j++];

    for (int p = 0; p < temp.size(); ++p) {
        products[left + p] = temp[p];
    }
}
void mergeSortByMinPrice(vector<Product> &products, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortByMinPrice(products, left, mid);
        mergeSortByMinPrice(products, mid + 1, right);
        merge(products, left, mid, right);
    }
}
void displayProducts(const vector<Product> &products) {
    for (const auto &product : products) {
        cout << "ID: " << product.id
             << ", Max Price: " << product.maxPrice
             << ", Min Price: " << product.minPrice
             << ", Date Added: " << product.dateAdded
             << ", Date Updated: " << product.dateUpdated << "\n";
    }
}
void printMenuHW1() {
    cout << "\n===== Sorting Menu =====\n";
    cout << "1. Bubble Sort by Max Price\n";
    cout << "2. Quick Sort by Date Added\n";
    cout << "3. Merge Sort by Min Price\n";
    cout << "4. Display Products\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}
void Homework1()
{
    string filePath = "ElectronicsProductsPricingData.csv";

    auto products = readCSV(filePath);
    if (products.empty()) {
        cout << "No products loaded. Exiting.\n";
        return;
    }

    int choice;
    do {
        printMenuHW1();
        cin >> choice;

        switch (choice) {
            case 1: {
                auto start = chrono::high_resolution_clock::now();
                bubbleSortByMaxPrice(products);
                auto end = chrono::high_resolution_clock::now();
                cout << "Bubble Sort by Max Price completed in "
                     << chrono::duration<double>(end - start).count() << " seconds\n";
                break;
            }
            case 2: {
                auto start = chrono::high_resolution_clock::now();
                quickSortByDateAdded(products, 0, products.size() - 1);
                auto end = chrono::high_resolution_clock::now();
                cout << "Quick Sort by Date Added completed in "
                     << chrono::duration<double>(end - start).count() << " seconds\n";
                break;
            }
            case 3: {
                auto start = chrono::high_resolution_clock::now();
                mergeSortByMinPrice(products, 0, products.size() - 1);
                auto end = chrono::high_resolution_clock::now();
                cout << "Merge Sort by Min Price completed in "
                     << chrono::duration<double>(end - start).count() << " seconds\n";
                break;
            }
            case 4:
                displayProducts(products);
                break;
            case 5:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

int main()
{
    Homework1();
}
