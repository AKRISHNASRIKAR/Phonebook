#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> // for std::transform
#include <cctype>    // for std::tolower

using namespace std;

// Trim whitespace from the beginning and end of a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Convert a string to lowercase
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char c) { return tolower(c); });
    return lowerStr;
}

class Contact {
public:
    Contact(const string& name, const string& phoneNumber)
        : name(name), phoneNumber(phoneNumber) {}

    const string& getName() const { return name; }
    const string& getPhoneNumber() const { return phoneNumber; }

private:
    string name;
    string phoneNumber;
};

class Phonebook {
public:
    void addContact(const string& name, const string& phoneNumber) {
        contacts.push_back(Contact(name, phoneNumber));
        saveToFile("contacts.txt"); // Save contacts to file after adding a new contact
    }

    vector<Contact> searchContacts(const string& query) {
        vector<Contact> result;
        string lowercaseQuery = toLower(query); // Convert query to lowercase
        for (const auto& contact : contacts) {
            string lowercaseName = toLower(contact.getName()); // Convert contact name to lowercase
            if (lowercaseName.find(lowercaseQuery) != string::npos ||
                contact.getPhoneNumber().find(query) != string::npos) {
                result.push_back(contact);
            }
        }
        return result;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (const auto& contact : contacts) {
            file << contact.getName() << "," << contact.getPhoneNumber() << endl;
        }
        file.close();
    }

private:
    vector<Contact> contacts;
};

int main() {
    Phonebook phonebook;

    // Add some sample contacts
    phonebook.addContact("John Doe", "1234567890");
    phonebook.addContact("Jane Smith", "9876543210");

    int choice;
    do {
        cout << "Phonebook Menu:" << endl;
        cout << "1. Search Contact" << endl;
        cout << "2. Add Contact" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline character from previous input

        switch (choice) {
            case 1: {
                // Manual search for a contact
                string searchQuery;
                cout << "Enter search query: ";
                getline(cin, searchQuery);
                searchQuery = trim(searchQuery); // Trim whitespace from search query
                vector<Contact> searchResults = phonebook.searchContacts(searchQuery);
                if (searchResults.empty()) {
                    cout << "No matching contacts found." << endl;
                } else {
                    cout << "Search Results:" << endl;
                    for (const auto& contact : searchResults) {
                        cout << "Name: " << contact.getName() << ", Phone: " << contact.getPhoneNumber() << endl;
                    }
                }
                break;
            }
            case 2: {
                // Add a new contact
                string newName, newPhoneNumber;
                cout << "Enter name of new contact: ";
                getline(cin, newName);
                cout << "Enter phone number of new contact: ";
                getline(cin, newPhoneNumber);
                phonebook.addContact(newName, newPhoneNumber);
                cout << "Contact added successfully." << endl;
                break;
            }
            case 3:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 3);

    return 0;
}
