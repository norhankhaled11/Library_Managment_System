// library final.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;
struct Bookstruct {
	int id;
	string title;
	string author;
	string genre;
	int quantity;
};

vector<Bookstruct>books;//global variable
//Book data type and books is variable  

void addBook(string filePath)
{
	Bookstruct newbook;
	bool uniqueID = false;
	while (!uniqueID) {
		uniqueID = true;
		cout << "Creat a unique ID that consists of 4 numbers for the new book \n";
		cin >> newbook.id;
		for (auto i = books.begin(); i != books.end(); ++i) {
			if (i->id == newbook.id) {// Check the ID of the currunt book matches the user's ID
				uniqueID = false;
				cout << "This ID is already used, create another one\n";
				break;
			}
		}
	}
	cin.ignore();// Prevents the string getline error 
	cout << "Enter book title\n";
	getline(cin, newbook.title);
	cout << "Enter book author\n";
	getline(cin, newbook.author);
	cout << "Enter book genre \n";
	getline(cin, newbook.genre);
	cout << "Enter book quantity\n";
	cin >> newbook.quantity;
	books.push_back(newbook); // Push back adds an element to the end of a vector dynamically 
	cout << "Book added correctly\n";


	ofstream output;
	output.open(filePath, ios::app);//
	output << setw(6) << left << newbook.id << "|";
	output << setw(51) << left << newbook.title << "|";
	output << setw(25) << left << newbook.author << "|";
	output << setw(25) << left << newbook.genre << "|";
	output << setw(14) << left << newbook.quantity << endl;
	output.close();

}

void savechanges(vector<Bookstruct>books, string filePath) {

	ofstream outFile(filePath);
	if (outFile.is_open())
	{
		// write the first line that contain columns names
		outFile << setw(6) << left << "ID" << "|";
		outFile << setw(51) << left << "Title" << "|";
		outFile << setw(25) << left << "Author" << "|";
		outFile << setw(25) << left << "Genre" << "|";
		outFile << setw(14) << left << "Quantity" << endl;

		// write the separating line
		outFile << "------------------------------------------------------------------------------------------------------------------------------";
		outFile << endl;

		// write the updated file
		for (int i = 0; i < books.size(); i++)
		{

			Bookstruct book = books[i];// We created a new struct named book to pass the vector's data to the struct
			outFile << setw(6) << left << book.id << "|";
			outFile << setw(51) << left << book.title << "|";
			outFile << setw(25) << left << book.author << "|";
			outFile << setw(25) << left << book.genre << "|";
			outFile << setw(14) << left << book.quantity << endl;

		}

		outFile.close();

	}
	else {
		cout << "Unable to open file \n";
	}
}


void deleteBook(string filePath) {
	int id;
	cout << "Enter the ID of the book you want to delete: ";
	cin >> id;

	for (auto i = books.begin(); i != books.end(); ++i) {
		if (i->id == id) {
			books.erase(i);// Function of the vector used to remove elements from specific position in vector
			savechanges(books, filePath);
			cout << "Book deleted successfully\n";
			return;
		}
	}
	cout << "Book not found, enter another ID\n";
}

void updateBook(string filePath) {
	int id;
	cout << "Enter the ID of the book you want to update: \n";
	cin >> id;
	cin.ignore();
	for (int i = 0; i < books.size(); i++)
	{
		Bookstruct book = books[i];
		if (book.id == id)
		{
			cout << "Enter new book title: \n";
			cin.ignore();
			getline(cin, book.title);
			cout << " Enter new book author: \n";
			getline(cin, book.author);
			cout << "Enter new book genre: \n";
			getline(cin, book.genre);
			cout << "Enter the new available quantity: \n";
			cin >> book.quantity;
			books[i] = book;// To copy updated book into the vector 

			savechanges(books, filePath);
			cout << "Book updated successfully\n";
			return;
		}
	}
	cout << "Book not found\n";
}

void displayBooks(string filePath) {
	ifstream input;
	input.open(filePath);
	if (!input.is_open()) {
		cout << "Error opening file: " << filePath << endl;
		return;
	}
	string line;
	while (getline(input, line)) {
		cout << line << endl;
	}
	input.close();
}
vector<Bookstruct> LoadBooks(string filePath) {// Function type returns a vector
	vector<Bookstruct> books;
	ifstream file(filePath);

	if (!file.is_open()) {
		cerr << "Unable to open file" << endl;
		return books;
	}
	string line;
	getline(file, line); // Skip the header line
	getline(file, line); // Skip separating line
	while (getline(file, line)) {
		Bookstruct book;
		stringstream ss(line);

		char delimiter;
		ss >> book.id >> delimiter; // Fills the struct with the string stream's data
		getline(ss, book.title, '|');
		getline(ss, book.author, '|');
		getline(ss, book.genre, '|');
		ss >> book.quantity;

		books.push_back(book);
	}
	file.close();
	return books;
}

void searchBooks(const vector<Bookstruct>& books, const string& query) {
	bool found = false;

	for (const auto& book : books) {

		if (book.title.find(query) != string::npos ||// npos means postision not found
			book.author.find(query) != string::npos ||
			book.genre.find(query) != string::npos) {
			cout << endl;
			cout << "ID:" << book.id << endl;
			cout << "Title: " << book.title << endl;
			cout << "Author: " << book.author << endl;
			cout << "Genre: " << book.genre << endl;
			cout << "Quantity: " << book.quantity << endl;
			cout << endl;
			cout << "----------------------------------------------" << endl;
			found = true;
		}
	}

	if (!found) {
		cout << "No books found matching the query: " << query << endl;
	}
}



int main()
{
	string filePath = "C://Users//Norhan Khaled//Downloads//Books.txt";
	books = LoadBooks(filePath);
	string txt;
	int choice;
	string query;
	do
	{
		cout << setw(98) << "------------------------------------\n";
		cout << setw(98) << "| library mangement system menu:   |\n";
		cout << setw(98) << "|                                  |\n";
		cout << setw(98) << "| 1) Add a Book                    |\n";
		cout << setw(98) << "| 2) Delete a Book                 |\n";
		cout << setw(98) << "| 3) Update a Book                 |\n";
		cout << setw(98) << "| 4) Search for book               |\n";
		cout << setw(98) << "| 5) Display all Books             |\n";
		cout << setw(98) << "| 6) Exit                          |\n";
		cout << setw(98) << "------------------------------------\n";
		cout << endl;
		cout << endl;

		cout << "Enter the number of your choice :\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			addBook(filePath);
			break;
		case 2:
			deleteBook(filePath);
			break;
		case 3:
			updateBook(filePath);
			break;
		case 4:
			cout << "Enter the title, author, or genre to search: ";
			cin.ignore();
			getline(cin, query);
			searchBooks(books, query);
			break;
		case 5:
			displayBooks(filePath);
			break;
		case 6:
			cout << "Exit program\n";
			break;
		default:
			cout << " Invalid choice .try again\n";
		}
	} while (choice != 6);
	return false;
}