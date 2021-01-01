#include <iostream>
#include <cstdlib>
#include "Book.h"

using namespace std;

Book::Book() {
	title = "#!#EMPTY#!#";
	author = "#!#EMPTY#!#";
	NumOfPages = -1;
	status = "#!#EMPTY#!#";
	idNum = -1;
}

Book::~Book() {
	//dtor
}

//Get
string Book::gettitle() {
	return title;
}

string Book::getauthor() {
	return author;
}

int Book::getNumOfPages() {
	return NumOfPages;
}

string Book::getstatus() {
	return status;
}

int Book::getidNum() {
	return idNum;
}

//Set
void Book::settitle(string newtitle) {
	title = newtitle;
	return;
}

void Book::setauthor(string newauthor) {
	author = newauthor;
	return;
}

void Book::setNumOfPages(int newNumOfPages) {
	NumOfPages = newNumOfPages;
	return;
}

void Book::setstatus(string newstatus) {
	status = newstatus;
	return;
}

void Book::setidNum(int newNum) {
	idNum = newNum;
	return;
}

//Operators
bool Book::operator==(Book nextBook) {
	if (title == nextBook.title && author == nextBook.author && NumOfPages == nextBook.NumOfPages && idNum == nextBook.idNum && status == nextBook.status) {
		return true;
	}
	else {
		return false;
	}
}

//Functions
void Book::displayBookInfo() {
	if (title != "#!#EMPTY#!#" && author != "#!#EMPTY#!#" && NumOfPages != -1) {
		cout << "Selected book is " << title << " by" << author << "." << endl;
		cout << "The book has " << NumOfPages << " pages." << endl;
		if (status != "AVALIABLE") {
			cout << "The book is taken by " << status << "." << endl;
		}
		else {
			cout << "The book " << status << "." << endl;
		}
	}
	else {
		cout << "No book to display." << endl;
	}
	return;
}

string Book::displaybookinfoshort() {
	if (title != "#!#EMPTY#!#" && author != "#!#EMPTY#!#" && NumOfPages != -1) {
		return title + " by " + author;
	}
	else {
		return "NO BOOK";
	}
}

void Book::outputbook() {
	string line;
	ofstream fileOut("data\\books.txt", ios::app);
	if (fileOut.is_open()) {
		fileOut << idNum << char(219) << endl;
		fileOut << title << char(219) << endl;
		fileOut << author << char(219) << endl;
		fileOut << NumOfPages << char(219) << endl;
		fileOut << status << char(219) << endl;
		fileOut.close();
	}
	return;
}

void Book::removeBook() {
	string lineIn, currLine = "", storeLine = "";   //string for input and two strings to chechk
	int runs = 0, idCheck = 5;                      //runs tracks lines to remove, idCehck for change idnumbers
	bool lineCheck, Checked, idChange = false;    //lineCheck Set to true when one string is true, idChange set to true to change idnumbers
	ifstream fileIn("data\\books.txt", ios::in);
	ofstream fileOut("\data\\books.txt", ios::out);
	if (fileIn.is_open() && fileOut) {
		while (getline(fileIn, lineIn)) {
			for (char i : lineIn) {
				if (i != char(219)) {
					currLine = currLine + i;
				}
				else {
					if (stoi(currLine) == idNum && !Checked) {
						lineCheck = true;
						idChange = true;
						Checked = true;
						storeLine = currLine;
						runs = 5;
					}
					else if (runs < 1) {
						lineCheck = false;
						fileOut << currLine << char(219) << endl;
					}
					else if (lineCheck = true) {
						runs--;
					}
					if (runs == 4) {
						if (currLine != title) {     //In case there was an error
							fileOut << storeLine << char(219) << endl;
							fileOut << currLine << char(219) << endl;
							runs = 0;
							Checked = false;
							lineCheck = false;
						}
					}
					if (idChange == true) {
						to_string(stoi(currLine) - 1);
						idCheck--;
						if (idCheck == 0) {
							idCheck = 5;
						}
					}
					currLine = "";
				}
			}
		}
		fileIn.close();
		fileOut.close();
	}
	return;
}

void Book::changeBook(string newTitle, string newAuthor, int newNumPages, string newStatus) {
	ifstream fileIn("data\\books.txt", ios::in);
	ofstream fileOut("data\\books.txt", ios::out);
	string line = "", storeLine = "", lineIn = "";
	int Runs = 0;
	bool lineCheck = false;
	if (fileIn.is_open() && fileOut) {
		while (getline(fileIn, lineIn)) {
			for (char i : lineIn) {
				if (i != char(219)) {
					line = line + i;
				}
				else {
					if (stoi(line) == idNum) {
						storeLine = line;
						lineCheck = true;
						Runs = 5;
					}
					else if (Runs < 1) {
						fileOut << line << char(219) << endl;
					}
					if (lineCheck == true) {
						Runs--;
					}
					if (Runs == 4) {
						if (line != title) {
							fileOut << storeLine << char(219) << endl;
							fileOut << line << char(219) << endl;
							Runs = 0;
						}
						else {
							fileOut << storeLine << char(219) << endl;
							fileOut << newTitle << char(219) << endl;
							fileOut << newAuthor << char(219) << endl;
							fileOut << to_string(newNumPages) << char(219) << endl;
							fileOut << newStatus << char(219) << endl;
						}
					}
				}
				line = "";
			}
		}
		fileOut.close();
		fileIn.close();
	}
	return;
}

void Book::borrowBook(string newOwner) {
	ifstream fileIn("data\\books.txt", ios::in);
	ofstream fileOut("data\\books.txt", ios::out);
	string line = "", storeLine = "", lineIn = "";
	int Runs = 0;
	bool lineCheck = false;
	if (fileIn.is_open() && fileOut) {
		getline(fileIn, lineIn);
		fileIn.close();
		for (char i : lineIn) {
			if (i != char(219)) {
				line = line + i;
			}
			else {
				if (stoi(line) == idNum) {
					storeLine = line;
					lineCheck = true;
					Runs = 5;
				}
				else if (Runs < 1 || Runs == 3 || Runs == 2) {
					fileOut << line << char(219) << endl;
				}
				if (lineCheck == true) {
					Runs--;
				}
				if (Runs == 4) {
					if (line != title) {
						Runs = 0;
					}
					fileOut << storeLine << char(219) << endl;
					fileOut << line << char(219) << endl;
				}
				if (Runs == 1) {
					fileOut << newOwner << char(219) << endl;
				}
			}
			line = "";
		}
		fileOut.close();
	}
	return;
}

void Book::returnBook() {
	ifstream fileIn("data\\books.txt", ios::in);
	ofstream fileOut("data\\books.txt", ios::out);
	string line = "", storeLine = "", lineIn = "";
	int Runs = 0;
	bool lineCheck = false;
	if (fileIn.is_open() && fileOut) {
		getline(fileIn, lineIn);
		fileIn.close();
		for (char i : lineIn) {
			if (i != char(219)) {
				line = line + i;
			}
			else {
				if (stoi(line) == idNum) {
					storeLine = line;
					lineCheck = true;
					Runs = 5;
				}
				else if (Runs < 1 || Runs == 3 || Runs == 2) {
					fileOut << line << char(219) << endl;
				}
				if (lineCheck == true) {
					Runs--;
				}
				if (Runs == 4) {
					if (line != title) {
						Runs = 0;
					}
					fileOut << storeLine << char(219) << endl;
					fileOut << line << char(219) << endl;
				}
				if (Runs == 1) {
					fileOut << "AVALIABLE" << char(219) << endl;
				}
			}
			line = "";
		}
		fileOut.close();
	}
	return;
}
