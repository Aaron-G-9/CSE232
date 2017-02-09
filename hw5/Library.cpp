#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

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

Book::Book(string ISBN, string title, string author, int copyYear, bool isCheckedOut, GENRE genre){

    if (Book::isDataValid(ISBN)){
        this -> ISBN = ISBN;
        this -> title = title;
        this -> author = author;
        this -> copyYear = copyYear;
        this -> isCheckedOut = isCheckedOut;
    }else{
        throw invalid_argument("ISBN is invalid\n");
    }
}


//Not sure what he wants right here...
bool Book::isDataValid(string ISBN){
    return true;
}


//##################################################################


class Patron{
    private:
        string name;
        int cardNum;
        bool isFeeDue;
        float feeAmount;

    public:
        int getCardNum() { return cardNum; }
        bool getIsFeeDue() { return isFeeDue; }
        float getFeeAmount() { return feeAmount; }
        bool operator== (const Patron & other){ return (this->cardNum == other.cardNum); }
        bool operator!= (const Patron & other){ return (this->cardNum != other.cardNum); }
        void setFee(float fee);
        Patron(string, int, bool, float);
        ~Patron();
};

Patron::Patron(string name, int cardNum, bool isFeeDue, float feeAmount){
    this -> name = name;
    this -> cardNum = cardNum;
    this -> isFeeDue = isFeeDue;
    this -> feeAmount = feeAmount;
}

void Patron::setFee(float fee){
    if (fee < 0.01 && fee > -0.01){
        feeAmount = 0.0;
        isFeeDue = false;
    }else{
        feeAmount = fee;
        isFeeDue = true;
    }
    
}

Patron::~Patron(){
    cout << "Patron was destroyed\n";
}

//####################################################################

struct Transaction{
    Book book;
    Patron patron;
    int date;
};


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

void Library::checkOutBook(Patron p, Book b){
    if (!patrons.empty() && !books.empty()){
        if (find(patrons.begin(), patrons.end(), p) != patrons.end() && find(books.begin(), books.end(), b) != books.end()){
            if (!p.getIsFeeDue()){
                Transaction newTrans = {
                    b,
                    p,
                    32
                };
                transactions.push_back(newTrans);
            }
        }
    }
}


int main(){
    cout << "Hello, world";
}