#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <random>

#include "Base64.h"
#include "Helpers.h"
#include "pugixml.hpp"

using namespace std;
using namespace pugi;

const char* keyFile = "keys.xml";

int ExitWithError(int code);
void WaitForKeypress();
//string GenerateRandomString(int length);

int main(int argc, char* argv[]) {
	// Check for argument count
	if(argc == 1)
		return ExitWithError(1);

	// Check that file exists
	ifstream ifile(argv[1]);
	if(!ifile)
		return ExitWithError(2);
	ifile.close();

	string file = argv[1];

	// Load local key library
	xml_document keys;
	xml_parse_result keysResult = keys.load_file(keyFile);

	// If it's XML, we use that and attempt
	if(std::string::npos != file.find(".xml"))
	{
		// Load the passed file
		xml_document doc;
		xml_parse_result result = doc.load_file(argv[1]);
		string Guid = doc.child("Data").child("GUID").text().as_string();
		cout << Guid << endl;
	}
	else 
	{
		// Otherwise we'll let users choose
	}

	cout << endl << Helpers::GenerateRandomString(128);

	WaitForKeypress();
	return 0;
}

int ExitWithError(int code)
{
	cout << endl << "Error code: " << code;
	WaitForKeypress();
	return code;
}

void WaitForKeypress()
{
	cout << endl << "Press any key to exit..." << endl;
	getch();
}
