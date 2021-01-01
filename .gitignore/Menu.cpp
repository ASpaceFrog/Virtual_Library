#include <iostream>
#include <cstdlib>
#include "Menu.h"

using namespace std;

Menu::Menu() {
	//ctor
}

Menu::~Menu() {
	//dtor
}

string Menu::signIn(Library& myLibrary) {
	cin.clear();
	system("CLS");
	string choice = "", lineIn, line = "", storeline = "";
	string username = "", password = "";
	string options[3][2] = { {">", "Librarian"},{" ", "Client"},{" ", "EXIT"} };
	bool selTrue = false, exitU = false, exitP = false;
	int pos = 0, counter = 0, numInArray = 0, CounterTermsL = 3, CounterTermsC = 4 + MaxNumOfBwrBooks;
	while (!selTrue) {
		cout << "Select what you are signing in as.(Type or select EXIT to exit)" << endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++) {
				cout << options[i][j];
			}
			cout << endl;
		}
		switch (getch()) {
		case KEY_UP:       //Up key
			if (pos != 0) {
				options[pos - 1][0] = options[pos][0];
				options[pos][0] = " ";
				pos--;
			}
			break;
		case 'w':       //Up key
			if (pos != 0) {
				options[pos - 1][0] = options[pos][0];
				options[pos][0] = " ";
			}
			pos--;
			break;
		case KEY_DOWN:       //Down key
			if (pos != 2) {
				options[pos + 1][0] = options[pos][0];
				options[pos][0] = " ";
				pos++;
			}
			break;
		case 's':       //Down key
			if (pos != 2) {
				options[pos + 1][0] = options[pos][0];
				options[pos][0] = " ";
			}
			pos++;
			break;
		case ' ':           //Space
			choice = options[pos][1];
			selTrue = true;
		case '\r':      //Enter
			choice = options[pos][1];
			selTrue = true;
		}
		system("CLS");
	}
	if (choice == "Librarian") {
		ifstream fileIn("data\\librarians.txt", ios::in);
		if (fileIn.is_open()) {
			while (!exitU || !exitP) {
				cout << "Enter your librarian username" << endl;
				getline(cin, username);
				if (username == "EXIT") {
					return "EXIT";
				}
				while (getline(fileIn, lineIn)) {
					for (char i : lineIn) {
						if (i != char(219)) {
							line = line + i;
							cout << line << endl;
						}
						else {
							if (line == username) {
								exitU = true;
								cout << "Enter you password" << endl;
								getline(cin, password);
								counter = 1;
							}
							if (exitU == true && counter == 1) {
								counter--;
								if (line == password) {
									system("CLS");
									LibrarianCommands(myLibrary.getLibrarian(numInArray), myLibrary);
									signIn(myLibrary);
								}
							}
							CounterTermsL--;
							if (CounterTermsL == 0) {
								CounterTermsL = 3;
								numInArray++;
							}
						}
					}
					line = "";
				}
				fileIn.close();
			}
		}
	}
	else if (choice == "Client") {
		ifstream fileIn("data\\clients.txt", ios::in);
		if (fileIn.is_open()) {
			while (!exitU || !exitP) {
				cout << "Enter your client username" << endl;
				getline(cin, username);
				if (username == "EXIT") {
					return "EXIT";
				}
				while (getline(fileIn, lineIn)) {
					for (char i : lineIn) {
						if (i != char(219)) {
							line = line + i;
						}
						else {
							if (line == username) {
								exitU = true;
								cout << "Enter your password" << endl;
								getline(cin, password);
								counter = 1;
							}
							if (exitU == true && counter == 1) {
								counter--;
								if (line == password) {
									system("CLS");
									ClientCommands(myLibrary.getClient(numInArray), myLibrary);
									signIn(myLibrary);
								}
							}
							CounterTermsC--;
							if (CounterTermsC == 0) {
								CounterTermsC = 4 + MaxNumOfBwrBooks;
								numInArray++;
							}
						}
						line = "";
					}
				}
				fileIn.close();
			}
		}

	}
	return "DONE";
}

void Menu::LibrarianCommands(Librarian currLibrarian, Library& myLibrary) {
	string choice = "";
	string optionsML[4][2] = { {">", "Librarian"},{" ", "Client"},{" ","Book"},{" ", "EXIT / SIGN OUT"} };
	string optionsL[4][2] = { {">", "Add Librarian"},{" ","Remove Librarian"},{" ", "Modify Librarian"},{" ", "EXIT"} };
	string optionsC[4][2] = { {">", "Add Client"},{" ","Remove Client"},{" ", "Modify Client"},{" ", "EXIT"} };
	string optionsV[4][2] = { {">", "Add Book"},{" ","Remove Book"},{" ", "Modify Book"},{" ", "EXIT"} };
	MenuDisplay(myLibrary, "What would you like to view commands on?", optionsML, 4);
	if (choice == "EXIT / SIGN OUT") {
		return;
	}
	else if (choice == "Librarian") {
		MenuDisplay(myLibrary, "What command would you like to do?", optionsL, 4);
		if (choice == "Add Librarian") {
			myLibrary.addlibrarian();
			system("CLS");
			LibrarianCommands(currLibrarian, myLibrary);
		}
		else if (choice == "Remove Librarian") {
			myLibrary.removelibrarian();
			system("CLS");
			LibrarianCommands(currLibrarian, myLibrary);
		}
		else if (choice == "Modify Librarian") {
			myLibrary.changelibrarian();
			system("CLS");
			LibrarianCommands(currLibrarian, myLibrary);
		}
		else {
			system("CLS");
			LibrarianCommands(currLibrarian, myLibrary);
		}
	}
	else if (choice == "Client") {
		MenuDisplay(myLibrary, "What command would you like to do?", optionsC, 4);
		if (choice == "Add Client") {
			myLibrary.addclient();
			system("CLS");
			LibrarianCommands(currLibrarian, myLibrary);
		}
		else if (choice == "Remove Client") {
			myLibrary.removelibrarian();
			system("CLS");
			LibrarianCommands(currLibrarian, myLibrary);
		}
		else if (choice == "Modify Client") {
			myLibrary.changeclient();
			system("CLS");
			LibrarianCommands(currLibrarian, myLibrary);
		}
		else {
			system("CLS");
			LibrarianCommands(currLibrarian, myLibrary);
		}

	}
	else {
		MenuDisplay(myLibrary, "What command would you like to do?", optionsL, 4);
		if (choice == "Add Book") {
			myLibrary.addbook();
			system("CLS");
			LibrarianCommands(currLibrarian, myLibrary);
		}
		else if (choice == "Remove Book") {
			myLibrary.removebook();
			system("CLS");
			LibrarianCommands(currLibrarian, myLibrary);
		}
		else if (choice == "Modify Book") {
			myLibrary.changebook();
			system("CLS");
			LibrarianCommands(currLibrarian, myLibrary);
		}
		else {
			system("CLS");
			LibrarianCommands(currLibrarian, myLibrary);
		}
	}
}

void Menu::ClientCommands(Client currClient, Library& myLibrary) {
	string optionsMC[3][2] = { {">", "Client"},{" ","Book"},{" ", "EXIT / SIGN OUT"} };
	string optionsC[2][2] = { {">","Change Login Info"},{" ","EXIT"} };
	string optionsB[4][2] = { {">","Borrow Book"},{" ","Return Book"},{"","View Borrowed Books"},{" ","EXIT"} };
	string choice = "";
	MenuDisplay(myLibrary, "What would you like to view commands on?", optionsMC, 3);
	if (choice == "EXIT / SIGN OUT") {
		return;
	}
	else if (choice == "Client") {
		MenuDisplay(myLibrary, "What would you like to do?", optionsC, 2);
		if (choice == "Change Login Info") {
			myLibrary.changeClientC();
			system("CLS");
			ClientCommands(currClient, myLibrary);
		}
		else {
			system("CLS");
			ClientCommands(currClient, myLibrary);
		}
	}
	else {
		MenuDisplay(myLibrary, "What would you like to do?", optionsB, 4);
		if (choice == "Borrow Book") {
			myLibrary.borrowBook(currClient);
			system("CLS");
			ClientCommands(currClient, myLibrary);
		}
		else if (choice == "Return Book") {
			myLibrary.returnBook(currClient);
			system("CLS");
			ClientCommands(currClient, myLibrary);
		}
		else if (choice == "View Borrowed Books") {
			myLibrary.displayBwrdBook(currClient);
			system("CLS");
			ClientCommands(currClient, myLibrary);
		}
		else {
			system("CLS");
			ClientCommands(currClient, myLibrary);
		}
	}
}

string Menu::MenuDisplay(Library& myLibrary, string question, string options[][2], int arrSize) {
	bool selTrue = false;
	string choice = "";
	int pos = 0;
	while (!selTrue) {
		cout << question << endl;
		for (int i = 0; i < arrSize; i++) {
			for (int j = 0; j < 2; j++) {
				cout << options[i][j];
			}
			cout << endl;
		}
		switch (getch()) {
		case KEY_UP:       //Up key
			if (pos != 0) {
				options[pos - 1][0] = options[pos][0];
				options[pos][0] = " ";
				pos--;
			}
			break;
		case 'w':       //Up key
			if (pos != 0) {
				options[pos - 1][0] = options[pos][0];
				options[pos][0] = " ";
				pos--;
			}
			break;
		case KEY_DOWN:       //Down key
			if (pos != arrSize - 1) {
				options[pos + 1][0] = options[pos][0];
				options[pos][0] = " ";
				pos++;
			}
			break;
		case 's':       //Down key
			if (pos != arrSize - 1) {
				options[pos + 1][0] = options[pos][0];
				options[pos][0] = " ";
				pos++;
			}
			break;
		case ' ':           //Space
			choice = options[pos][1];
			selTrue = true;
		case '\r':      //Enter
			choice = options[pos][1];
			selTrue = true;
		}
		system("CLS");
	}
	return choice;
}

