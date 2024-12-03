#include <iostream>
#include <bits/stdc++.h>
using namespace std;


struct Song {
    string title;
    string artist;
    string genre;
    string mood;

    void display() const {
        cout << "Title: " << title
             << ", Artist: " << artist
             << ", Genre: " << genre
             << ", Mood: " << mood << endl;
    }
};

bool compare(Song &a, Song &b, vector<string> &criteria) {
    for (auto &criterion : criteria) {
        if (criterion == "genre" && a.genre != b.genre) {
            return a.genre > b.genre;
        }
        else if (criterion == "artist" && a.artist != b.artist) {
            return a.artist > b.artist;
        }
        else if (criterion == "title" && a.title != b.title) {
            return a.title > b.title;
        }
        else if (criterion == "mood" && a.mood != b.mood) {
            return a.mood > b.mood;
        }
    }
    return false;
}

void bubbleSort(vector<Song> &playlist, vector<string> &criteria) {
    int n = playlist.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (!compare(playlist[j], playlist[j + 1], criteria)) {
                swap(playlist[j], playlist[j + 1]);
            }
        }
    }
}

void countingSort(vector<Song> &playlist,string &key, unordered_map<string, int> &mapping) {
    int n = playlist.size();
    vector<Song> output(n);
    vector<int> count(mapping.size(), 0);

    for (auto &song : playlist) {
        string value;
        if (key == "genre") value = song.genre;
        else if (key == "mood") value = song.mood;

        count[mapping.at(value)]++;
    }

    for (size_t i = 1; i < count.size(); ++i) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        string value;
        if (key == "genre") value = playlist[i].genre;
        else if (key == "mood") value = playlist[i].mood;

        int index = mapping.at(value);
        output[count[index] - 1] = playlist[i];
        count[index]--;
    }

    playlist = output;
}

void countingSortByCharacter(vector<Song> &playlist, int charIndex) {
    int n = playlist.size();
    vector<Song> output(n);
    vector<int> count(256, 0);

    for (const auto &song : playlist) {
        char c = (charIndex < song.title.size()) ? song.title[charIndex] : 0;
        count[c]++;
    }

    for (size_t i = 1; i < count.size(); ++i) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        char c = (charIndex < playlist[i].title.size()) ? playlist[i].title[charIndex] : 0;
        output[count[c] - 1] = playlist[i];
        count[c]--;
    }

    playlist = output;
}

void radixSort(vector<Song> &playlist) {
    size_t maxLength = 0;
    for (const auto &song : playlist) {
        maxLength = max(maxLength, song.title.size());
    }

    for (int charIndex = maxLength - 1; charIndex >= 0; --charIndex) {
        countingSortByCharacter(playlist, charIndex);
    }
}

int main() {
    vector<Song> playlist = {
        {"Rolling in the Deep", "Adele", "Soul", "Powerful"},
        {"Blinding Lights", "The Weeknd", "Pop", "Energetic"},
        {"Hotel California", "Eagles", "Rock", "Chill"},
        {"Yesterday", "The Beatles", "Classic", "Melancholic"},
        {"Lose Yourself", "Eminem", "Hip-Hop", "Motivational"},
        {"Bad Guy", "Billie Eilish", "Pop", "Dark"},
        {"Billie Jean", "Michael Jackson", "Pop", "Groovy"},
        {"Wonderwall", "Oasis", "Rock", "Nostalgic"},
        {"Let It Be", "The Beatles", "Classic", "Inspiring"},
        {"Smells Like Teen Spirit", "Nirvana", "Rock", "Rebellious"}
    };

    cout << "Available criteria: genre, artist, title, mood\n";
    cout << "Enter sorting criteria one by one (type 'done' to finish):\n";

    vector<string> criteria;
    while (true) {
        string criterion;
        cout << "Criterion: ";
        getline(cin, criterion);
        if (criterion == "done") break;
        criteria.push_back(criterion);
    }

    if (criteria.empty()) {
        cout << "No criteria provided. Exiting.\n";
        return 0;
    }

    cout << "Choose sorting algorithm:\n";
    cout << "1. Bubble Sort\n2. Counting Sort (works for genre or mood only)\n3. Radix Sort (works for title only)\n";
    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1:
        bubbleSort(playlist, criteria);
        break;
    case 2: {
        if (criteria[0] != "genre" && criteria[0] != "mood") {
            cout << "Counting Sort works only for 'genre' or 'mood'. Exiting.\n";
            return 0;
        }
        unordered_map<string, int> mapping;
        if (criteria[0] == "genre") {
            mapping = { {"Rock", 0}, {"Pop", 1}, {"Soul", 2}, {"Classic", 3}, {"Hip-Hop", 4} };
        }
        else if (criteria[0] == "mood") {
            mapping = { {"Powerful", 0}, {"Energetic", 1}, {"Chill", 2}, {"Melancholic", 3}, {"Motivational", 4}, {"Dark", 5}, {"Groovy", 6}, {"Nostalgic", 7}, {"Inspiring", 8}, {"Rebellious", 9} };
        }
        countingSort(playlist, criteria[0], mapping);
        break;
    }
    case 3:
        if (criteria[0] != "title") {
            cout << "Radix Sort works only for 'title'. Exiting.\n";
            return 0;
        }
        radixSort(playlist);
        break;
    default:
        cout << "Invalid choice. Exiting.\n";
        return 0;
    }

    cout << "\nSorted Playlist:\n";
    for (const auto& song : playlist) {
        song.display();
    }

    return 0;
}
