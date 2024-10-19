#include <iostream>
#include <string>
#include <vector>
using namespace std;

class DiaryEntry
{
private:
    string date;     // Private members for encapsulation
    string content;  // Data hiding is applied here

public:
    // Mutator (setter) for date
    void setDate(const string &date)
    {
        this->date = date;
    }

    // Accessor (getter) for date
    string getDate() const
    {
        return this->date;
    }

    // Mutator (setter) for content
    void setContent(const string &content)
    {
        this->content = content;
    }

    // Accessor (getter) for content
    string getContent() const
    {
        return this->content;
    }

    // Display function to show the entry's details
    void displayEntry() const
    {
        cout << "Date: " << this->date << "\nContent: " << this->content << "\n";
    }
};

class DiaryManager
{
private:
    vector<DiaryEntry*> entries;  // Private vector to store diary entries
    static int totalEntries;      // Static variable to count total entries
    static int totalDeleted;      // Static variable to count deleted entries

public:
    // Destructor to free up dynamically allocated memory
    ~DiaryManager() 
    {
        for (auto entry : entries)
        {
            delete entry;
        }
    }

    // Add a new diary entry
    void addEntry(DiaryEntry* entry)
    {
        this->entries.push_back(entry);
        totalEntries++;  // Increment total entries count
    }

    // View all diary entries
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

    // Delete an entry by its date
    void deleteEntry(const string &date)
    {
        for (auto it = this->entries.begin(); it != this->entries.end();)
        {
            if ((*it)->getDate() == date)
            {
                delete *it;  // Free memory
                it = this->entries.erase(it);  // Erase entry from vector
                totalDeleted++;  // Increment total deleted count
            }
            else
            {
                ++it;
            }
        }
    }

    // Find an entry by its date
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

    // Static function to display stats about entries and deletions
    static void displayStats()
    {
        cout << "Total Entries Created: " << totalEntries << "\n";
        cout << "Total Entries Deleted: " << totalDeleted << "\n";
    }
};

// Initialize static members
int DiaryManager::totalEntries = 0;
int DiaryManager::totalDeleted = 0;

int main()
{
    DiaryManager diaryManager;  // DiaryManager object
    int choice;
    string date, content;

    const int SIZE = 5;
    DiaryEntry* initialEntries[SIZE];  // Array of pointers for initial entries

    // Initialize sample entries
    initialEntries[0] = new DiaryEntry();
    initialEntries[0]->setDate("2024-01-01");
    initialEntries[0]->setContent("New Year's Day");

    initialEntries[1] = new DiaryEntry();
    initialEntries[1]->setDate("2024-02-14");
    initialEntries[1]->setContent("Valentine's Day");

    initialEntries[2] = new DiaryEntry();
    initialEntries[2]->setDate("2024-03-17");
    initialEntries[2]->setContent("St. Patrick's Day");

    initialEntries[3] = new DiaryEntry();
    initialEntries[3]->setDate("2024-07-04");
    initialEntries[3]->setContent("Independence Day");

    initialEntries[4] = new DiaryEntry();
    initialEntries[4]->setDate("2024-12-25");
    initialEntries[4]->setContent("Christmas Day");

    // Add initial entries to the diary
    cout << "Adding initial entries...\n";
    for (int i = 0; i < SIZE; ++i)
    {
        diaryManager.addEntry(initialEntries[i]);
        cout << "Entry " << i + 1 << ": " << initialEntries[i]->getDate() << " - " << initialEntries[i]->getContent() << "\n";
    }

    // Menu for user interaction
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
        cin.ignore();  // Clear the input buffer

        switch (choice)
        {
        case 1:
            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "Enter content: ";
            getline(cin, content);
            {
                DiaryEntry* entry = new DiaryEntry();
                entry->setDate(date);
                entry->setContent(content);
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