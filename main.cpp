//Arttu Pietarinen
// Mygrep project
// This program implements a simple version of the grep command

// Including neccesary libraries
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <stdexcept>

using namespace std;

// Struct to hold the options for the search
struct searchoptions {
    bool showlinenumbers;
    bool showcount;
    bool caseinsensitive;
    bool reversesearch;
};

// Prototypes
int interactive();
int filesearch(const string &search, const string &filename, searchoptions options);
searchoptions parseoptions(const string &options);
string tolowerstr(const string &s);
void printusage();

// Main function to handle command line arguments and redirect to the appropriate function
// It checks the amount of arguments and their format
int main(int argc, char **argv) {
    try {
        if (argc == 1) {
            return interactive();
        } else if (argc == 3) {
            string search = argv[1];
            string filename = argv[2];
            searchoptions opts = {false, false, false, false}; // Default options
            return filesearch(search, filename, opts);
        } else if (argc == 4) {
            string optstr = argv[1];
            string search = argv[2];
            string filename = argv[3];

            if (optstr.size() < 2 || optstr[0] != '-' || optstr[1] != 'o') { // Check if options string is valid
                printusage();
                return 1;
            }

            searchoptions opts = parseoptions(optstr); // Parse the options from the command line
            return filesearch(search, filename, opts);
        } else {
            printusage(); // If the number of arguments is not valid, print usage instructions
            return 1;
        }
    } catch (const exception &e) {
        cout << "An exception occurred. Exception Nr. -1" << endl; // Catch any exceptions and print the error message
        cout << e.what() << endl;
        return -1;
    }
}

// Function for interactive mode, it prompts the user for a source string and a search string, then performs the search and prints the results
int interactive() {
    string source, search;

    cout << "Give a string from which to search for: ";
    getline(cin, source);

    cout << "Give search string: ";
    getline(cin, search);

    size_t pos = source.find(search);

    if (pos != string::npos) {
        cout << "\"" << search << "\" found in \"" << source << "\" in position " << pos << endl;
    } else {
        cout << "\"" << search << "\" NOT found in \"" << source << "\"" << endl;
    }

    return 0;
}

// Function to convert a string to lowercase, used for case insensitive searching
string tolowerstr(const string &s) {
    string result = s;
    for (size_t i = 0; i < result.length(); i++) {
        result[i] = static_cast<char>(tolower((unsigned char)result[i]));
    }
    return result;
}

// Function to perform the file search, it reads the file line by line and checks if the search string is present, then prints the results according to the options provided
int filesearch(const string &search, const string &filename, searchoptions options) {
    ifstream file(filename);

    if (!file) {
        throw runtime_error("Could not find out the size of file \"" + filename + "\"");
    }

    string searchtolower = search;
    if (options.caseinsensitive) {
        searchtolower = tolowerstr(search);
    }

    string line;
    int linenumber = 0;
    int count = 0;

    while (getline(file, line)) {
        linenumber++;

        string linetolower = line;
        if (options.caseinsensitive) {
            linetolower = tolowerstr(line);
        }

        bool match = (linetolower.find(searchtolower) != string::npos);

        if (options.reversesearch) {
            match = !match;
        }

        if (match) {
            count++;

            if (options.showlinenumbers || !options.showcount) {
                if (options.showlinenumbers) {
                    cout << linenumber << ": ";
                }
                cout << line << endl;
            }
        }
    }

    if (count == 0 && !options.showcount) {
        cout << "No matches found for \"" << search << "\"" << endl;
    }

    if (options.showcount) {
        if (options.reversesearch) {
            cout << "Occurrences of lines NOT containing \"" << search << "\": " << count << endl;
        } else {
            cout << "Occurrences of lines containing \"" << search << "\": " << count << endl;
        }
    }

    return 0;
}

// Function to parse the options from the command line, it checks for the presence of each option and sets the corresponding fields in the searchoptions struct
searchoptions parseoptions(const string &options) {
    searchoptions opts = {false, false, false, false};

    for (size_t i = 2; i < options.length(); i++) {
        if (options[i] == 'l') {
            opts.showlinenumbers = true;
        } else if (options[i] == 'o') {
            opts.showcount = true;
        } else if (options[i] == 'i') {
            opts.caseinsensitive = true;
        } else if (options[i] == 'r') {
            opts.reversesearch = true;
        } else {
            throw runtime_error(string("Option not recognized: '") + options[i] + "'");
        }
    }

    return opts;
}

// Function to print usage instructions
void printusage() {
    cout << "Wrong usage, try:" << endl;
    cout << "mygrep" << endl;
    cout << "mygrep <search> <filename>" << endl;
    cout << "mygrep -o<flags> <search> <filename>" << endl;
    cout << "flags: l (line numbers), o (count), i (ignore case), r (reverse)" << endl;
}
