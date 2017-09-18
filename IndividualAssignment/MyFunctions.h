#include "MyClasses.h"

using namespace std;

//Used when pulling numbers from input string. Verifies characrer passed is a digit 0-9
bool isInt(char token);

//Pulls a cost out of input string. Pulls chars until decimal, then takes two more after decimal
string getCost(string input, int start);

//Pulls department code out of input string. chars in string must be letters A-Z
string getDepartmentCode(string input, int start);

//Pulls number out of input string of length 'length'
string getNumber(string input, int start, int length);

//Gets rest of string after start. In the case of all commands that use it, names are the end of the string
string getName(string input, int start);

//Pulls date out of string in form MM/YYYY. Also verifies month is valid
string getDate(string input, int start);

//Verifies that any cost has been defined for book
bool costExists(book* currentBook);

//Pulls out min or max cost for book. string compare must either be 'min' or 'max'
double compareCost(book* currentBook, string compare);

//computes arithmetic average
double average(vector<double> vec);

//When items are added to maps, keys are added to vector lists. This checks if a key is in a specific list
bool keyExists(vector<string> list, string key);