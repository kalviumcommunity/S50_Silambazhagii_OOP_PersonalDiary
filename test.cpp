#include <iostream>
#include <string>
#include <vector>
using namespace std;

class DiaryEntry
{
private:
    string date;
    string content;

public:
    void setAll(const string &date, const string &content)
    {
        this->date = date;
        this->content = content;
    }

    string getDate() const
    {
        return this->date;
    }

    string getContent() const
    {
        return this->content;
    }

    void displayEntry() const
    {
        cout << "Date: " << this->date << "\nContent: " << this->content << "\n";
    }
};

class DiaryManager
{
private:
    vector<DiaryEntry*> entries;
    static int totalEntries;
    static int totalDeleted;

public:
    ~DiaryManager() // Destructor to free memory
    {
        for (auto entry : entries)
        {
            delete entry;
        }
    }

    void addEntry(DiaryEntry* entry)
    {
        this->entries.push_back(entry);
        totalEntries++;  // Increment total entries
    }

    void viewEntries() const
    {
        if (this->entries.empty())
        {
            cout << "No entries to display.\n";
            return;
        }

        for (const auto &entry : this->entries)
        {
            entry->displayEntry();
            cout << "----------------------\n";
        }
    }

    void deleteEntry(const string &date)
    {
        for (auto it = this->entries.begin(); it != this->entries.end();)
        {
            if ((*it)->getDate() == date)
            {
                delete *it; // Free memory
                it = this->entries.erase(it);
                totalDeleted++;  // Increment total deleted
            }
            else
            {
                ++it;
            }
        }
    }

    void findEntry(const string &date) const
    {
        bool found = false;
        for (const auto &entry : this->entries)
        {
            if (entry->getDate() == date)
            {
                entry->displayEntry();
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Entry not found for date: " << date << "\n";
        }
    }

    static void displayStats()
    {
        cout << "Total Entries Created: " << totalEntries << "\n";
        cout << "Total Entries Deleted: " << totalDeleted << "\n";
    }
};

// Initialize static variables
int DiaryManager::totalEntries = 0;
int DiaryManager::totalDeleted = 0;

int main()
{
    DiaryManager diaryManager;
    int choice;
    string date, content;

    const int SIZE = 5;
    DiaryEntry* initialEntries[SIZE];

    initialEntries[0] = new DiaryEntry();
    initialEntries[0]->setAll("2024-01-01", "New Year's Day");

    initialEntries[1] = new DiaryEntry();
    initialEntries[1]->setAll("2024-02-14", "Valentine's Day");

    initialEntries[2] = new DiaryEntry();
    initialEntries[2]->setAll("2024-03-17", "St. Patrick's Day");

    initialEntries[3] = new DiaryEntry();
    initialEntries[3]->setAll("2024-07-04", "Independence Day");

    initialEntries[4] = new DiaryEntry();
    initialEntries[4]->setAll("2024-12-25", "Christmas Day");

    cout << "Adding initial entries...\n";
    for (int i = 0; i < SIZE; ++i)
    {
        diaryManager.addEntry(initialEntries[i]);
        cout << "entry " << i + 1 << ": " << initialEntries[i]->getDate() << " - " << initialEntries[i]->getContent() << "\n";
    }

    while (true)
    {
        cout << "\nDiary Manager\n";
        cout << "1. Add Entry\n";
        cout << "2. View Entries\n";
        cout << "3. Delete Entry\n";
        cout << "4. Find Entry\n";
        cout << "5. Display Stats\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "Enter content: ";
            getline(cin, content);
            {
                DiaryEntry* entry = new DiaryEntry();
                entry->setAll(date, content);
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
            DiaryManager::displayStats();
            break;

        case 6:
            return 0;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}
