#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <conio.h>
#include "Book.h"
#include "Client.h"
#include "Library.h"
#include "Menu.h"

using namespace std;

void setBooksFromFile(Library&);
void setClientsFromFile(Library&);
void setLibrariansFromFile(Library&);
void setNumsFromFile(Library&);

int main() {
	string exit = "";
	Library myLibrary;
	setNumsFromFile(myLibrary);
	setClientsFromFile(myLibrary);
	setLibrariansFromFile(myLibrary);
	setBooksFromFile(myLibrary);
	Menu mymenu;
	while (exit != "DONE") {
		exit = mymenu.signIn(myLibrary);
	}
	cout << "Exiting library..." << endl;
	return 0;
}

void setBooksFromFile(Library& myLibrary) {
	ifstream fileIn("data\\books.txt", ios::in);
	string line = "", lineIn;
	Book temp;
	int CounterTerms = 5, CounterNumBooks = 0;
	if (fileIn.is_open()) {
		while (getline(fileIn, lineIn)) {
			for (char i : lineIn) {
				if (i != char(219)) {
					line = line + i;
				}
				else {
					if (CounterTerms == 5) {
						if (line == "") {
							temp.setidNum(-1);
						}
						temp.setidNum(stoi(line));
					}
					else if (CounterTerms == 4) {
						if (line == "") {
							temp.settitle(line);
						}
						else {
							temp.settitle(line);
						}
					}
					else if (CounterTerms == 3) {
						if (line == "") {
							temp.setauthor("#!#EMPTY#!#");
						}
						else {
							temp.setauthor(line);
						}
					}
					else if (CounterTerms == 2) {
						if (line == "") {
							temp.setNumOfPages(-1);
						}
						else {
							temp.setNumOfPages(stoi(line));
						}
					}
					else {
						if (line == "") {
							temp.setstatus("#!#EMPTY#!#");
						}
						else {
							temp.setstatus(line);
						}
					}
					CounterTerms--;
					if (CounterTerms == 0) {
						CounterTerms = 5;
						CounterNumBooks++;
						myLibrary.setBook(CounterNumBooks, temp);
					}
				}
				line = "";
			}
		}
		fileIn.close();
		CounterNumBooks++;
	}
	return;
}

void setClientsFromFile(Library& myLibrary) {
	ifstream fileIn("data\\books.txt", ios::in);
	string line = "", lineIn;
	Client temp;
	int CounterTerms = 4 + MaxNumOfBwrBooks, CounterNumClients = 0;
	if (fileIn.is_open()) {
		while (getline(fileIn, lineIn)) {
			for (char i : lineIn) {
				if (i != char(219)) {
					line = line + i;
				}
				else {
					if (CounterTerms == 4 + MaxNumOfBwrBooks) {
						if (line == "") {
							temp.setidNum(-1);
						}
						temp.setidNum(stoi(line));
					}
					else if (CounterTerms == 3 + MaxNumOfBwrBooks) {
						if (line == "") {
							temp.setname("#!#EMPTY#!#");
						}
						else {
							temp.setname(line);
						}
					}
					else if (CounterTerms == 2 + MaxNumOfBwrBooks) {
						if (line == "") {
							temp.setpassword("#!#EMPTY#!#");
						}
						else {
							temp.setpassword(line);
						}
					}
					else if (CounterTerms == 1 + MaxNumOfBwrBooks) {
						if (line == "") {
							temp.setnumBwr(0);
						}
						else {
							temp.setnumBwr(stoi(line));
						}
					}
					else {
						if (line == "") {
							temp.setBook((CounterTerms - MaxNumOfBwrBooks), -1);
						}
						else {
							temp.setBook((CounterTerms - MaxNumOfBwrBooks), stoi(line));
						}
					}
					CounterTerms--;
					if (CounterTerms == 0) {
						CounterTerms = 4 + MaxNumOfClients;
						CounterNumClients++;
						myLibrary.setClient(CounterNumClients, temp);
					}
				}
				line = "";
			}
		}
		fileIn.close();
		CounterNumClients++;
	}
	return;
}

void setLibrariansFromFile(Library& myLibrary) {
	ifstream fileIn("data\\librarians.txt", ios::in);
	string line = "", lineIn;
	int CounterTerms = 3, CounterNumLibrarians = 0;
	Librarian temp;
	if (fileIn.is_open()) {
		getline(fileIn, lineIn);
		for (char i : lineIn) {
			if (i != char(219)) {
				line = line + i;
			}
			else {
				if (CounterTerms == 3) {
					myLibrary.setnumBooks(stoi(line));
				}
				else if (CounterTerms == 2) {
					myLibrary.setnumClients(stoi(line));
				}
				else {
					myLibrary.setnumLibrarians(stoi(line));
				}
				CounterTerms--;
				if (CounterTerms == 0) {
					CounterTerms = 3;
					CounterNumLibrarians++;
					myLibrary.setLibrarian(CounterNumLibrarians, temp);
				}
			}
			line = "";
		}
		fileIn.close();
		CounterNumLibrarians++;
	}
	return;
}

void setNumsFromFile(Library& myLibrary) {
	ifstream fileIn("data\\nums.txt", ios::in);
	string line = "", lineIn;
	int Counter = 0;
	if (fileIn.is_open()) {
		while (getline(fileIn, lineIn)) {
			for (char i : lineIn) {
				if (i != char(219)) {
					line = line + i;
				}
				else {
					if (Counter == 0) {
						myLibrary.setnumBooks(stoi(line));
					}
					else if (Counter == 1) {
						myLibrary.setnumClients(stoi(line));
					}
					else {
						myLibrary.setnumLibrarians(stoi(line));
					}
					Counter++;
				}
				line = "";
			}
		}
		fileIn.close();
	}
	return;
}
