#include "p3char.h"
#include <sstream>
#include <iomanip>
#include <fstream>

Book::Book() { //default constructor for Book character class
    pageNo = 0;
    lineNo = 0;
    index = 0;
    c[0] = ' ';
    c[1] = ' ';
    key = 0;
}


std::string Book::generateKey(int a, int b, int c) {
    std::ostringstream ss;
    //setw and setfill are used to not generate duplicate keys when lineNo or index is lower than 10.
    ss << a << std::setw(2) << std::setfill('0') << b << std::setw(2) << std::setfill('0') << c;
    return ss.str();
}

void Book::insertInputFile(Book *inputBooks) {
    std::string inputFileName = "/home/baris/CLionProjects/proje3/ds-set-input.txt";
    std::string line, tempKey;
    int i=0;

    std::ifstream infile(inputFileName);
    while (std::getline(infile, line)) { //reading the file line-by-line with istream function
        std::stringstream iss(line);
        iss >> inputBooks[i].pageNo >> inputBooks[i].lineNo >> inputBooks[i].index >> inputBooks[i].c;
        tempKey = inputBooks[i].generateKey(inputBooks[i].pageNo, inputBooks[i].lineNo, inputBooks[i].index);
        inputBooks[i].key = atoi(tempKey.c_str());
        i++;
    }
    infile.close();
}

void Book::insertLookupFile(Book *lookupBooks) {
    std::string lookupFileName = "/home/baris/CLionProjects/proje3/ds-set-lookup.txt";
    std::string line, tempKey;
    int i = 0;

    std::ifstream lookupFile(lookupFileName);
    while (getline(lookupFile, line)) { //reading line-by-line
        std::stringstream iss(line);
        iss >> lookupBooks[i].pageNo >> lookupBooks[i].lineNo >> lookupBooks[i].index;
        tempKey = lookupBooks[i].generateKey(lookupBooks[i].pageNo, lookupBooks[i].lineNo, lookupBooks[i].index);
        lookupBooks[i].key = (atoi(tempKey.c_str()));
        i++;
    }
    lookupFile.close();
}

