#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
class Item {
public:
    Item(const string& title, const string& author, int id) 
        : title(title), author(author), id(id), available(true) {}

    const string& getTitle() const {
        return title;
    }

    const string& getAuthor() const {
        return author;
    }

    int getId() const {
        return id;
    }

    bool isAvailable() const {
        return available;
    }

    virtual void borrowItem() {
        if (available) {
            available = false;
            cout << "Item borrowed successfully." << endl;
        } else {
            cout << "Item is not available for borrowing." << endl;
        }
    }

    virtual void returnItem() {
        available = true;
        cout << "Item returned successfully." << endl;
    }

    virtual void displayDetails() const {
        cout << "Item ID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Status: " << (available ? "Available" : "Not Available") << std::endl;
        cout << "------------------------" << endl;
    }

    virtual char getItemType() const {
        return 'I'; // Base class identifier
    }

    virtual ~Item() {}

protected:
    string title;
    string author;
    int id;
    bool available;
};

class Book : public Item {
public:
    Book(const string& title, const string& author, int id, const string& genre) 
        : Item(title, author, id), genre(genre) {}

    void displayDetails() const override {
        Item::displayDetails();
        cout << "Genre: " << genre << endl;
    }

    char getItemType() const override {
        return 'B'; // Derived class identifier
    }

private:
    string genre;
};

class Library {
public:
    void addItem(Item* item) {
        items.push_back(item);
    }

    void displayAllItems() const {
        if (items.empty()) {
            cout << "No items in the library." << endl;
        } else {
            for (const auto& item : items) {
                item->displayDetails();
            }
        }
    }

    void borrowItem(int itemId) {
        auto it = find_if(items.begin(), items.end(), [itemId](const Item* i) {
            return i->getId() == itemId;
        });

        if (it != items.end()) {
            (*it)->borrowItem();
        } else {
            cout << "Item not found." << endl;
        }
    }

    void returnItem(int itemId) {
        auto it = find_if(items.begin(), items.end(), [itemId](const Item* i) {
            return i->getId() == itemId;
        });

        if (it != items.end()) {
            (*it)->returnItem();
        } else {
            cout << "Item not found." << endl;
        }
    }

    void saveLibraryToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& item : items) {
                file << item->getItemType() << ' '
                     << item->getId() << ' '
                     << item->getTitle() << ' '
                     << item->getAuthor() << ' ';
                if (item->getItemType() == 'B') {
                    Book* book = dynamic_cast<Book*>(item);
                    file << book->getItemType() << ' ';
                }
                file << '\n';
            }
            cout << "Library saved to file successfully." << endl;
        } else {
            cout << "Unable to save library to file." << endl;
        }
    }

    void loadLibraryFromFile(const string& filename) {
        items.clear(); // Clear existing items when loading from a file

        ifstream file(filename);
        if (file.is_open()) {
            char itemType;
            while (file >> itemType) {
                int id;
                string title, author;

                file >> id >> title >> author;

                if (itemType == 'B') {
                    string genre;
                    file >> genre;
                    items.push_back(new Book(title, author, id, genre));
                } else {
                    items.push_back(new Item(title, author, id));
                }
            }
            cout << "Library loaded from file successfully." << endl;
        } else {
            cout << "Unable to load library from file." << endl;
        }
    }

    ~Library() {
        // Clean up allocated memory
        for (auto& item : items) {
            delete item;
        }
    }

private:
    vector<Item*> items;
};

int main() {
    Library library;

    while (true) {
        cout << "\nLibrary Management System Menu:" << endl;
        cout << "1. Add Item\n2. Display All Items\n3. Borrow Item\n4. Return Item\n5. Save Library to File\n6. Load Library from File\n7. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1: {
                string title, author, genre;
                int id;

                cout << "Enter item title: ";
                getline(cin, title);

                cout << "Enter author/genre: ";
                getline(cin, author);

                cout << "Enter item ID: ";
                cin >> id;

                char itemType;
                cout << "Enter item type (I for Item, B for Book): ";
                cin >> itemType;
                cin.ignore(); // Clear the newline character from the input buffer

                if (itemType == 'B') {
                    cout << "Enter book genre: ";
                    getline(cin, genre);
                    library.addItem(new Book(title, author, id, genre));
                } else {
                    library.addItem(new Item(title, author, id));
                }

                cout << "Item added successfully." << endl;
                break;
            }
            case 2:
                cout << "\nAll Items in the Library:\n";
                library.displayAllItems();
                break;
            case 3: {
                int itemId;
                cout << "Enter item ID to borrow: ";
                cin >> itemId;
                library.borrowItem(itemId);
                break;
            }
            case 4: {
                int itemId;
                cout << "Enter item ID to return: ";
                cin >> itemId;
                library.returnItem(itemId);
                break;
            }
            case 5: {
                string filename;
                cout << "Enter filename to save library: ";
                cin >> filename;
                library.saveLibraryToFile(filename);
                break;
            }
            case 6: {
                string filename;
                cout << "Enter filename to load library: ";
                cin >> filename;
                library.loadLibraryFromFile(filename);
                break;
            }
            case 7:
                cout << "Exiting program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}
