#include <iostream>
#include <cstdlib>
#include "Librarian.h"

using namespace std;
Librarian::Librarian(){
    //ctor
}

Librarian::~Librarian(){
    //dtor
}
//Get
string Librarian::getuser(){
    return user;
}

string Librarian::getpassword(){
    return password;
}

int Librarian::getidNum(){
    return idNum;
}

//Set
void Librarian::setuser(string newUser){
    user=newUser;
    return;

}void Librarian::setpassword(string newpass){
    password=newpass;
    return;
}

void Librarian::setidNum(int newNum){
    idNum=newNum;
    return;
}

//Functions
void Librarian::outputlibrarian(){
    string line;
    ofstream fileOut ("data\\librarians.txt", ios::app);
    if (fileOut.is_open()){
        fileOut<<idNum<<char(219)<<endl;
        fileOut<<user<<char(219)<<endl;
        fileOut<<password<<char(219)<<endl;
        fileOut.close();
    }
    return;
}

void Librarian::removeLibrarian(){
    string lineIn, currLine="", storeLine="";   //string for input and two strings to chechk
    int runs=0, idCheck=5;                      //runs tracks lines to remove, idCehck for change idnumbers
    bool lineCheck, Checked, idChange=false;    //lineCheck Set to true when one string is true, idChange set to true to change idnumbers
    ifstream fileIn ("datalibrarians.txt", ios::in);
    ofstream fileOut ("datalibrarians.txt", ios::out);
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
                    runs=3;
                }
                else if(runs<1){
                    lineCheck=false;
                    fileOut<<currLine<<char(219)<<endl;
                }
                else if(lineCheck=true){
                    runs--;
                }
                if(runs==2){
                    if(currLine!=user){     //In case there was an error
                        fileOut<<storeLine<<char(219)<<endl;
                        fileOut<<currLine<<char(219)<<endl;
                        runs=0;
                        Checked=false;
                        lineCheck=false;
                    }
                }
                if(idChange==true){
                    to_string(stoi(currLine)-1);
                    idCheck--;
                    if(idCheck==0){
                        idCheck=3;
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

void Librarian::changeLibrarin(string newUser, string newPass){
    ifstream fileIn ("data\\librarians.txt", ios::in);
    ofstream fileOut ("data\\librarians.txt", ios::out);
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
                    Runs=3;
                }
                else if(Runs<2){
                    fileOut<<line<<char(219)<<endl;
                }
                else if(lineCheck==true){
                    Runs--;
                }
                if(Runs==2){
                    if(line!=user){
                        fileOut<<storeLine<<char(219)<<endl;
                        fileOut<<line<<char(219)<<endl;
                        Runs=0;
                    }
                    else{
                        fileOut<<storeLine<<char(219)<<endl;
                        fileOut<<newUser<<char(219)<<endl;
                        fileOut<<newPass<<char(219)<<endl;
                    }
                }
            }
            line="";
        }
        }
        fileIn.close();
        fileOut.close();
    }
    return;
}
