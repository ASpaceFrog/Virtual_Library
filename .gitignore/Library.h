#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "Client.h"
#include "Librarian.h"
#include <string>
#include <fstream>
#include <limits>
#include <conio.h>
#define MaxNumOfBooks 100
#define MaxNumOfClients 20
#define MaxNumOfLibrarians 5
using namespace std;

class Library {
    public:
        Library();
        virtual ~Library();

        //Get============================================================================================================
        Book getBook(int);
        int getnumBooks();
        Client getClient(int);
        int getnumClients();
        Librarian getLibrarian(int);
        int getnumLibrarians();

        //Set============================================================================================================
        void setBook(int, Book);
        void setnumBooks(int);
        void setClient(int, Client);
        void setnumClients(int);
        void setLibrarian(int, Librarian);
        void setnumLibrarians(int);

        //FUNCTIONS=======================================================================================================
        int checkInput(int,int);
        //Files operations======================================================================================
        //Books===================================================
        void addbook();                                         //Add new book
        void removebook();                                      //Remove existing book
        void changebook();          //Change existing book
        //Clients=================================================
        void addclient();                                       //Add new client
        void removeclient();                                    //Remove existing client
        void changeclient();                                    //Change existing client
        void changeClientC();
        //Librarians==============================================
        void addlibrarian();                                    //Add new librarian
        void removelibrarian();                                 //Remove existing librarian
        void changelibrarian();                                 //Change existing librarian

        //======================================================================================================
        void displayBooks();
        void displayClients();
        void displayLibrarians();
        void displayBwrdBook(Client);
        void borrowBook(Client);                                //Cleint selects a book to borrow
        void returnBook(Client);                                //Client selects a book to return
        void shiftClients(int);                                 //Shift client id numbers
        void shiftBooks(int);                                   //Shift book id numbers
        void shiftLibrarians(int);                              //Shift librarian id numbers
        void changeNums(int, int, int);                         //Change "total of" numbers
        bool checkClientNames(string);                          //Check for copies
        bool checkBookTitles(string);                           //Check for copies
        bool checkLibrarianNames(string);                       //Check for copies

        //Selection=============================================================================================
        Book findBookFromIdnum(int);                            //Find a book and return the book
        Client findClientC(int, string, Client);                //Find a client and return the client
        int findClientI(int, string, Client);                   //Find a client and return the array number
        Book findBookB(int, string, Book);                      //Find a book and return the book
        int findBookI(int, string, Book);                       //Find a book and return the array number.
        Librarian findLibrarianL(int, string, Librarian);       //Find a librarian and return the librarian
        int findLibrarianI(int, string, Librarian);             //Find a librarian and return the array number
        bool findCheck(int, string, char);                      //True/false return for finding client, book, or librarian

    protected:

    private:
        Book Books[MaxNumOfBooks];                              //Array to store clients
        int numBooks;                                           //Number of current amount of books
        Client Clients[MaxNumOfClients];                        //Array to store clients
        int numClients;                                         //Number of current amount of clients
        Librarian Librarians[MaxNumOfLibrarians];               //Array to store librarians
        int numLibrarians;                                     //Number of current amount of librarians
};



#endif // LIBRARY_H
