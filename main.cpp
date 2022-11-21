#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class dictionary {

private:
    std::string ***dict = new std::string **[26]; // initalize nested hashtable
    void createDict() { //create nested dictionary
        for (int i = 0; i < 26; ++i) {
            dict[i] = new std::string *[26];
            for (int j = 0; j < 26; ++j) {
                dict[i][j] = new std::string[26];
            }
        }
    }

    int hashFunc(char key) {    //Since all keys are letters A-Z, subtracting by 65 ('A') will get indices from 0 to 25
        return (toupper(key) - 65);
    }

public:
    dictionary() {
        createDict();
        string line;
        std::ifstream myReadFile("output.txt"); // open file

        while (getline(myReadFile, line)) {
            dict[hashFunc(line[0])][hashFunc(line[1])][hashFunc(line[2])] = line.substr(4); // add word to dictionary
        }
        myReadFile.close(); // close file
    }

    bool insert(string &word, string &desc) {
        if (word.length() != 3 || !isalpha(word[0]) || !isalpha(word[1]) || !isalpha(word[2]))
            return false; // not a valid 3-letter word
        if (dict[hashFunc(word[0])][hashFunc(word[1])][hashFunc(word[2])] != "")
            return false; // word already in dictionary
        dict[hashFunc(word[0])][hashFunc(word[1])][hashFunc(word[2])] = desc;
        return true;
    }
    string lookUp(string &word) {
        if (word.length() != 3 || !isalpha(word[0]) || !isalpha(word[1]) || !isalpha(word[2]))
            return NULL; // not a valid 3-letter word
        return dict[hashFunc(word[0])][hashFunc(word[1])][hashFunc(word[2])]; // returns the word's description
    }
    bool deleteWord(string &word) {
        if (word.length() != 3 || !isalpha(word[0]) || !isalpha(word[1]) || !isalpha(word[2]))
            return false; // not a valid 3-letter word
        dict[hashFunc(word[0])][hashFunc(word[1])][hashFunc(word[2])] = ""; //erase element in hashtable
        return true;
    }
};

void fixInput() {
    /*
    Format the input file so the word is the always the first in the line followed by the description after a space
    */
    string line;

    std::ifstream myReadFile("input.txt");
    std::ofstream myWriteFile("output.txt");
    while (getline(myReadFile, line)) {
        if ((line[0] == '(') || (line[0] == '"') || (islower(line[0])) || (line[3] != ' ')) {
            myWriteFile << " " << line; // add the definitions to the same line the word is on
        } else if (line.empty() || (line[0] == ' ')) {
            continue;   //skip blank lines
        } else {
            if (line.substr(0, 3) == "AAH")
                myWriteFile << line; // if first line, don't add \n
            myWriteFile << "\n"
                        << line;
        }
    }
    myReadFile.close();
    myWriteFile.close();
}

int main() {
    fixInput();
    // create dictionary
    dictionary myDictionary;
    //TESTING
    string word = "AAH", desc = "v. to have fun", word2 = "(LL";
    cout << "Try to insert a word that already exists (returns false): " << myDictionary.insert(word, desc) << endl;
    cout << "Look up the description of a word: " << word << " " << myDictionary.lookUp(word) << endl;
    cout << "Delete a word that exists in the dictionary (returns true): " << myDictionary.deleteWord(word) << endl;
    cout << "Look up the description of a deleted word: " << word << " " << myDictionary.lookUp(word) << endl;
    cout << "Insert a valid word (returns true): " << myDictionary.insert(word, desc) << endl;
    cout << "Look up the description of the newly added word: " << word << " " << myDictionary.lookUp(word) << endl;
    cout << "Try to add an invalid 3-letter word (returns false): " << myDictionary.insert(word2, desc) << endl;
}