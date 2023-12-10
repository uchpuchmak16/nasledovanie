#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

class Book {
public:
    Book(std::string title, std::string author, std::string genre)
        : title(title), author(author), genre(genre) {}

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getGenre() const { return genre; }

private:
    std::string title;
    std::string author;
    std::string genre;
};

class Library {
public:
    void addBook(Book* book) {
        books.push_back(book);
    }

    Book* findBookByTitle(std::string title) {
        for (Book* book : books) {
            if (book->getTitle() == title) {
                return book;
            }
        }
        return nullptr;
    }

    bool borrowBook(std::string title) {
        Book* book = findBookByTitle(title);
        if (book != nullptr) {
            auto it = std::find(books.begin(), books.end(), book);
            if (it != books.end()) {
                books.erase(it);
                return true;
            }
        }
        return false;
    }

private:
    std::vector<Book*> books;
};

class User {
public:
    User(std::string name, std::string password)
        : name(name), password(password) {}

    std::string getName() const { return name; }
    std::string getPassword() const { return password; }
    std::vector<Book*> getBorrowedBooks() const { return borrowedBooks; }
    void borrowBook(Book* book) { borrowedBooks.push_back(book); }
    void returnBook(Book* book) {
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), book);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
        }
    }

private:
    std::string name;
    std::string password;
    std::vector<Book*> borrowedBooks;
};

int main() {
    Library library;
    std::map<std::string, User> users;

    // Регистрация пользователя
    std::string username, password;
    std::cout << "Enter your username: ";
    std::cin >> username;
    if (users.find(username) != users.end()) {
        std::cout << "User already exists" << std::endl;
        return 1;
    }
    std::cout << "Enter your password: ";
    std::cin >> password;
    users.insert(std::make_pair(username, User(username, password)));

    // Вход пользователя
    std::string inputUsername, inputPassword;
    std::cout << "Enter your username: ";
    std::cin >> inputUsername;
    std::cout << "Enter your password: ";
    std::cin >> inputPassword;
    auto userIt = users.find(inputUsername);
    if (userIt == users.end() || userIt->second.getPassword() != inputPassword) {
        std::cout << "Invalid username or password" << std::endl;
        return 1;
    }
    User& currentUser = userIt->second;

    // Добавление книг в библиотеку
    Book* t = new Book("The_Great_Gatsby", "F_Scott Fitzgerald", "Classic");
    Book* g = new Book("To_Kill_a_Mockingbird", "Harper_Lee", "Fiction");
    Book* a = new Book("1984", "George_Orwell", "Dystopian");
    library.addBook(t);
    library.addBook(g);
    library.addBook(a);

    // Поиск и аренда книг
    std::string userInput;
    std::cout << "Enter the title of the book you want to find: ";
    std::cin >> userInput;

    Book* foundBook = library.findBookByTitle(userInput);
    if (foundBook != nullptr) {
        if (library.borrowBook(userInput)) {
            currentUser.borrowBook(foundBook);
            std::cout << "Book found and borrowed: " << foundBook->getTitle() << std::endl;
        }
        else {
            std::cout << "Book found but already borrowed" << std::endl;
        }
    }
    else {
        std::cout << "No book found" << std::endl;
    }

    // Проверка взятых книг текущим пользователем
    std::cout << "Books borrowed by " << currentUser.getName() << ":" << std::endl;
    for (Book* book : currentUser.getBorrowedBooks()) {
        std::cout << book->getTitle() << std::endl;
    }

    delete t; // удаляем выделенную память для объектов Book
    delete g;
    delete a;

    return 0;
}


