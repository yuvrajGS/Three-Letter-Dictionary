#include <fstream>
#include <iostream>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;

void fixInput() {
    /*
    Format the input file so the word is the always the first in the line followed by the description after a space
    */
    string line;

    std::ifstream myReadFile("input.txt");
    std::ofstream myWriteFile("output.txt");
    while (getline(myReadFile, line)) {
        if ((line[0] == '(') || (line[0] == '"') || (islower(line[0])) || (line[3] != ' ')) {
            myWriteFile << " " << line;
        } else if (line.empty() || (line[0] == ' ')) {
            continue;
        } else {
            if (line.substr(0, 3) == "AAH")
                myWriteFile << line; // if first line, don't add \n
            myWriteFile << "\n" << line;
        }
    }
    myReadFile.close();
    myWriteFile.close();
}

void setDictionary(std::unordered_map<char, std::unordered_map<char, std::unordered_map<char, string>>> &dictionary) {
    string line;
    std::ifstream myReadFile("output.txt");

    while (getline(myReadFile, line)) {
        dictionary[line[0]][line[1]][line[2]] = line.substr(4);
    }
    myReadFile.close();
}

int main() {
    std::unordered_map<char, std::unordered_map<char, std::unordered_map<char, string>>> dictionary;
    fixInput();
    // initalize dictionary
    setDictionary(dictionary);
    cout << dictionary['A']['A']['H'] << endl;
    cout << dictionary['Z']['Z']['Z'] << endl;
}