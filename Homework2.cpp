#include <bits/stdc++.h>

using namespace std;

struct Post {
    string text;
    string sentiment;
    string timestamp;
    string user;
    string platform;
    string hashtags;
    int retweets;
    int likes;
    string country;
    int year, month, day, hour;
    double engagement_score;

    Post() {}

    Post(string t, string ts, double l, double r, string u, string p) {
        text = t;
        timestamp = ts;
        likes = l;
        retweets = r;
        user = u;
        platform = p;
        engagement_score = likes + retweets;
    }
};

vector<Post> readCSV(const string& filepath) {
    vector<Post> posts;
    ifstream file(filepath);
    string line, word;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        Post post;
        getline(ss, word, ',');
        getline(ss, post.text, ',');
        getline(ss, post.sentiment, ',');
        getline(ss, post.timestamp, ',');
        getline(ss, post.user, ',');
        getline(ss, post.platform, ',');
        getline(ss, post.hashtags, ',');
        ss >> post.retweets;
        ss.ignore();
        ss >> post.likes;
        ss.ignore();
        getline(ss, post.country, ',');
        ss >> post.year;
        ss.ignore();
        ss >> post.month;
        ss.ignore();
        ss >> post.day;
        ss.ignore();
        ss >> post.hour;
        posts.push_back(post);
    }
    return posts;
}

class SortingAlgorithms {
public:
    static void bubbleSort(vector<Post>& posts) {
        int n = posts.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (posts[j].engagement_score < posts[j + 1].engagement_score) {
                    swap(posts[j], posts[j + 1]);
                }
            }
        }
    }

    static int partition(vector<Post>& posts, int low, int high) {
        double pivot = posts[high].engagement_score;
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (posts[j].engagement_score > pivot) {
                i++;
                swap(posts[i], posts[j]);
            }
        }
        swap(posts[i + 1], posts[high]);
        return i + 1;
    }

    static void quickSort(vector<Post>& posts, int low, int high) {
        if (low < high) {
            int pi = partition(posts, low, high);
            quickSort(posts, low, pi - 1);
            quickSort(posts, pi + 1, high);
        }
    }

    static void merge(vector<Post>& posts, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<Post> L(posts.begin() + left, posts.begin() + left + n1);
        vector<Post> R(posts.begin() + mid + 1, posts.begin() + mid + 1 + n2);

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (L[i].engagement_score >= R[j].engagement_score) {
                posts[k] = L[i];
                i++;
            } else {
                posts[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            posts[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            posts[k] = R[j];
            j++;
            k++;
        }
    }

    static void mergeSort(vector<Post>& posts, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(posts, left, mid);
            mergeSort(posts, mid + 1, right);
            merge(posts, left, mid, right);
        }
    }

    static void heapify(vector<Post>& posts, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && posts[left].engagement_score > posts[largest].engagement_score)
            largest = left;

        if (right < n && posts[right].engagement_score > posts[largest].engagement_score)
            largest = right;

        if (largest != i) {
            swap(posts[i], posts[largest]);
            heapify(posts, n, largest);
        }
    }

    static void heapSort(vector<Post>& posts) {
        int n = posts.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(posts, n, i);

        for (int i = n - 1; i > 0; i--) {
            swap(posts[0], posts[i]);
            heapify(posts, i, 0);
        }
    }

    static void insertionSort(vector<Post>& posts) {
        for (size_t i = 1; i < posts.size(); ++i) {
            Post key = posts[i];
            int j = i - 1;
            while (j >= 0 && posts[j].engagement_score < key.engagement_score) {
                posts[j + 1] = posts[j];
                --j;
            }
            posts[j + 1] = key;
        }
    }

    static void jumpSort(vector<Post>& posts) {
        int n = posts.size();
        int step = sqrt(n);
        for (int i = 0; i < n; i += step) {
            for (int j = i; j < min(i + step, n); ++j) {
                for (int k = j; k > i && posts[k].engagement_score > posts[k - 1].engagement_score; --k) {
                    swap(posts[k], posts[k - 1]);
                }
            }
        }
    }
};

void displayPosts(const vector<Post>& posts, int limit = 5) {
    for (int i = 0; i < min(limit, (int)posts.size()); i++) {
        cout << "Text: " << posts[i].text << "\n";
        cout << "Engagement Score: " << posts[i].engagement_score << "\n";
        cout << "Platform: " << posts[i].platform << "\n";
        cout << "-------------------\n";
    }
}

int main() {
    string filepath = "../dataset/sentimentdataset.csv";
    vector<Post> posts = readCSV(filepath);

    cout << "Original Posts:\n";
    displayPosts(posts);

    vector<Post> bubbleSortPosts = posts;
    vector<Post> quickSortPosts = posts;
    vector<Post> mergeSortPosts = posts;
    vector<Post> heapSortPosts = posts;
    vector<Post> insertionSortPosts = posts;
    vector<Post> jumpSortPosts = posts;

    cout << "\nBubble Sort:\n";
    SortingAlgorithms::bubbleSort(bubbleSortPosts);
    displayPosts(bubbleSortPosts);

    cout << "\nQuick Sort:\n";
    SortingAlgorithms::quickSort(quickSortPosts, 0, quickSortPosts.size() - 1);
    displayPosts(quickSortPosts);

    cout << "\nMerge Sort:\n";
    SortingAlgorithms::mergeSort(mergeSortPosts, 0, mergeSortPosts.size() - 1);
    displayPosts(mergeSortPosts);

    cout << "\nHeap Sort:\n";
    SortingAlgorithms::heapSort(heapSortPosts);
    displayPosts(heapSortPosts);

    cout << "\nInsertion Sort:\n";
    SortingAlgorithms::insertionSort(insertionSortPosts);
    displayPosts(insertionSortPosts);

    cout << "\nJump Sort:\n";
    SortingAlgorithms::jumpSort(jumpSortPosts);
    displayPosts(jumpSortPosts);

    return 0;
}
