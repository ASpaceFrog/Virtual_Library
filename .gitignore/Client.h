#ifndef CLIENT_H
#define CLIENT_H
#include "Book.h"
#include <string>
#include <fstream>
#include <string>
#define MaxNumOfBwrBooks 5
using namespace std;

class Client{
    public:
        Client();
        virtual ~Client();

        //Get
        int getBook(int);
        string getname();
        string getpassword();
        int getidNum();
        int getnumBwr();

        //Set
        void setBook(int, int);
        void setname(string);
        void setpassword(string);
        void setidNum(int);
        void setnumBwr(int);

        //Operators
        bool operator ==(Client);

        //Functions
        void BorrowBook(int,int);
        void ReturnBwrBook(int);
        void outputclient();
        void removeClient();
        void changeClient(string, string);
        void EmptyClient();
        void displayClientInfo();

    protected:

    private:
        int BooksBorrowed[MaxNumOfBwrBooks];        //Tracks book idnum
        int numBwr;                                 //tracks num of books borrowed
        string name;
        string password;
        int idNum;                                  //tracks Client idnum
};

#endif // CLIENT_H
