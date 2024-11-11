#include <iostream>
#include <string>
#include <vector>
using namespace std;

class DiaryEntry
{
protected:
    string date;    
    string content; 

public:
    // Default constructor
    DiaryEntry()
    {
        date = "N/A";
        content = "Empty";
        cout << "Default constructor called for DiaryEntry.\n";
    }

    // Parameterized constructor
    DiaryEntry(const string &date, const string &content)
    {
        this->date = date;
        this->content = content;
        cout << "Parameterized constructor called for DiaryEntry with date: " << date << "\n";
    }

    // Destructor
    virtual ~DiaryEntry()
    {
        cout << "Destructor called for DiaryEntry with date: " << date << "\n";
    }

    // Overloaded display function for different scenarios (demonstrating function overloading)
    void displayEntry() const
    {
        cout << "Date: " << this->date << "\nContent: " << this->content << "\n";
    }

    virtual void displayEntry(bool includeHeader) const
    {
        if (includeHeader)
            cout << "---- Diary Entry ----\n";
        cout << "Date: " << this->date << "\nContent: " << this->content << "\n";
    }

    // Public Mutator (setter) for the date
    void setDate(const string &date)
    {
        this->date = date;
    }

    // Public Accessor (getter) for the date
    string getDate() const
    {
        return this->date;
    }

    // Public Mutator (setter) for the content
    void setContent(const string &content)
    {
        this->content = content;
    }

    // Public Accessor (getter) for the content
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
    PersonalEntry(const string &date, const string &content, const string &mood) : DiaryEntry(date, content), mood(mood) {}

    void setMood(const string &mood)
    {
        this->mood = mood;
    }

    string getMood() const
    {
        return this->mood;
    }

    // Overridden display function demonstrating polymorphism
    void displayEntry(bool includeHeader = true) const override
    {
        if (includeHeader)
            cout << "---- Personal Entry ----\n";
        DiaryEntry::displayEntry(false);
        cout << "Mood: " << this->mood << "\n";
    }
};

// Derived class representing work-related diary entries
class WorkEntry : public DiaryEntry
{
private:
    string projectName;

public:
    WorkEntry(const string &date, const string &content, const string &projectName) : DiaryEntry(date, content), projectName(projectName) {}

    void setProjectName(const string &projectName)
    {
        this->projectName = projectName;
    }

    string getProjectName() const
    {
        return this->projectName;
    }

    // Overridden display function demonstrating polymorphism
    void displayEntry(bool includeHeader = true) const override
    {
        if (includeHeader)
            cout << "---- Work Entry ----\n";
        DiaryEntry::displayEntry(false);
        cout << "Project: " << this->projectName << "\n";
    }
};

// Class to manage multiple diary entries
class DiaryManager
{
private:
    vector<DiaryEntry*> entries;
    static int totalEntries;      
    static int totalDeleted;      

public:
    // Constructor
    DiaryManager()
    {
        cout << "DiaryManager created.\n";
    }

    // Destructor to clean up dynamically allocated memory
    ~DiaryManager() 
    {
        for (auto entry : entries)
        {
            delete entry;
        }
        cout << "DiaryManager destroyed, memory cleaned.\n";
    }

    // Function to add a new diary entry
    void addEntry(DiaryEntry* entry)
    {
        this->entries.push_back(entry);  
        totalEntries++;  
    }

    // Function to view all diary entries
    void viewEntries() const
    {
        if (this->entries.empty())
        {
            cout << "No entries to display.\n";
            return;
        }

        for (const auto &entry : this->entries)
        {
            entry->displayEntry(true);  // Using the overloaded function with header option
            cout << "----------------------\n";
        }
    }

    // Function to delete an entry by its date
    void deleteEntry(const string &date)
    {
        for (auto it = this->entries.begin(); it != this->entries.end();)
        {
            if ((*it)->getDate() == date)
            {
                delete *it;  
                it = this->entries.erase(it); 
                totalDeleted++;  
            }
            else
            {
                ++it;
            }
        }
    }

    // Function to find an entry by its date
    void findEntry(const string &date) const
    {
        bool found = false;
        for (const auto &entry : this->entries)
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

    // Static function to display total entries and deletions
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
    DiaryManager diaryManager; 
    int choice;
    string date, content, mood, projectName;

    // Array to hold initial diary entries
    const int SIZE = 2;
    DiaryEntry* initialEntries[SIZE]; 

    // Initialize sample entries
    initialEntries[0] = new PersonalEntry("2024-01-01", "New Year's Day", "Happy");
    initialEntries[1] = new WorkEntry("2024-02-14", "Project deadline", "Tech Project");

    // Add the initial entries to the diary
    cout << "Adding initial entries...\n";
    for (int i = 0; i < SIZE; ++i)
    {
        diaryManager.addEntry(initialEntries[i]);
    }

    // Menu-driven interface for user interaction
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
            // Add a new personal entry
            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "Enter content: ";
            getline(cin, content);
            cout << "Enter mood: ";
            getline(cin, mood);
            diaryManager.addEntry(new PersonalEntry(date, content, mood));
            break;

        case 2:
            // Add a new work entry
            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "Enter content: ";
            getline(cin, content);
            cout << "Enter project name: ";
            getline(cin, projectName);
            diaryManager.addEntry(new WorkEntry(date, content, projectName));
            break;

        case 3:
            // View all entries
            cout << "Diary Entries:\n";
            diaryManager.viewEntries();
            break;

        case 4:
            // Delete an entry by date
            cout << "Enter date of entry to delete (YYYY-MM-DD): ";
            getline(cin, date);
            diaryManager.deleteEntry(date);
            break;

        case 5:
            // Find an entry by date
            cout << "Enter date to find entry (YYYY-MM-DD): ";
            getline(cin, date);
            diaryManager.findEntry(date);
            break;

        case 6:
            // Display statistics
            DiaryManager::displayStats();
            break;

        case 7:
            return 0;  // Exit the program

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}
