#include <iostream>
#include <fstream>	
#include <string>
#include <vector>

using namespace std;

class publication {
public:
	string title;
	int year;
	int cyear=2025;
	int age;	
	publication(string t, int y) : title(t), year(y) {}
	virtual void info() {
		cout << "Title: '" << title << "'. Year: " << year << ". ";
		if (this->restoration()) {
			cout << "Restoration: required." << endl;
		}
		else {
			cout << "Restoration: not required." << endl;
		}
	}
	void get_age() {
		age = cyear - year;
	}
	bool restoration() {
		get_age();
		if (age > 50) {
			return true;
		}
		else {
			return false;
		}
	}
	virtual ~publication() {}
};

class book : public publication {
private:
	string author;
	int pages;
public:
	book(string t, int y, string a, int p) : publication(t, y), author(a), pages(p) {}
	void info() override{
		cout << "Book title: '" << title << "'. Year: " << year << ". " << "Author: " << author << ". Pages: " << pages << ". ";
		if (this->restoration()) {
			cout << "Restoration: required." << endl;
		}
		else {
			cout << "Restoration: not required." << endl;
		}
	}
};

class magazine : public publication {
private:
	int in;
public:
	magazine(string t, int y, int i) : publication(t, y), in(i){}
	void info() override {
		cout << "Magazine title: '" << title << "'. Year: " << year << ". " << "Issue number: " << in << ". ";
		if (this->restoration()) {
			cout << "Restoration: required." << endl;
		}
		else {
			cout << "Restoration: not required." << endl;
		}
	}
};

class newspaper : public publication {
private:
	string date;
public:
	newspaper(string t, int y, string d) : publication(t, y), date(d) {}
	void info() override {
		cout << "Newspaper title: '" << title << "'. Year: " << year << ". " << "Publication date: " << date << ". ";
		if (this->restoration()) {
			cout << "Restoration: required." << endl;
		}
		else {
			cout << "Restoration: not required." << endl;
		}
	}
};
int main() {
	ifstream file("library.txt");
	if (!file.is_open()) {
		cout << "Error" << endl;
	}
	vector<publication*> library;

	string line;
	while (getline(file, line)) {
		string type, title, year, author, pages, issue, date;
		string field;
		int count = 0;

		for (int i = 0; i < line.length(); i++) {
			if (line[i] == ';') {
				if (count == 0) type = field;
				else if (count == 1) title = field;
				else if (count == 2) year = field;
				else if (count == 3) {
					if (type == "Book") author = field;
					else if (type == "Magazine") issue = field;
					else if (type == "Newspaper") date = field;
				}
				else if (count == 4 && type == "Book") pages = field;

				field = "";
				count++;
			}
			else {
				field += line[i];
			}
		}

		if (type == "Book") {
			library.push_back(new book(title, stoi(year), author, stoi(pages)));
		}
		else if (type == "Magazine") {
			library.push_back(new magazine(title, stoi(year), stoi(issue)));
		}
		else if (type == "Newspaper") {
			library.push_back(new newspaper(title, stoi(year), date));
		}
	}
	//library[0]->info(); - для теста
	file.close();
	for (auto pub : library) {
		delete pub;
	}
	library.clear();
}