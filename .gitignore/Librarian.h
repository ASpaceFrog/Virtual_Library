#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#define MaxNumOfBooks 100
#define MaxNumOfClients 20

#include "Book.h"
#include "Client.h"
#include <fstream>
using namespace std;

class Librarian{
    public:
        Librarian();
        virtual ~Librarian();
        //Get
        string getuser();
        string getpassword();
        int getidNum();
        //Set
        void setuser(string);
        void setpassword(string);
        void setidNum(int);
        //Functions
        void outputlibrarian();
        void removeLibrarian();
        void changeLibrarin(string, string);
    protected:

    private:
        string user;
        string password;
        int idNum;
};

#endif // LIBRARIAN_H
