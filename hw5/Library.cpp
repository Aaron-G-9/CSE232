//This (large) program was written by Aaron Goodfellow for CSE232
//Although it could be divided up into seperate files, one bigger one is easier on moodle ;) 

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Date.cpp"

using namespace std;

//Definition of class Book
//I like the way C++ defines private and public attributes and methods
//I really like the ability to in-line some simple methods. I think it could
//be a little cleaner, but I was excited by the ability to write everything in one line...

class Book {
    private:
        string ISBN, title, author;
        int copyYear;
        bool isCheckedOut;
        bool isDataValid(string);
    public:
        string getISBN(){ return ISBN; }
        string getTitle(){ return title; }
        string getAuthor(){ return author; }
        int getCopyYear(){ return copyYear; }
        bool getIsCheckedOut(){ return isCheckedOut; }
        void checkIn(){ isCheckedOut = false; }
        void checkOut(){ isCheckedOut = true; }
        enum class GENRE { FICTION, NONFICTION, PERIODICAL, BIOGRAPHY, CHILDREN };
        bool operator== (const Book & other){ return (this->ISBN == other.ISBN); }
        bool operator!= (const Book & other){ return (this->ISBN != other.ISBN); }
        void operator<< (const Book& b1){
            cout << b1.title << "\n" << b1.author << "\n" << b1.ISBN << "\n";
        }
        Book(string, string, string, int, bool, GENRE);
};

//Constructor for Book object

Book::Book(string ISBN, string title, string author, int copyYear, bool isCheckedOut, GENRE genre){

    if (Book::isDataValid(ISBN)){
        this -> ISBN = ISBN;
        this -> title = title;
        this -> author = author;
        this -> copyYear = copyYear;
        this -> isCheckedOut = isCheckedOut;
    }else{
        //Using this instead of error because I'm not importing the little helper header file
        //and I'm on linux :/
        throw invalid_argument("ISBN is invalid\n");
    }
}


//Yup
bool Book::isDataValid(string ISBN){
    //consider ASCII values and remember strings are like vectors 
    //65 - 90
    //97 - 122

    for (auto c : ISBN){
      if (c > 64 && c < 123){
        return true;
      } 
    }
    return false;
}


//##################################################################

//Begin definition of the patron class!

class Patron{
    private:
        string name;
        int cardNum;
        bool isFeeDue;
        float feeAmount;

    public:
        string getName() { return name; }
        int getCardNum() { return cardNum; }
        bool getIsFeeDue() { return isFeeDue; }
        float getFeeAmount() { return feeAmount; }
        bool operator== (const Patron & other){ return (this->cardNum == other.cardNum); }
        bool operator!= (const Patron & other){ return (this->cardNum != other.cardNum); }
        void setFee(float fee);
        Patron(string, int, bool, float);
};

//Constructor for patrons. Did I mention how I like that arrow? I mean the dot operator of 
//java takes up less room, but that arrow just looks cool ;) 
Patron::Patron(string name, int cardNum, bool isFeeDue, float feeAmount){
    this -> name = name;
    this -> cardNum = cardNum;
    this -> isFeeDue = isFeeDue;
    this -> feeAmount = feeAmount;
}

//No direct equality check on floats because that doesn't work
void Patron::setFee(float fee){
    if (fee < 0.01 && fee > -0.01){
        feeAmount = 0.0;
        isFeeDue = false;
    }else{
        feeAmount = fee;
        isFeeDue = true;
    }
    
}


//####################################################################

//Transaction struct with magic Date from Stroustrup
struct Transaction{
    Book book;
    Patron patron;
    Chrono::Date date;
};

//Begin definition of library class! A collection of vectors, basically. 
class Library{
    private: 
        vector<Book> books;
        vector<Patron> patrons;
        vector<Transaction> transactions;
    public:
        void addBook(Book b){ books.push_back(b); }
        void addPatron(Patron p){ patrons.push_back(p); }
        vector<Patron> patronsWhoOwe();
        void checkOutBook(Patron, Book);
};

//Gets those patrons who think they can steal from a library... 
vector<Patron> Library::patronsWhoOwe(){
    if (patrons.empty()){
        throw invalid_argument("No patrons owe money\n");
    }
    vector<Patron> debters;
    for (auto p : patrons){
        if (p.getIsFeeDue()){
            debters.push_back(p);
        }
    }
    return debters;
}

//The biggest method in this whole file, I think. 
//Lots of conditional statements here. Sorry about the nesting.
//Also, the find() method is compliments of the <algorithm> include up there. Pretty nice.
void Library::checkOutBook(Patron p, Book b){
    if (!patrons.empty() && !books.empty()){
        if (find(patrons.begin(), patrons.end(), p) != patrons.end() && find(books.begin(), books.end(), b) != books.end()){
            if (!p.getIsFeeDue()){
                Transaction newTrans = {
                    b,
                    p,
                    Chrono::Date(2017, Chrono::Date::Month::feb, 12)
                };
                transactions.push_back(newTrans);
                cout << b.getTitle() + " was given to " + p.getName() + "\n" ;
                return;
            }
            throw invalid_argument("Patron " + p.getName() + " owes money\n");
        }
        throw invalid_argument("Book or patron does not exist\n");
    }
    throw invalid_argument("No books or no patrons\n");
}


//With these basic tests, it seems to work fine. I have five books, five people and one library.
//It should allow Aaron to checkout TKAM but fail on Corey, because he owes money. Cool little program!
int main(){
    
    Book book1 = Book::Book("abc1", "To Kill A Mockingbird", "Harper Lee", 1996, false, Book::GENRE::FICTION);
    Book book2 = Book::Book("abc2", "Poisonwook Bible", "Barbara Kingsolver", 1996, false, Book::GENRE::FICTION);
    Book book3 = Book::Book("abc3", "Count of Monte Cristo", "Alexander Dumas", 1996, false, Book::GENRE::FICTION);
    Book book4 = Book::Book("abc4", "I Used to Touch the Sky", "Melissa George", 1996, false, Book::GENRE::BIOGRAPHY);
    Book book5 = Book::Book("abc5", "Catcher in the Rye", "J. Salinger", 1996, false, Book::GENRE::FICTION);
    
    Patron patron1 = Patron::Patron("Aaron", 12341, false, 0.00);
    Patron patron2 = Patron::Patron("Melissa", 1232, false, 0.00);
    Patron patron3 = Patron::Patron("Corey", 12343, true, 3.50);
    Patron patron4 = Patron::Patron("Lizzi", 12344, false, 0.00);
    Patron patron5 = Patron::Patron("Caleb", 12345, true, 0.90);


    Library mcfarland = Library::Library();

    mcfarland.addPatron(patron1);
    mcfarland.addPatron(patron2);
    mcfarland.addPatron(patron3);
    mcfarland.addPatron(patron4);
    mcfarland.addPatron(patron5);
    mcfarland.addBook(book1);
    mcfarland.addBook(book2);
    mcfarland.addBook(book3);
    mcfarland.addBook(book4);
    mcfarland.addBook(book5);

    mcfarland.checkOutBook(patron1, book1);
    mcfarland.checkOutBook(patron3, book3);
    vector<Patron> jerks = mcfarland.patronsWhoOwe();
    
    return 0;

}
