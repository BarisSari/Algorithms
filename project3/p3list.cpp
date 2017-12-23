#include "p3list.h"
#include <ctime>
#include <fstream>

std::vector<Book> List::insertToList(std::vector<Book> ls, Book *inputBooks) {
    double M = 131071;
    double insertionToList;
    std::cout << "\nLIST" << std::endl;
    clock_t begin = clock();
    for (int i = 0; i < M-1; i++) {
        ls.push_back(inputBooks[i]);    //appends data
    }
    clock_t end = clock();
    insertionToList = double(end - begin) / CLOCKS_PER_SEC; //calculating time
    std::cout << "Insertion finished after " << insertionToList << " seconds." << std::endl;
    return ls;  //returns vector that all input elements are inserted
}

void List::lookupList(std::vector<Book> ls, Book *lookupBooks) {
    std::string outputNameForList = "ds-output-list.txt";
    double lookupToList;
    double M = 131071;
    clock_t begin = clock();
    for (int i = 0; i < M-1; i++) { //for all elements of the lookup file
        for (int j = 0; j < M-1; j++) { //parse the vector until keys are matched
            if (lookupBooks[i].key == ls[j].key) {  //if key is found, update the lookup character
                lookupBooks[i].c[0] = ls[j].c[0];
                lookupBooks[i].c[1] = ls[j].c[1];
                break;
            }
        }
    }
    clock_t end = clock();
    lookupToList = double(end - begin) / CLOCKS_PER_SEC; //calculating time
    std::cout << "Lookup finished after " << lookupToList << " seconds." << std::endl;
    std::ofstream outputFile(outputNameForList);
    for (int i = 0; i < M; ++i) { //writing output
        outputFile << lookupBooks[i].pageNo << "\t" << lookupBooks[i].lineNo << "\t"
                   << lookupBooks[i].index << "\t" << lookupBooks[i].c << std::endl;
    }
    outputFile.close();
}

