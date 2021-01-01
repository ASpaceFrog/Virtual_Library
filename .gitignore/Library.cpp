#include <iostream>
#include <cstdlib>
#include "Library.h"
using namespace std;

Library::Library(){
    numBooks=0;
    numClients=0;
}

Library::~Library(){
    //dtor
}

//Get=======================================================================================================
Book Library::getBook(int Booknum){
    return Books[Booknum];
}

int Library::getnumBooks(){
    return numBooks;
}

Client Library::getClient(int ClientNum){
    return Clients[ClientNum];
}

int Library::getnumClients(){
    return numClients;
}

Librarian Library::getLibrarian(int Libnum){
    return Librarians[Libnum];
}

int Library::getnumLibrarians(){
    return numLibrarians;
}

//set=======================================================================================================
void Library::setBook(int BookNum, Book newBook){
    Books[BookNum]=newBook;
    return;
}

void Library::setnumBooks(int BookNum){
    numBooks=BookNum;
    return;
}

void Library::setClient(int ClientNum, Client newClient){
    Clients[ClientNum]=newClient;
    return;
}

void Library::setnumClients(int Clientnum){
    numClients=Clientnum;
    return;
}

void Library::setLibrarian(int libnnum, Librarian newLibn){
    Librarians[libnnum]=newLibn;
    return;
}

void Library::setnumLibrarians(int libnnum){
    numLibrarians=libnnum;
    return;
}

//Functions===================================================================================================================================
int Library::checkInput(int Min, int Max){
    bool valid=false;
    int ans;
    while(!valid){
        cin>>ans;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000);
        }
        else if(ans>Max||ans<Min){
            cout<<"Not in range"<<endl;
        }
        else {
            valid=true;
        }
    }
    return ans;
}
//File operations====================================================================================================
//Books=======================================================================================================
void Library::addbook(){
    system("CLS");
    bool exit=false;
    if(numBooks!=MaxNumOfBooks){                                            //Check for room
        string tempS;
        int tempI;
        Book newBook;
        cout<<"Enter the following information regarding the book."<<endl;   //Enter info
        while(!exit){
            cout<<endl<<"Title (Must me unique!): ";
            getline(cin, tempS);
            exit=checkBookTitles(tempS);
        }
        newBook.settitle(tempS);
        cout<<endl<<"Author: ";
        getline(cin, tempS);
        newBook.settitle(tempS);
        cout<<endl<<"Number of Pages: ";
        cin>>tempI;
        cout<<endl;
        newBook.setNumOfPages(tempI);
        newBook.setidNum(numBooks+1);
        Books[numBooks]=newBook;                                            //Add new book to array
        Books[numBooks].outputbook();                                       //Add new book to file
        changeNums(1,0,0);
    }
    else {
        cout << "There is no more room for new books." << endl;
    }
}

void Library::removebook(){
    system("CLS");
    string tempS;
    int tempI;
    bool valid=false;
    Book currBook;
    displayBooks();
    cout<<"Enter the following information regarding the book."<<endl;  //Enter info
    cout<<"NOTE: Removing a book will shift the id numbers of the next books down by one."<<endl;
    cout<<"Name: ";
    cin>>tempS;
    currBook.settitle(tempS);
    cout<<endl<<"Id number: ";
    tempI=checkInput(1,MaxNumOfBooks);
    cout<<endl;
    if(findBookB(tempI, tempS, currBook).getstatus()!="Avaliable"){
        valid=false;
    }
    else if(!(findCheck(tempI, tempS, 'B'))){
        valid=false;
    }
    else{
        valid=true;
    }
    if(valid==true){
        shiftBooks(findBookI(tempI, tempS, currBook));          //Removes book from array
        Books[findBookI(tempI, tempS, currBook)].removeBook();  //Removes book from file
        changeNums(-1,0,0);
    }
    else{
        cout<<"Book is currently borrowed. Cannont remove/."<<endl;
    }
    return;
}

void Library::changebook(){
    system("CLS");
    Book currBook;
    string tempS, newTitle, newAuthor, newStatus;
    bool exit=false;
    int tempI, newPages;
    displayBooks();
    cout<<"Enter the following information regarding the client."<<endl;
    cout<<"NOTE: The id number cannot be changed, nor can you return a client's book for them; they must do that themselves"<<endl;
    cout<<"Title: ";
    cin>>tempS;
    currBook.settitle(tempS);
    cout<<endl<<"Id number: ";
    cin>>tempI;
    cout<<endl;
    if(!findCheck(tempI, tempS, 'B')){
        cout<<"No book found"<<endl;
    }
    else if(findBookB(tempI, tempS, currBook).getstatus()!="Avaliable"){
        cout<<"Book is currently borrowed. Cannot change contents."<<endl;
    }
    else{
        while(!exit){
            cout<<endl<<"What would you like to change the books's title to? (Enter \"#!#EMPTY#!#\" for no change)(Must me unique!)";
            getline(cin, newTitle);
            exit=checkBookTitles(newTitle);
        }
        cout<<"What would you like to change the books's author to? (Enter \"#!#EMPTY#!#\" for no change)"<<endl;
        getline(cin, newAuthor);
        cout<<"What would you like to change the book's number of pages to? (Enter \"-1\" for no change)"<<endl;
        newPages=checkInput(1,INT_MAX);
        cout<<"What would you like to change the books's status to? (Enter \"#!#EMPTY#!#\" for no change)"<<endl;
        getline(cin, newStatus);
        findBookB(tempI, tempS, currBook).changeBook(newTitle, newAuthor, newPages, newStatus);
    }
    return;
}

//Clients===================================================================================================
void Library::addclient(){
    system("CLS");
    bool exit=false;
    if(numClients!=MaxNumOfClients){//Check for room
        string tempS;
        Client newClient;
        cout<<"Enter the following information regarding the client."<<endl;         //Enter info
        while(!exit){
            cout<<endl<<"name (Must me unique!): ";
            getline(cin, tempS);
            exit=checkClientNames(tempS);
        }
        newClient.setname(tempS);
        cout<<endl<<"Default password: ";
        getline(cin, tempS);
        newClient.setpassword(tempS);
        cout<<endl;
        newClient.setidNum(numClients+1);
        newClient.setnumBwr(0);
        Clients[numClients]=newClient;                                              //Add new client to array
        Clients[numClients].outputclient();                                         //Add new client to file
        changeNums(0,1,0);
    }
    else{
        cout << "There is no more room for new clients." << endl;
    }
    return;
}

void Library::removeclient(){
    system("CLS");
    bool valid=true;
    string tempS;
    int tempI;
    Client currClient;
    cout<<"Enter the following information regarding the client."<<endl;                                 //Enter info
    cout<<"NOTE: Removing a client will shift the id numbers of the next clients down by one."<<endl;
    cout<<"Name: ";
    cin>>tempS;
    currClient.setname(tempS);
    cout<<endl<<"Id number: ";
    tempI=checkInput(1,MaxNumOfClients);
    cout<<endl;
    for(int i=0;i<findClientC(tempI, tempS, currClient).getnumBwr();i++){
        if(findClientC(tempI, tempS, currClient).getBook(i)!=1){
                valid=false;
        }
    }
    if(valid==true){
        shiftClients(findClientI(tempI, tempS, currClient));                                                //Remove client from array
        Clients[findClientI(tempI, tempS, currClient)].removeClient();                                      //Remove client from file
        changeNums(0,-1,0);
    }
    else{
        cout<<"Client still has books borrow. Cannot remove client"<<endl;
    }
    return;
}

void Library::changeclient(){
    system("CLS");
    string tempS, newName, newPass;
    bool exit=false;
    int tempI;
    Client currClient;
    bool valid=true;
    cout<<"Enter the following information regarding the client."<<endl;
    cout<<"NOTE: The id number cannot be changed, nor can you return a client's book for them; they must do that themselves"<<endl;
    cout<<"Name: ";
    cin>>tempS;
    currClient.setname(tempS);
    cout<<endl<<"Id number: ";
    tempI=checkInput(1,MaxNumOfClients);
    cout<<endl;
    if(!findCheck(tempI, tempS, 'C')){
        cout<<"No client found"<<endl;
        valid=false;
    }
    else{
        while(!exit){
            cout<<endl<<"What would you like to change the client's user to? (Enter \"#!#EMPTY#!#\" for no change)(Must me unique!)";
            getline(cin, newName);
            exit=checkClientNames(newName);
        }
        cout<<"What would you like to change the client's password to? (Enter \"#!#EMPTY#!#\" for no change)"<<endl;
        getline(cin, newPass);
        currClient.setidNum(tempI);
        findClientC(tempI, tempS, currClient).changeClient(newName, newPass);
    }
    return;
}

void Library::changeClientC(){
    system("CLS");
    string tempS, newName, newPass;
    bool exit=false, valid=false;
    int tempI;
    Client currClient;
    if(!findCheck(tempI, tempS, 'C')){
        cout<<"No client found"<<endl;
        valid=false;
    }
    else{
        while(!exit){
            cout<<endl<<"What would you like to change your username to? (Enter \"#!#EMPTY#!#\" for no change)(Must me unique!)";
            getline(cin, newName);
            exit=checkClientNames(newName);
        }
        cout<<"What would you like to change your password to? (Enter \"#!#EMPTY#!#\" for no change)"<<endl;
        getline(cin, newPass);
        currClient.setidNum(tempI);
        findClientC(tempI, tempS, currClient).changeClient(newName, newPass);
    }
    return;
}

//Librarians=================================================================================================
void Library::addlibrarian(){
    system("CLS");
    bool exit=false;
    if(numClients!=MaxNumOfLibrarians){//Check for room
        string tempS;
        Librarian currLibrarian;
        cout<<"Enter the following information regarding the liberian."<<endl;         //Enter info
        while(!exit){
            cout<<endl<<"Username (Must me unique!): ";
            getline(cin, tempS);
            exit=checkLibrarianNames(tempS);
        }
        currLibrarian.setuser(tempS);
        cout<<endl<<"Default password: ";
        exit=checkClientNames(tempS);
        currLibrarian.setpassword(tempS);
        cout<<endl;
        currLibrarian.setidNum(numLibrarians+1);
        Librarians[numLibrarians]=currLibrarian;                                              //Add new client to array
        Librarians[numLibrarians].outputlibrarian();                                         //Add new client to file
        changeNums(0,0,1);
    }
    else{
        cout << "There is no more room for new clients." << endl;
    }
    return;
}

void Library::removelibrarian(){
    system("CLS");
    string tempS;
    int tempI;
    Librarian currLibrarian;
    if(numLibrarians!=1){
        cout<<"Enter the following information regarding the liberian."<<endl;                                 //Enter info
        cout<<"NOTE: Removing a liberian will shift the id numbers of the next liberians down by one."<<endl;
        cout<<"Name: ";
        cin>>tempS;
        currLibrarian.setuser(tempS);
        cout<<endl<<"Id number: ";
        tempI=checkInput(1,MaxNumOfLibrarians);
        cout<<endl;
        shiftLibrarians(findLibrarianI(tempI, tempS, currLibrarian));                                                //Remove client from array
        Librarians[findLibrarianI(tempI, tempS, currLibrarian)].removeLibrarian();                                      //Remove client from file
        changeNums(0,0,-1);
    }
    else{
        cout<<"There is only one librarian meaing no more can be added."<<endl;
    }
    return;
}

void Library::changelibrarian(){
    system("CLS");
    string tempS, newUser, newPass;
    bool exit=false;
    int tempI;
    Librarian currLibrarian;
    cout<<"Enter the following information regarding the liberian."<<endl;
    cout<<"NOTE: The id number cannot be changed"<<endl;
    cout<<"Name: ";
    cin>>tempS;
    currLibrarian.setuser(tempS);
    cout<<endl<<"Id number: ";
    tempI=checkInput(1,MaxNumOfLibrarians);
    cout<<endl;
    if(!findCheck(tempI, tempS, 'L')){
        cout<<"No librarian found"<<endl;
    }
    else{
        while(!exit){
            cout<<endl<<"What would you like to change the librarians's username to? (Enter \"#!#EMPTY#!#\" for no change)(Must me unique!)";
            getline(cin, newUser);
            exit=checkLibrarianNames(newUser);
        }
        cout<<"What would you like to change the librarian's password to? (Enter \"#!#EMPTY#!#\" for no change)"<<endl;
        getline(cin, newPass);
        currLibrarian.setidNum(tempI);
        findLibrarianL(tempI, tempS, currLibrarian).changeLibrarin(newUser, newPass);
    }
    return;
}

//==========================================================================================
void Library::changeNums(int changeB, int changeC, int changeL){
    ifstream fileIn ("data\\nums.txt", ios::in);
    ofstream fileOut ("data\\nums.txt", ios::out);
    string line="", lineIn="";
    int bookCheck=0;
    if (fileIn.is_open()&&fileOut.is_open()){       //Books first, then clients
        while(getline(fileIn,lineIn)){
        for(char i : lineIn){
            if(i!=char(219)){
                line=line+i;
            }
            else{
                if(bookCheck==0){
                    line=to_string(stoi(line)+changeB); //Books
                    fileOut<<line<<char(219)<<endl;
                    bookCheck++;
                }
                else if(bookCheck==1){
                    line=to_string(stoi(line)+changeC); //Clients
                    fileOut<<line<<char(219)<<endl;
                }
                else{
                    line=to_string(stoi(line)+changeL); //Librarians
                    fileOut<<line<<char(219)<<endl;
                }
                line="";
            }
        }
        }
        fileIn.close();
        fileOut.close();
    }
    return;
}

//Shift Funciotns ====================================================================
void Library::shiftBooks(int bookNum){
    for (int i = bookNum; i < numBooks-1; i++){
        Books[i]=Books[i+1];
    }
    Books[numBooks-2]=Books[numBooks-1];
    numBooks--;
    return;
}

void Library::shiftClients(int clientNum){
    for (int i = clientNum; i < numClients-1; i++){
        Clients[i]=Clients[i+1];
    }
    Clients[numClients-2]=Clients[numClients-1];
    return;
}

void Library::shiftLibrarians(int libnnum){
    for (int i = libnnum; i < numLibrarians-1; i++){
        Librarians[i]=Librarians[i+1];
    }
    Librarians[numLibrarians-2]=Librarians[numLibrarians-1];
    return;
}

//Seleciton Funcitons
Book Library::findBookFromIdnum(int tempI){
    for(int i = 0; i < numBooks; i++){
        if(Books[i].getidNum()==tempI){
            return Books[i];
        }
    }
    cout<<"No book found"<<endl;
}

bool Library::findCheck(int _idNum, string _name, char type){
    switch(type){
        case 'B':
            for(int i = 0; i < numBooks; i++){
                if(Books[i].getidNum()==_idNum&&Books[i].gettitle()==_name){
                    return true;
                }
            }
            return false;
        case 'C':
            for(int i = 0; i < numBooks; i++){
                if(Clients[i].getidNum()==_idNum&&Clients[i].getname()==_name){
                    return true;
                }
            }
            return false;
        case 'L':
            for(int i = 0; i < numBooks; i++){
                if(Librarians[i].getidNum()==_idNum&&Librarians[i].getuser()==_name){
                    return true;
                }
            }
            return false;
    }
}

Client Library::findClientC(int _idnum, string _name, Client currClient){
    for(int i = 0; i < numClients; i++){
        if(Clients[i].getname()==currClient.getname()&&Clients[i].getidNum()==currClient.getidNum()){
            return  Clients[i];
        }
    }
    cout<<"ERROR: No client found"<<endl;
}

int Library::findClientI(int _idnum, string _name, Client currClient){
    for(int i = 0; i < numClients; i++){
        if(Clients[i].getname()==currClient.getname()&&Clients[i].getidNum()==currClient.getidNum()){
            return i;
        }
    }
    cout<<"No client found"<<endl;
}

Book Library::findBookB(int _idnum, string _name, Book currBook){
    for(int i = 0; i < numClients; i++){
        if(Books[i].gettitle()==currBook.gettitle()&&Books[i].getidNum()==currBook.getidNum()){
            return  Books[i];
        }
    }
    cout<<"ERROR: No client found"<<endl;
}

int Library::findBookI(int _idnum, string _name, Book currBook){
    for(int i = 0; i < numClients; i++){
        if(Books[i].gettitle()==currBook.gettitle()&&Books[i].getidNum()==currBook.getidNum()){
            return i;
        }
    }
    cout<<"No client found"<<endl;
}

Librarian Library::findLibrarianL(int _idnum, string _name, Librarian currLibrarian){
    for(int i = 0; i < numClients; i++){
        if(Librarians[i].getuser()==currLibrarian.getuser()&&Librarians[i].getidNum()==currLibrarian.getidNum()){
            return Librarians[i];
        }
    }
    cout<<"ERROR: No client found"<<endl;
}

int Library::findLibrarianI(int _idnum, string _name, Librarian currLibn){
    for(int i = 0; i < numClients; i++){
        if(Librarians[i].getuser()==currLibn.getuser()&&Librarians[i].getidNum()==currLibn.getidNum()){
            return i;
        }
    }
    cout<<"No client found"<<endl;
}
//=========================================================================================
void Library::borrowBook(Client currClient){
    if(currClient.getnumBwr()==MaxNumOfBwrBooks){
        cout<<"You cannot take out any more books."<<endl;
    }
    else{
        int selBook;
        bool valid=false;
        cout<<"Select a book to borrow."<<endl;
        displayBooks();
        selBook=checkInput(1, numBooks);
        selBook--;
        if(Books[selBook].getstatus()!="AVALIABLE"){
            if(Books[selBook].getstatus()=="UNAVALIABLE"){
                cout<<"The book cannot be borrowed."<<endl;
            }
            else{
                cout<<"The book is currently borrowed by someone else."<<endl;
            }
        }
        else{
            currClient.setBook(currClient.getnumBwr(),Books[selBook].getidNum());
            currClient.BorrowBook(currClient.getnumBwr()-1, Books[selBook].getidNum());
            findBookFromIdnum(Books[selBook].getidNum()).borrowBook(currClient.getname());
        }
    }
    return;
}

void Library::returnBook(Client currClient){
    cout<<"Which book would you like to return?"<<endl;
    int selBook;
    Book tempB;
    bool valid=false;
    for(int i = 0; i <currClient.getnumBwr(); i++){
        cout<<i+1<<": ";
        findBookFromIdnum(currClient.getBook(i)).displaybookinfoshort();
    }
    selBook=checkInput(1,currClient.getnumBwr());
    selBook--;
    findBookFromIdnum(currClient.getBook(selBook)).returnBook();
    currClient.ReturnBwrBook(selBook);
    for(int i=selBook; i<MaxNumOfBwrBooks-1; i++){
        currClient.setBook(i, currClient.getBook(i+1));
    }
    currClient.setBook(currClient.getnumBwr()-2,currClient.getnumBwr()-1);
    currClient.setnumBwr(currClient.getnumBwr()-1);
    return;
}

void Library::displayBooks(){
    system("CLS");
    cout<<"Here is the list of books"<<endl;
    for (int i=0; i<numBooks; i++){
        cout<<i+1<<":"<<endl;
        Books[i].displayBookInfo();
        cout<<endl;
    }
    return;
}

void Library::displayClients(){
    system("CLS");
    cout<<"Here is the list of clients"<<endl;
    for (int i=0; i<numClients; i++){
        cout<<i+1<<":"<<endl;
        Clients[i].displayClientInfo();
        cout<<endl;
    }
    return;
}

void Library::displayBwrdBook(Client currClient){
    for (int i=0; i<currClient.getnumBwr(); i++){
        findBookFromIdnum(currClient.getBook(i)).displaybookinfoshort();
    }
    return;
}

//Checks======================================================
bool Library::checkBookTitles(string _title){
    for (int i=0; i<numBooks; i++){
        if (Books[i].gettitle()==_title){
            return false;
        }
    }
    return true;
}

bool Library::checkClientNames(string _name){
    for (int i=0; i<numClients; i++){
        if (Clients[i].getname()==_name){
            return false;
        }
    }
    return true;
}

bool Library::checkLibrarianNames(string _user){
    for (int i=0; i<numLibrarians; i++){
        if (Librarians[i].getuser()==_user){
            return false;
        }
    }
    return true;
}
