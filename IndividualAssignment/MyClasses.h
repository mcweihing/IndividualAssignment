#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class BadInput { };

//contains the various costs
class cost {
public:
	string costNew;
	string costUsed;
	string costRent;
	string costElectronic;
};
//contains all details of a book
class book {
public:
	string Title;
	string Edition;
	string Author;
	string Date;
	string Required;
	cost Cost;
};
//sections only contain book isbns that are used in a section
class section {
public:
	vector<string> sectionBooksISBNs;
};
//maps all sections of a course and contains te name of course
class course {
public:
	unordered_map<string, section*> sectionMap;
	vector<string> sectionNumbers;
	string Name;
};
//contains map of courses in department and books in sections in departments
class department {
public:
	unordered_map<string, course*> courseMap;
	vector<string> courseNumbers;
	vector<string> departmentBooksISBNs;
};
