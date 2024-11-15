#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Abstract base class representing a generic diary entry
class DiaryEntry
{
protected:
    string date;
    string content;

public:
    DiaryEntry() : date("N/A"), content("Empty")
    {
        cout << "Default constructor called for DiaryEntry.\n";
    }

    DiaryEntry(const string &date, const string &content) : date(date), content(content)
    {
        cout << "Parameterized constructor called for DiaryEntry with date: " << date << "\n";
    }

    virtual ~DiaryEntry()
    {
        cout << "Destructor called for DiaryEntry with date: " << date << "\n";
    }

    virtual void displayEntry(bool includeHeader = true) const = 0;

    void setDate(const string &date)
    {
        this->date = date;
    }

    string getDate() const
    {
        return this->date;
    }

    void setContent(const string &content)
    {
        this->content = content;
    }

    string getContent() const
    {
        return this->content;
    }
};

// Derived class representing personal diary entries
class PersonalEntry : public DiaryEntry
{
private:
    string mood;

public:
    PersonalEntry(const string &date, const string &content, const string &mood)
        : DiaryEntry(date, content), mood(mood) {}

    void setMood(const string &mood)
    {
        this->mood = mood;
    }

    string getMood() const
    {
        return this->mood;
    }

    void displayEntry(bool includeHeader = true) const override
    {
        if (includeHeader)
            cout << "---- Personal Entry ----\n";
        cout << "Date: " << this->date << "\nContent: " << this->content << "\n";
        cout << "Mood: " << this->mood << "\n";
    }
};

// Derived class representing work-related diary entries
class WorkEntry : public DiaryEntry
{
private:
    string projectName;

public:
    WorkEntry(const string &date, const string &content, const string &projectName)
        : DiaryEntry(date, content), projectName(projectName) {}

    void setProjectName(const string &projectName)
    {
        this->projectName = projectName;
    }

    string getProjectName() const
    {
        return this->projectName;
    }

    void displayEntry(bool includeHeader = true) const override
    {
        if (includeHeader)
            cout << "---- Work Entry ----\n";
        cout << "Date: " << this->date << "\nContent: " << this->content << "\n";
        cout << "Project: " << this->projectName << "\n";
    }
};

// Class to manage diary statistics
class DiaryStatistics
{
private:
    int totalEntries = 0;
    int totalDeleted = 0;

public:
    void incrementEntries()
    {
        totalEntries++;
    }

    void incrementDeleted()
    {
        totalDeleted++;
    }

    void displayStats() const
    {
        cout << "Total Entries Created: " << totalEntries << "\n";
        cout << "Total Entries Deleted: " << totalDeleted << "\n";
    }
};

// Class to manage multiple diary entries
class DiaryManager
{
private:
    vector<DiaryEntry*> entries;
    DiaryStatistics stats;

public:
    DiaryManager()
    {
        cout << "DiaryManager created.\n";
    }

    ~DiaryManager()
    {
        for (auto entry : entries)
        {
            delete entry;
        }
        cout << "DiaryManager destroyed, memory cleaned.\n";
    }

    void addEntry(DiaryEntry* entry)
    {
        entries.push_back(entry);
        stats.incrementEntries();
    }

    void viewEntries() const
    {
        if (entries.empty())
        {
            cout << "No entries to display.\n";
            return;
        }

        for (const auto &entry : entries)
        {
            entry->displayEntry(true);
            cout << "----------------------\n";
        }
    }

    void deleteEntry(const string &date)
    {
        for (auto it = entries.begin(); it != entries.end();)
        {
            if ((*it)->getDate() == date)
            {
                delete *it;
                it = entries.erase(it);
                stats.incrementDeleted();
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
        for (const auto &entry : entries)
        {
            if (entry->getDate() == date)
            {
                entry->displayEntry(true);
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Entry not found for date: " << date << "\n";
        }
    }

    void displayStats() const
    {
        stats.displayStats();
    }
};

int main()
{
    DiaryManager diaryManager;
    int choice;
    string date, content, mood, projectName;

    const int SIZE = 2;
    DiaryEntry* initialEntries[SIZE];

    initialEntries[0] = new PersonalEntry("2024-01-01", "New Year's Day", "Happy");
    initialEntries[1] = new WorkEntry("2024-02-14", "Project deadline", "Tech Project");

    cout << "Adding initial entries...\n";
    for (int i = 0; i < SIZE; ++i)
    {
        diaryManager.addEntry(initialEntries[i]);
    }

    while (true)
    {
        cout << "\nDiary Manager\n";
        cout << "1. Add Personal Entry\n";
        cout << "2. Add Work Entry\n";
        cout << "3. View Entries\n";
        cout << "4. Delete Entry\n";
        cout << "5. Find Entry\n";
        cout << "6. Display Stats\n";
        cout << "7. Exit\n";
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
            cout << "Enter mood: ";
            getline(cin, mood);
            diaryManager.addEntry(new PersonalEntry(date, content, mood));
            break;

        case 2:
            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "Enter content: ";
            getline(cin, content);
            cout << "Enter project name: ";
            getline(cin, projectName);
            diaryManager.addEntry(new WorkEntry(date, content, projectName));
            break;

        case 3:
            cout << "Diary Entries:\n";
            diaryManager.viewEntries();
            break;

        case 4:
            cout << "Enter date of entry to delete (YYYY-MM-DD): ";
            getline(cin, date);
            diaryManager.deleteEntry(date);
            break;

        case 5:
            cout << "Enter date to find entry (YYYY-MM-DD): ";
            getline(cin, date);
            diaryManager.findEntry(date);
            break;

        case 6:
            diaryManager.displayStats();
            break;

        case 7:
            return 0;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}
