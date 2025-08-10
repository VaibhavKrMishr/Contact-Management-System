#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

struct Contact {
    std::string name;
    std::vector<std::string> phoneNumbers;
    std::string email;

    void display() const {
    std::cout << "Name: " << name << "\n";
    std::cout << "Phone(s): ";
    for (size_t i = 0; i < phoneNumbers.size(); i++) {
        std::cout << phoneNumbers[i];
        if (i != phoneNumbers.size() - 1) std::cout << ", ";
    }
    if (!email.empty())
        std::cout << "\nEmail: " << email;
    std::cout << "\n----------------------\n";
}

};

std::string toLower(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

class ContactManager {
private:
    std::vector<Contact> contacts;

public:
    ContactManager() {
        loadFromFile();
    }
    

    void addContact() {
    Contact c;
    std::cout << "Enter name: ";
    std::getline(std::cin >> std::ws, c.name);

    // Prevent duplicate name
    for (const auto& existing : contacts) {
        if (toLower(existing.name) == toLower(c.name)) {
            std::cout << "Contact with this name already exists!\n";
            return;
        }
    }

    int count;
    std::cout << "Enter number of phone numbers (default 1): ";
    std::string countInput;
    std::getline(std::cin, countInput);

    if (countInput.empty()) {
        count = 1; // default if empty
    } else {
        try {
            count = std::stoi(countInput);
            if (count <= 0) count = 1; // enforce minimum 1
        } catch (...) {
            count = 1; // fallback if not a number
        }
    }


    for (int i = 0; i < count; i++) {
        std::string phone;
        std::cout << "Phone " << (i + 1) << ": ";
        std::cin >> phone;
        c.phoneNumbers.push_back(phone);
    }

    std::cin.ignore(); // clear leftover newline
    std::cout << "Enter email (optional, press Enter to skip): ";
    std::getline(std::cin, c.email);

    contacts.push_back(c);
    saveToFile();
    std::cout << "Contact added!\n";
}


    void displayAll() const {
        if (contacts.empty()) {
            std::cout << "No contacts found.\n";
            return;
        }
        for (const auto& c : contacts) {
            c.display();
        }
    }

    void searchContact(const std::string& name) const {
        bool found = false;
        std::string searchTerm = toLower(name);

        for (const auto& c : contacts) {
            if (toLower(c.name).find(searchTerm) != std::string::npos) {
                c.display();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No contact found matching: " << name << "\n";
        }
    }

    void deleteContact(const std::string& name) {
        std::string searchTerm = toLower(name);
        auto it = std::remove_if(contacts.begin(), contacts.end(),
            [&](const Contact& c) { return toLower(c.name) == searchTerm; });

        if (it != contacts.end()) {
            contacts.erase(it, contacts.end());
            saveToFile();
            std::cout << "Contact deleted.\n";
        } else {
            std::cout << "Contact not found.\n";
        }
    }

    void saveToFile() const {
        std::ofstream file("contacts.txt");
        if (!file) return;

        for (const auto& c : contacts) {
            file << c.name << '\n';
            file << c.phoneNumbers.size() << '\n';
            for (const auto& num : c.phoneNumbers) {
                file << num << '\n';
            }
            file << c.email << '\n';
        }
    }

    void loadFromFile() {
        std::ifstream file("contacts.txt");
        if (!file) return;

        contacts.clear();
        Contact c;
        while (std::getline(file, c.name)) {
            int count;
            file >> count;
            file.ignore();
            c.phoneNumbers.clear();
            for (int i = 0; i < count; i++) {
                std::string num;
                std::getline(file, num);
                c.phoneNumbers.push_back(num);
            }
            std::getline(file, c.email);
            contacts.push_back(c);
        }
    }
};

int main() {
    ContactManager cm;
    int choice;

    while (true) {
        std::cout << "-------------------------------------\n";
        std::cout << "Contact Management System\n";
        std::cout << "1. Add Contact\n";
        std::cout << "2. Display All Contacts\n";
        std::cout << "3. Search Contact\n";
        std::cout << "4. Delete Contact\n";
        std::cout << "5. Exit\n";
        std::cout << "-------------------------------------\n";
        std::cout << "Enter choice: ";


        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid choice. Try again.\n";
            continue;
        }
        std::cout << "-------------------------------------\n";


        if (choice == 1) {
            cm.addContact();
        } else if (choice == 2) {
            cm.displayAll();
        } else if (choice == 3) {
            std::string name;
            std::cout << "Enter name to search: ";
            std::getline(std::cin >> std::ws, name);
            cm.searchContact(name);
        } else if (choice == 4) {
            std::string name;
            std::cout << "Enter name to delete: ";
            std::getline(std::cin >> std::ws, name);
            cm.deleteContact(name);
        } else if (choice == 5) {
            std::cout << "Exiting...\n";
            return 0;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}
