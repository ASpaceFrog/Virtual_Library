#include <iostream>
#include <cstdlib>
#include "Client.h"
using namespace std;

Client::Client(){
    for(int i = 0; i < MaxNumOfBwrBooks; i++){
        BooksBorrowed[i]=-1;
    }
    name="#!#EMPTY#!#";
    password="#!#EMPTY#!#";
    idNum=-1;
    numBwr=0;
}

Client::~Client(){
    //dtor
}

//Get
int Client::getBook(int BookPlace){
    return BooksBorrowed[BookPlace];
}

string Client::getname(){
    return name;
}

string Client::getpassword(){
    return password;
}

int Client::getidNum(){
    return idNum;
}

int Client::getnumBwr(){
    return numBwr;
}

//Set
void Client::setBook(int BookPlace, int newBook){
    BooksBorrowed[BookPlace]=newBook;
    return;
}

void Client::setname(string newName){
    name=newName;
    return;
}

void Client::setpassword(string newpass){
    password=newpass;
    return;
}

void Client::setidNum(int newNum){
    idNum=newNum;
    return;
}

void Client::setnumBwr(int newNum){
    numBwr=newNum;
    return;
}

//Operators
bool Client::operator==(Client nextClient){
    if(name==nextClient.name && password==nextClient.password && idNum==nextClient.idNum){
        return true;
    }
    else {
        return false;
    }
}

//Functions
//File Operations
void Client::BorrowBook(int BookPlace, int Bookid){
    if(numBwr==MaxNumOfBwrBooks){
        cout << "You have already borrowed the maximum of "<<MaxNumOfBwrBooks<<" books" << endl;
    }
    else{
        string line="", storeline="", lineIn;
        int runs=0;
        bool lineCheck=false, Checked=false;
        ifstream fileIn ("data\\clients.txt", ios::in);
        ofstream fileOut ("data\\clients.txt", ios::out);
        if(fileIn.is_open()&&fileOut){
            while(getline(fileIn, lineIn)){
            for(char i:lineIn){
                if(i!=char(219)){
                    line=line+i;
                }
                else{
                    if(stoi(line)==idNum&&!Checked){
                        Checked=true;
                        lineCheck=true;
                        storeline=line;
                        runs=4+MaxNumOfBwrBooks;
                    }
                    else if(runs<1){
                        lineCheck=false;
                        fileOut<<line<<char(219)<<endl;
                    }
                    else if(lineCheck==true){
                        runs--;
                    }
                    if(runs==3+MaxNumOfBwrBooks){
                        if(line!=name){
                            runs=0;
                        }
                        fileOut<<storeline<<char(219)<<endl;
                        fileOut<<line<<char(219)<<endl;
                    }
                    if(runs==MaxNumOfBwrBooks-BookPlace){
                        fileOut<<Bookid<<char(219)<<endl;
                    }
                    else if(runs>0&&runs<MaxNumOfBwrBooks+1){
                        fileOut<<line<<char(219)<<endl;
                    }
                }
                line="";
            }
            }
            fileIn.close();
        }
    }
    return;
}

void Client::ReturnBwrBook(int BookPlace){
    BooksBorrowed[BookPlace]=-1;    //-1 means no book
    string line="", storeline="", lineIn;
    int runs=0;
    bool lineCheck=false, Checked=false;
    ifstream fileIn ("data\\clients.txt", ios::in);
    ofstream fileOut ("data\\clients.txt", ios::out);
    if(fileIn.is_open()&&fileOut){
        while(getline(fileIn, lineIn)){
        for(char i:lineIn){
            if(i!=char(219)){
                line=line+i;
            }
            else{
                if(stoi(line)==idNum&&!Checked){
                    Checked=true;
                    lineCheck=true;
                    storeline=line;
                    runs=4+MaxNumOfBwrBooks;
                }
                else if(runs<1){
                    lineCheck=false;
                    fileOut<<line<<char(219)<<endl;
                }
                else if(lineCheck==true){
                    runs--;
                }
                if(runs==3+MaxNumOfBwrBooks){
                    if(line!=name){
                        runs=0;
                    }
                    fileOut<<storeline<<char(219)<<endl;
                    fileOut<<line<<char(219)<<endl;
                }
                if(runs==MaxNumOfBwrBooks-BookPlace){
                }
                else if(runs>0&&runs<MaxNumOfBwrBooks+1){
                    fileOut<<line<<char(219)<<endl;
                }
            }
            line="";
        }
        }
        fileIn.close();
    }
    return;
}

void Client::outputclient(){
    string line;
    ofstream fileOut ("data\\clients.txt", ios::app);
    if (fileOut.is_open()){
        fileOut<<idNum<<char(219)<<endl;
        fileOut<<name<<char(219)<<endl;
        fileOut<<password<<char(219)<<endl;
        fileOut<<numBwr<<char(219)<<endl;
        for(int i = 0; i < MaxNumOfBwrBooks; i++){
            fileOut<<BooksBorrowed[i]<<char(219)<<endl;
        }
    }
    fileOut.close();
    return;
}

void Client::removeClient(){
    string lineIn, currLine="", storeLine="";   //string for input and two strings to chechk
    int runs=0, idCheck=4+MaxNumOfBwrBooks;                      //runs tracks lines to remove, idCehck for change idnumbers
    bool lineCheck=false, Checked=false, idChange=false;    //lineCheck Set to true when one string is true, idChange set to true to change idnumbers
    ifstream fileIn ("data\\clients.txt", ios::in);
    ofstream fileOut ("data\\clients.txt", ios::out);
    if(fileIn.is_open()&&fileOut){
        while(getline(fileIn, lineIn)){
        for(char i : lineIn){
            if(i!=char(219)){
                currLine=currLine+i;
            }
            else{
                if(stoi(currLine)==idNum&&!Checked){
                    lineCheck=true;
                    idChange=true;
                    Checked=true;
                    storeLine=currLine;
                    runs=4+MaxNumOfBwrBooks;
                }
                else if(runs<1&&idCheck!=4+MaxNumOfBwrBooks){
                    lineCheck=false;
                    fileOut<<currLine<<char(219)<<endl;
                }
                else if(lineCheck==true){
                    runs--;
                }
                if(runs==3+MaxNumOfBwrBooks){
                    if(currLine!=name){     //In case there was an error
                        fileOut<<storeLine<<char(219)<<endl;
                        fileOut<<currLine<<char(219)<<endl;
                        runs=0;
                        Checked=false;
                        lineCheck=false;
                        idChange=false;
                    }
                }
                if(idChange==true){
                    if(idCheck==4+MaxNumOfBwrBooks&&runs<1){
                        fileOut<<to_string(stoi(currLine)-1)<<char(219)<<endl;
                        idCheck--;
                    }
                    if(idCheck==0){
                        idCheck=4+MaxNumOfBwrBooks;
                        runs=0;
                    }
                }
                currLine="";
            }
        }
        }
        fileIn.close();
        fileOut.close();
    }
    return;
}

void Client::changeClient(string _name, string _password){
    ifstream fileIn ("data\\clients.txt", ios::in);
    ofstream fileOut ("data\\clients.txt", ios::out);
    string line="", storeLine="", lineIn="";
    int Runs=0;
    bool lineCheck=false;
    if(fileIn.is_open()&&fileOut){
        while(getline(fileIn, lineIn)){
        for(char i : lineIn){
            if(i!=char(219)){
                line=line+i;
            }
            else{
                if(stoi(line)==idNum){
                    storeLine=line;
                    lineCheck=true;
                    Runs=4+MaxNumOfBwrBooks;
                }
                else if(Runs<2+MaxNumOfBwrBooks){
                    fileOut<<line<<char(219)<<endl;
                }
                if(lineCheck==true){
                    Runs--;
                }
                if(Runs==3+MaxNumOfBwrBooks){
                    if(line!=name){
                        fileOut<<storeLine<<char(219)<<endl;
                        fileOut<<line<<char(219)<<endl;
                        Runs=0;
                    }
                    else{
                        fileOut<<storeLine<<char(219)<<endl;
                        if(_name=="#!#EMPTY#!#"){
                            fileOut<<_name<<char(219)<<endl;
                        }
                        else{
                            fileOut<<name<<char(219)<<endl;
                        }
                        if(_password=="#!#EMPTY#!#"){
                            fileOut<<password<<char(219)<<endl;
                        }
                        else{
                            fileOut<<_password<<char(219)<<endl;
                        }
                    }
                }
            }
            line="";
        }
        }
        fileOut.close();
        fileIn.close();
    }
    return;
}

void Client::EmptyClient(){
    for(int i = 0; i < MaxNumOfBwrBooks; i++){
        BooksBorrowed[i]=-1;
    }
    name="#!#EMPTY#!#";
    password="#!#EMPTY#!#";
    idNum=-1;
    numBwr=0;
}

void Client::displayClientInfo(){
    cout<<"Username is "<<name<<". Password is "<<password<<"."<<endl;
    cout<<"Client id number is "<<idNum<<"."<<endl;
    for(int i = 0; i < MaxNumOfBwrBooks; i++){
        cout<<"Id num of borrowed book is "<<idNum<<"."<<endl;
    }
    cout<<"Number of borrowed books is "<<numBwr<<"."<<endl;
}
