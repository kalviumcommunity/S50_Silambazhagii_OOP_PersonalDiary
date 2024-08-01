#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DiaryEntry {
private:
    string date;
    string content;

public:
    void setAll(const string& entryDate, const string& entryContent) {
        date = entryDate;
        content = entryContent;
    }

    string getDate() const {
        return date;
    }

    string getContent() const {
        return content;
    }

    void displayEntry() const {
        cout << "Date: " << date << "\nContent: " << content << "\n";
    }
};

class DiaryManager {
private:
    vector<DiaryEntry> entries;

public:
    void addEntry(const DiaryEntry& entry) {
        entries.push_back(entry);
    }

    void viewEntries() const {
        if (entries.empty()) {
            cout << "No entries to display.\n";
            return;
        }

        for (const auto& entry : entries) {
            entry.displayEntry();
            cout << "----------------------\n";
        }
    }

    void deleteEntry(const string& date) {
        for (auto it = entries.begin(); it != entries.end(); ) {
            if (it->getDate() == date) {
                it = entries.erase(it);
            } else {
                ++it;
            }
        }
    }

    void findEntry(const string& date) const {
        bool found = false;
        for (const auto& entry : entries) {
            if (entry.getDate() == date) {
                entry.displayEntry();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Entry not found for date: " << date << "\n";
        }
    }
};

int main() {
    DiaryManager diaryManager;
    int choice;
    string date, content;

    while (true) {
        cout << "\nDiary Manager\n";
        cout << "1. Add Entry\n";
        cout << "2. View Entries\n";
        cout << "3. Delete Entry\n";
        cout << "4. Find Entry\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the leftover newline character

        switch (choice) {
            case 1:
                cout << "Enter date (YYYY-MM-DD): ";
                getline(cin, date);
                cout << "Enter content: ";
                getline(cin, content);
                {
                    DiaryEntry entry;
                    entry.setAll(date, content);
                    diaryManager.addEntry(entry);
                }
                break;

            case 2:
                cout << "Diary Entries:\n";
                diaryManager.viewEntries();
                break;

            case 3:
                cout << "Enter date of entry to delete (YYYY-MM-DD): ";
                getline(cin, date);
                diaryManager.deleteEntry(date);
                break;

            case 4:
                cout << "Enter date to find entry (YYYY-MM-DD): ";
                getline(cin, date);
                diaryManager.findEntry(date);
                break;

            case 5:
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}

