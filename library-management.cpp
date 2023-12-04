#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Book {
public:
    Book(const string& name, const string& author, int id, double price)
        : name(name), author(author), id(id), price(price) {}

    const string& getName() const {
        return name;
    }

    const string& getAuthor() const {
        return author;
    }

    int getId() const {
        return id;
    }

    double getPrice() const {
        return price;
    }

    void displayDetails() const {
        cout << "Book ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Author: " << author << endl;
        cout << "Price: $" << price << endl;
        cout << "------------------------" << endl;
    }

private:
    string name;
    string author;
    int id;
    double price;
};

void saveBooksToFile(const vector<Book>& books, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& book : books) {
            file << book.getName() << ' ' << book.getAuthor() << ' ' << book.getId() << ' ' << book.getPrice() << '\n';
        }
        cout << "Books saved to file successfully." << endl;
    } else {
        cout << "Unable to save books to file." << endl;
    }
}

void loadBooksFromFile(vector<Book>& books, const string& filename) {
    books.clear(); // Clear existing books when loading from a file

    ifstream file(filename);
    if (file.is_open()) {
        string name, author;
        int id;
        double price;
        while (file >> name >> author >> id >> price) {
            books.push_back(Book(name, author, id, price));
        }
        cout << "Books loaded from file successfully." << endl;
    } else {
        cout << "Unable to load books from file." << endl;
    }
}

int main() {
    vector<Book> books;

    while (true) {
        cout << "\nSimple Book Management Menu:" << endl;
        cout << "1. Add Book\n2. Display All Books\n3. Save Books to File\n4. Load Books from File\n5. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1: {
                string name, author;
                int id;
                double price;

                cout << "Enter book name: ";
                getline(cin, name);

                cout << "Enter author name: ";
                getline(cin, author);

                cout << "Enter book ID: ";
                cin >> id;

                cout << "Enter book price: $";
                cin >> price;

                books.push_back(Book(name, author, id, price));

                cout << "Book added successfully." << endl;
                break;
            }
            case 2:
                cout << "\nAll Books:\n";
                for (const auto& book : books) {
                    book.displayDetails();
                }
                break;
            case 3: {
                string filename;
                cout << "Enter filename to save books: ";
                cin >> filename;
                saveBooksToFile(books, filename);
                break;
            }
            case 4: {
                string filename;
                cout << "Enter filename to load books: ";
                cin >> filename;
                loadBooksFromFile(books, filename);
                break;
            }
            case 5:
                cout << "Exiting program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}
