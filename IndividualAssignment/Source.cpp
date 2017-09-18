using namespace std;
#include <iostream>
#include <iomanip>
#include "MyFunctions.h"

int main() {
	unordered_map<string,book*> allBooksMap;
	vector<string> allBooksISBNs;
	unordered_map<string, department*> allDepartmentsMap;
	vector<string> allDepartmentCodes;
	string input;

	bool quit = 0;
	while (!quit) {
		try {
			getline(cin, input);
			if (input == "quit") quit = 1;
			else {
				string userCommand = input.substr(0, 2);
				if (userCommand == "B ") {
					//gets the isbn, creates new book if needed and stores the title from input
					string isbn = getNumber(input, 2, 13);
					if (!keyExists(allBooksISBNs, isbn)) {
						allBooksMap[isbn] = new book;
						allBooksISBNs.push_back(isbn);
					}
					string title = getName(input, 16);
					allBooksMap[isbn]->Title = title;
				}
				else if (userCommand == "D ") {
					//get isbn, find book. book must first be defined
					string isbn = getNumber(input, 2, 13);
					if (!keyExists(allBooksISBNs, isbn)) throw BadInput();
					book* currentBook = allBooksMap[isbn];
					if (input.size() <= 18) throw BadInput();
					string opcode = input.substr(15, 2);
					//get and store author
					if (opcode == " A") {
						string author = input.substr(18, input.size() - 18);
						currentBook->Author = author;
					}
					//get and store edition
					else if (opcode == " E") {
						string edition = getNumber(input, 18, input.size()-18);
						currentBook->Edition = edition;
					}
					//get and store date
					else if (opcode == " D") {
						string date = getDate(input, 18);
						currentBook->Date = date;
					}
					else throw BadInput();
				}
				else if (userCommand == "M ") {
					//assign cost to book specified by isbn
					string isbn = getNumber(input, 2, 13);
					if (!keyExists(allBooksISBNs, isbn)) throw BadInput();
					book* currentBook = allBooksMap[isbn];
					string cost = getCost(input, 16);
					//type index changes based on size of the cost, refers to new,used,etc
					int typeIndex = 17 + cost.size();
					string type = input.substr(typeIndex, input.size() - typeIndex);
					if (type == "N") {
						currentBook->Cost.costNew = cost;
					}
					else if (type == "U") {
						currentBook->Cost.costUsed = cost;
					}
					else if (type == "R") {
						currentBook->Cost.costRent = cost;
					}
					else if (type == "E") {
						currentBook->Cost.costElectronic = cost;
					}
					else throw BadInput();
				}
				else if (userCommand == "C ") {
					//find / create department and course number then assign name to course
					string departmentCode = getDepartmentCode(input, 2);
					string courseNumber = getNumber(input, 7, 3);
					if (!keyExists(allDepartmentCodes, departmentCode)) {
						allDepartmentsMap[departmentCode] = new department;
						allDepartmentCodes.push_back(departmentCode);
					}
					department* currentDepartment = allDepartmentsMap[departmentCode];
					if (!keyExists(currentDepartment->courseNumbers, courseNumber)) {
						(currentDepartment->courseMap)[courseNumber] = new course;
						currentDepartment->courseNumbers.push_back(courseNumber);
					}
					course* currentCourse = (currentDepartment->courseMap)[courseNumber];
					string courseName = getName(input, 11);
					currentCourse->Name = courseName;
				}
				else if (userCommand == "A ") {
					//assign book to course. Both must be defined or else exception will be thrown
					string isbn = getNumber(input, 2, 13);
					string departmentCode = getDepartmentCode(input, 16);
					string courseNumber = getNumber(input, 21, 3);
					string sectionNumber = getNumber(input, 25, 3);
					string required = input.substr(28, input.size() - 28);

					if (!keyExists(allDepartmentCodes, departmentCode)) throw BadInput();
					department* currentDepartment = allDepartmentsMap[departmentCode];
					if (!keyExists(currentDepartment->courseNumbers, courseNumber)) throw BadInput();
					course* currentCourse = (currentDepartment->courseMap)[courseNumber];
					if (!keyExists(allBooksISBNs, isbn)) throw BadInput();
					book* currentBook = allBooksMap[isbn];

					if (!keyExists(currentCourse->sectionNumbers, sectionNumber)) {
						currentCourse->sectionMap[sectionNumber] = new section;
						currentCourse->sectionNumbers.push_back(sectionNumber);
					}
					section* currentSection = (currentCourse->sectionMap)[sectionNumber];

					//assign books to section/department isbn lists
					if (!keyExists(currentDepartment->departmentBooksISBNs, isbn)) {
						(currentDepartment->departmentBooksISBNs).push_back(isbn);
					}
					if (!keyExists(currentSection->sectionBooksISBNs, isbn)) {
						(currentSection->sectionBooksISBNs).push_back(isbn);
					}
					//mark as required or optional
					if (required == " R") {
						currentBook->Required = "R";
					}
					else if (required == " O") {
						currentBook->Required = "O";
					}
					else {
						throw BadInput();
					}
				}
				else if (userCommand == "GC") {
					//print books required for course for all sections
					string departmentCode = getDepartmentCode(input, 3);
					string courseNumber = getNumber(input, 8, 3);

					if (!keyExists(allDepartmentCodes, departmentCode)) throw BadInput();
					department* currentDepartment = allDepartmentsMap[departmentCode];
					if (!keyExists(currentDepartment->courseNumbers, courseNumber)) throw BadInput();
					course* currentCourse = (currentDepartment->courseMap)[courseNumber];
					vector<string> sectionList = currentCourse->sectionNumbers;
					//list all of the books by section
					cout << "\n\n";
					for (int i = 0; i < sectionList.size(); ++i) {
						string sectionNumber = sectionList[i];
						section* currentSection = (currentCourse->sectionMap)[sectionNumber];

						vector<string> ISBNs = currentSection->sectionBooksISBNs;
						cout << "Books for Section " << sectionNumber << ":\n\n";
						for (int j = 0; j < ISBNs.size(); ++j) {
							string currentISBN = ISBNs[j];
							book* currentBook = allBooksMap[currentISBN];

							cout << currentISBN << ": " << setw(40) << left << currentBook->Title << currentBook->Required << '\n';
						}
						cout << '\n';
					}

				}
				else if (userCommand == "GS") {
					//print all books for given section
					string departmentCode = getDepartmentCode(input, 3);
					string courseNumber = getNumber(input, 8, 3);
					string sectionNumber = getNumber(input, 12, 3);

					if (!keyExists(allDepartmentCodes, departmentCode)) throw BadInput();
					department* currentDepartment = allDepartmentsMap[departmentCode];
					if (!keyExists(currentDepartment->courseNumbers, courseNumber)) throw BadInput();
					course* currentCourse = (currentDepartment->courseMap)[courseNumber];
					if (!keyExists(currentCourse->sectionNumbers, sectionNumber)) throw BadInput();
					section* currentSection = (currentCourse->sectionMap)[sectionNumber];
					
					vector<string> ISBNs = currentSection->sectionBooksISBNs;
					//Now list all books in section book list
					cout << "\n\nBooks for Section " << sectionNumber << ":\n\n";
					for (int i = 0; i < ISBNs.size(); ++i) {
						string currentISBN = ISBNs[i];
						book* currentBook = allBooksMap[currentISBN];

						cout << currentISBN << ": " << setw(40) << left << currentBook->Title << currentBook->Required << '\n';
					}
					cout << '\n';
				}
				else if (userCommand == "GB") {
					//print all info about specified book. If particular book info is not defined, there will be a blank
					string isbn = getNumber(input, 3, 13);
					if (!keyExists(allBooksISBNs, isbn)) throw BadInput();
					book* currentBook = allBooksMap[isbn];
					cout << "\nTitle: " << currentBook->Title <<
						"\nEdition: " << currentBook->Edition <<
						"\nAuthor: " << currentBook->Author <<
						"\nDate: " << currentBook->Date <<
						"\nISBN: " << isbn <<
						"\nCost" <<
						"\n\tNew: " << currentBook->Cost.costNew <<
						"\n\tUsed: " << currentBook->Cost.costUsed <<
						"\n\tElectronic: " << currentBook->Cost.costElectronic <<
						"\n\tRent: " << currentBook->Cost.costRent <<
						"\nRequired: " << currentBook->Required << "\n\n";
				}
				else if (userCommand == "PB") {
					//print all books by isbn,title,required/optional
					cout << "\n\nAll defined books:\n\n";
					for (int i = 0; i < allBooksISBNs.size(); ++i) {
						string isbn = allBooksISBNs[i];
						book* currentBook = allBooksMap[isbn];

						cout << isbn << ": " << setw(40) << left << currentBook->Title << currentBook->Required << '\n';
					}
					cout << "\n";
				}
				else if (userCommand == "PC") {
					//prints all courses defined
					cout << "\n\n";
					for (int i = 0; i < allDepartmentCodes.size(); ++i) {
						string departmentCode = allDepartmentCodes[i];
						department* currentDepartment = allDepartmentsMap[departmentCode];
						for (int j = 0; j < (currentDepartment->courseNumbers).size(); ++j) {
							string courseNumber = (currentDepartment->courseNumbers)[j];
							course* currentCourse = (currentDepartment->courseMap)[courseNumber];
							cout << departmentCode << ' ' << courseNumber << ' ' << currentCourse->Name << '\n';
						}
					}
					cout << "\n\n";
				}
				else if (userCommand == "PY") {
					//print all books in given month/year or newer
					string dateSpecified = getDate(input, 3);
					string monthSpecified = dateSpecified.substr(0, 2);
					string yearSpecified = dateSpecified.substr(3, 4);

					cout << "\n\n";
					for (int i = 0; i < allBooksISBNs.size(); ++i) {
						string isbn = allBooksISBNs[i];
						book* currentBook = allBooksMap[isbn];
						//print the books and publication dates
						if (currentBook->Date != "") {
							string bookDate = currentBook->Date;
							string bookMonth = bookDate.substr(0, 2);
							string bookYear = bookDate.substr(3, 4);
							if ((bookYear > yearSpecified) || ((bookMonth >= monthSpecified) && (bookYear == yearSpecified))) {
								cout << isbn << ": " << setw(40) << left << currentBook->Title << currentBook->Date << '\n';
							}
							//otherwise don't print book
						}
					}
					cout << "\n\n";
				}
				else if (userCommand == "PD") {
					//print all books in the department
					string departmentCode = getDepartmentCode(input, 3);
					if (!keyExists(allDepartmentCodes, departmentCode)) throw BadInput();
					department* currentDepartment = allDepartmentsMap[departmentCode];
					cout << "\n\n";
					//go through list of books and print each
					for (int i = 0; i < (currentDepartment->departmentBooksISBNs).size(); ++i) {
						string isbn = (currentDepartment->departmentBooksISBNs)[i];
						book* currentBook = allBooksMap[isbn];
						cout << isbn << ": " << setw(40) << left << currentBook->Title << '\n';
					}
					cout << "\n\n";
				}
				else if (userCommand == "PM") {
					//print average minimum and maximum book prices
					string departmentCode = getDepartmentCode(input, 3);
					if (!keyExists(allDepartmentCodes, departmentCode)) throw BadInput();
					department* currentDepartment = allDepartmentsMap[departmentCode];
					
					vector<double> minCosts;
					vector<double> maxCosts;
					//iterates to find all maxes and mins of each book
					for (int i = 0; i < (currentDepartment->departmentBooksISBNs).size(); ++i) {
						string isbn = (currentDepartment->departmentBooksISBNs)[i];
						book* currentBook = allBooksMap[isbn];
						//if theres a cost, add to lists
						if (costExists(currentBook)) {
							//minimum is only concerned with required books
							if (currentBook->Required == "R") {
								minCosts.push_back(compareCost(currentBook, "min"));
							}
							maxCosts.push_back(compareCost(currentBook, "max"));
						}
					}
					//compute averages of each and print them to 2 decimal places
					double avgMin = average(minCosts);
					double avgMax = average(maxCosts);
					cout << "\n\n";
					cout << "Average Minimum Cost: ";
					printf("%.2lf", avgMin);
					cout << '\n';
					cout << "Average Maximum Cost: ";
					printf("%.2lf", avgMax);
					cout << "\n\n\n";
				}
				else {
					throw BadInput();
				}
			}
		}
		catch (BadInput) {
			cout << "\n\n" << "Sorry, Bad Input. Please Check Your Syntax." << "\n\n";
		}
	}

	system("pause");
	
}