using namespace std;
#include <iostream>
#include <string>
#include <unordered_map>

class book {
public:
	string Author;
	string Date;
	string Required;
	string Title;
	string Cost;
	string Edition;
};

string getISBN(string input, int start) {
	string isbn;
	for (int i = start; i < (start+13); ++i) {
		int ascii = (int)input[i];
		if ((ascii > 47) && (ascii < 58)) {
			isbn += input[i];
		}
		else throw;
	}
	return isbn;
}

bool bookExists(string key, unordered_map<string, book*> map) {
	unordered_map<string, book*>::const_iterator loc = map.find(key);
	if (loc == map.end()) return false;
	else return true;
}

int main() {
	unordered_map<string,book*> unorderedBooks;
	string input;
	bool quit = 0;
	while (!quit) {
		try {
			getline(cin, input);
			if (input == "quit") quit = 1;
			else {
				string charcode = input.substr(0, 2);
				if (charcode == "B ") {
					string isbn = getISBN(input, 2);
					if (!bookExists(isbn, unorderedBooks)) unorderedBooks[isbn] = new book;
					string title = input.substr(16, input.size() - 16);
					unorderedBooks[isbn]->Title = title;
				}
				else if (charcode == "D ") {
					string isbn = getISBN(input, 2);
					if (!bookExists(isbn, unorderedBooks)) unorderedBooks[isbn] = new book;
					string author = input.substr(16, input.size() - 16);
					unorderedBooks[isbn]->Author = author;
				}
			}
		}
		catch (...) {
			throw;
		}
	}
	string a = unorderedBooks.at("1234567890123")->Title;
	string b = unorderedBooks.at("1234567890123")->Author;
	cout << "\n\n" << a << ' ' << b << '\n';
	system("pause");
}