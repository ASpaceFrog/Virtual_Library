#ifndef BOOK_H
#define BOOK_H

#include<string>
#include <fstream>

using namespace std;

class Book {
public:
	Book();
	virtual ~Book();

	//Get
	string gettitle();
	string getauthor();
	int getNumOfPages();
	string getstatus();
	int getidNum();

	//Set
	void settitle(string);
	void setauthor(string);
	void setNumOfPages(int);
	void setstatus(string);
	void setidNum(int);

	//Operators
	bool operator ==(Book);

	//Functions
	void displayBookInfo();
	string displaybookinfoshort();
	void outputbook();
	void removeBook();
	void changeBook(string, string, int, string);
	void borrowBook(string);
	void returnBook();

protected:

private:
	string title;
	string author;
	int NumOfPages;
	string status;
	int idNum;
};

#endif // BOOK_H
