//
// Created by Juan Segura Rico on 7/4/23.
// Partner: Jonathan Curimao
//

#include "dictionary340.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <chrono>
#include <thread>
#include <iomanip>
using namespace std;

const static string file = "Data.CS.SFSU.txt"; // using string to go through the contents of the filoe
const static string null = "pos";
set<string> partsOfSpeech;
multimap<string, vector<string>> dictionary340;
list<string> output;

void toLowercase(string& s) { // converts to lower case
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

vector<string> parseText(const string& s, const string& delim) { // extracts the data from the file
    vector<string> result;
    size_t start = 0;
    size_t end = s.find(delim);
    while (end != string::npos) {
        result.push_back(s.substr(start, end - start));
        start = end + delim.length();
        end = s.find(delim, start);
    }
    result.push_back(s.substr(start, s.length()));
    return result;
}
string getValidFilePath() { // asks user to input the correct file path
    string filePath;
    while (true) {
        cout << "<!>Enter the CORRECT data file path: ";
        getline(cin, filePath);

        // Check if the entered file path matches the required file name
        if (filePath == "./" + file) {
            break;
        }

        cout << "<!>ERROR<!> ===> Provided file path: " << filePath << endl;
        cout << "<!>ERROR<!> ===> File could not be opened." << endl;
    }
    return filePath;
}

void loadDictionary340() {
    string line;
    string filePath = getValidFilePath();
    ifstream ioFile;
    cout << "! Opening data file... " << filePath << endl;
    cout << "! Loading data..." << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    ioFile.open(file, ios::in);
    if (!ioFile) {
        cout << "<!>ERROR<!> ===> File could not be opened." << endl;
        return;
    }
    while (getline(ioFile, line)) {
        vector<string> firstParse = parseText(line, "|");
        for (int i = 1; i < static_cast<int>(firstParse.size()); i++) {
            vector<string> secondParse = parseText(firstParse[i], "-=>>");

            partsOfSpeech.insert(secondParse[0]);
            dictionary340.emplace(firstParse[0], secondParse);
        }
    }
    ioFile.close();
    cout << "! Loading completed..." << endl;
    cout << "! Closing data file...  ./" << file << endl;
    int keywordCount = partsOfSpeech.size();
    int definitionCount = dictionary340.size();
    cout << "\n====== DICTIONARY 340 C++ =====\n" << endl;
    cout << "------ Keywords: " << keywordCount << endl;
    cout << "------ Definitions: " << dictionary340.size() << "\n" << endl;
}

void showDictionary() {
    for (const auto& entry : dictionary340) {
        cout << entry.first << " [" << entry.second[0] << "]: " << entry.second[1] << endl;

    }
}



string outputCapitalization(const string& s) {
    string result = s;
    if (result.find("csc") == 0) {
        transform(result.begin(), result.begin() + 3, result.begin(), ::toupper);
    }
    else {
        result[0] = toupper(result[0]);
    }
    return result;
}

// this function was made, so it can go through the search entries and see if it has a reverse, distinct, or part of speech
void query(const string& keywords, const string& partOfSpeech, const bool& distinct, const bool& reverse) {
    vector<string> keywordWords = parseText(keywords, " ");
    vector<pair<string, string>> matchingEntries;

    vector<pair<string, string>> posMatchingEntries;
    bool matchedpos = false;
    for (int i = 0; i < keywordWords.size(); i++) {

        // Find the range of entries with the target key
        if (i == 0) {
            auto range = dictionary340.equal_range(keywordWords[0]);

            // Print the entries with the target key
            for (auto it = range.first; it != range.second; ++it) {
                matchingEntries.emplace_back(make_pair(it->second[0], it->second[1]));
            }
        }
        // Checks for part of speech
        bool mustmatchpos = false;
        for (const auto& pos : partsOfSpeech) {
            if (keywordWords.size() > 1 && keywordWords[1] + " " == pos) {
                mustmatchpos = true;
            }
        }
        if (i == 1 && mustmatchpos) {
            matchedpos = true;

            for (int j = 0; j < matchingEntries.size(); j++) {
                // added whitespace because part of speech has an extra space at the end
                if (keywordWords[1] + " " == matchingEntries[j].first) {
                    posMatchingEntries.push_back(matchingEntries[j]);
                }
            }
        }
    }

    if (matchingEntries.empty() || (matchedpos && posMatchingEntries.empty())) {
        cout << "      |\n";
        cout << "        <NOT FOUND> To be considered for the next release. Thank you." << endl;
        cout << "      |\n";
        cout << "      |\n";
        cout << "        PARAMETER HOW-TO, please enter: \n";
        cout << "        1. A search key -then 2. An optional part of speech -then\n";
        cout << "        3. An optional 'distinct' -then 4. An optional 'reverse'\n";
        cout << "      |\n";
        cout << "      |\n";
        return;
    }

    cout << "      |\n";
    list<pair<string, string>> listEntries;
    if (matchedpos) {
        for (const auto& pair : posMatchingEntries) {
            string entry = keywordWords[0] + " [" + pair.first + "] :";
            listEntries.push_back(make_pair(entry, pair.second));
        }
    }
    else {
        for (const auto& pair : matchingEntries) {
            listEntries.push_back(make_pair(keywordWords[0], "[" + pair.first + "] : " + pair.second));
        }
    }

    if (distinct) {
        listEntries.sort();
        listEntries.unique();
    }
    if (reverse) {
        listEntries.reverse();
    }

    for (const auto& pair : listEntries) {
        cout << setw(11) << pair.first << " " << pair.second << endl;
    }
    cout << "      |\n";
}

void runSearch() {
    int searchCount = 0;
    while (true) {
        string input;
        cout << "Search [" << searchCount + 1 << "]: ";
        getline(cin, input);
        toLowercase(input);
        vector<string> searchParams = parseText(input, " ");
        if (input == "!q") {
            break; // Exit the loop and end the program
        }
        else if (searchParams[0].compare("!help") == 0 || input.empty()) {
            cout << "      |\n";
            cout << "        PARAMETER HOW-TO, please enter: \n";
            cout << "        1. A search key -then 2. An optional part of speech -then\n";
            cout << "        3. An optional 'distinct' -then 4. An optional 'reverse'\n";
            cout << "      |\n";
            searchCount++;
            continue;
        }

        searchCount++;  // Increment search count after each search

        string keywords;
        bool distinct = false;
        bool reverse = false;
        bool partOfSpeech = false;

        if (searchParams.size() > 4) {
            cout << "      |\n";
            cout << "        PARAMETER HOW-TO, please enter: \n";
            cout << "        1. A search key -then 2. An optional part of speech -then\n";
            cout << "        3. An optional 'distinct' -then 4. An optional 'reverse'\n";
            cout << "      |\n";
            continue;
        }
        // Extract keywords, distinct option, and reverse
        if (searchParams.size() > 1) {
            keywords = searchParams[0];
            if (searchParams[1] == "distinct") {
                distinct = true;
            }
            else if (searchParams[1] == "reverse") {
                reverse = true;
            }
            else if (searchParams[1] == "adjective") {
                reverse = true;
            }
            else if (searchParams[1] == "noun") {
                partOfSpeech = true;
            }
            else if (searchParams[1] == "verb") {
                partOfSpeech = true;
            }
            else if (searchParams[1] == "interjection") {
                partOfSpeech = true;
            }
            else if (searchParams[1] == "conjunction") {
                partOfSpeech = true;
            }
            else if (searchParams[1] == "pronoun") {
                partOfSpeech = true;
            }
            else if (searchParams[1] == "adverb") {
                partOfSpeech = true;
            }
            else if (searchParams[1] == "preposition") {
                partOfSpeech = true;
            }
            else {
                cout << "      |\n";
                cout << "        <The entered 2nd parameter " << searchParams[1] << " is NOT a part of speech.>" << endl;
                cout << "        <The entered 2nd parameter " << searchParams[1] << " is NOT 'distinct'.>" << endl;
                cout << "        <The entered 2nd parameter " << searchParams[1] << " is NOT 'reverse'.>" << endl;
                cout << "        <The entered 2nd parameter " << searchParams[1] << " was disregarded.>" << endl;
                cout << "        <The 2nd parameter " << searchParams[1] << " should be a part of speech or 'distinct' or 'reverse'.>" << endl;
                cout << "      |\n";

            }
        }

        if (searchParams.size() > 2) {
            if (searchParams[2] == "distinct") {
                distinct = true;
            }
            else if (searchParams[2] == "reverse") {
                reverse = true;
            }
            else {
                cout << "      |\n";
                cout << "        <The entered 3rd parameter " << searchParams[2] << " is NOT 'distinct'.>" << endl;
                cout << "        <The entered 3rd parameter " << searchParams[2] << " is NOT 'reverse'.>" << endl;
                cout << "        <The entered 3rd parameter " << searchParams[2] << " was disregarded.>" << endl;
                cout << "        <The 3rd parameter " << searchParams[2] << " should be 'distinct' or 'reverse'.>" << endl;
                cout << "      |\n";
            }
        }

        if (searchParams.size() > 3) {
            if (searchParams[3] == "reverse") {
                reverse = true;
            }
            else {
                cout << "      |\n";
                cout << "        <The entered 4th parameter " << searchParams[3] << " is NOT 'reverse'.>" << endl;
                cout << "        <The entered 4th parameter " << searchParams[3] << " was disregarded>" << endl;
                cout << "        <The 4th parameter " << searchParams[3] << " should be 'reverse'.>" << endl;
                cout << "      |\n";

            }
        }
        query(input, null, distinct, reverse);


        output.clear();
    }
    cout << "" << endl;
    cout << "-----THANK YOU-----" << endl;
}

int main() {
    loadDictionary340();
    runSearch();
    return 0;
}
