using namespace std;
#include <iostream>
#include <string>

int main() {
	string input;
	bool quit = 0;
	while (!quit) {
		getline(cin, input);
		if (input == "quit") quit = 1;
		else {
			string charcode = input.substr(0, 2);
			
			if (charcode == "B ") {
				string isbn;
				for (int i = 2; i < 15; ++i) {

				}
			}

			cout << charcode << '\n';
		}
	}
	system("pause");
}