#ifndef MENU_H
#define MENU_H
#include "Book.h"
#include "Client.h"
#include "Librarian.h"
#include "Library.h"
#include <fstream>
#include <string>
#include <conio.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class Menu
{
    public:
        Menu();
        virtual ~Menu();

        string signIn(Library&);
        void LibrarianCommands(Librarian, Library&);
        void ClientCommands(Client, Library&);
        string MenuDisplay(Library&,string, string[][2], int);

    protected:

    private:
};

#endif // MENU_H
