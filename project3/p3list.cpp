#include "p3list.h"
#include <ctime>
#include <fstream>

void List::insertToList(std::vector<Book> ls, Book *inputBooks) {
    double M = 131071;
    double insertionToList;
    std::cout << "\nLIST" << std::endl;
    clock_t begin = clock();
    for (int i = 0; i < M-1; i++) {
        ls.push_back(inputBooks[i]);
//        std::cout << list.bookList[i].key << std::endl;
    }

    clock_t end = clock();
    insertionToList = double(end - begin) / CLOCKS_PER_SEC; //calculating sorting time
    std::cout << "Insertion finished after " << insertionToList << " seconds." << std::endl;

}

void List::lookupList(std::vector<Book> ls, Book *lookupBooks) {
    std::cout << ls[0].key << std::endl;
    /* std::string outputNameForList = "ds-output-list1.txt";
     double lookupToList;
     std::cout << list.bookList[0].key << std::endl;
     double M = 131071;
     clock_t begin = clock();
     std::cout << list.bookList[1].key << std::endl;
     for (int i = 0; i < M-1; i++) {*/
//        for (int j = 0; j < M-1; j++) {
//            std::cout << list.bookList[i].key << std::endl;
//            if (lookupBooks[i].key == list.bookList[j].key) {
//                std::cout << "eslesti" << std::endl;
//                lookupBooks[i].c[0] = list.bookList[j].c[0];
//                lookupBooks[i].c[1] = list.bookList[j].c[1];
//                break;
//
//            }
//            std::cout << "eslesmedi" << std::endl;
//        }
//    }
//    clock_t end = clock();
//    std::cout << "nerde patliyo3" << std::endl;
//    lookupToList = double(end - begin) / CLOCKS_PER_SEC; //calculating sorting time
//    std::cout << "Lookup finished after " << lookupToList << " seconds." << std::endl;
//    std::ofstream outputFile(outputNameForList);
//    for (int i = 0; i < M; ++i) { //writing output
//        outputFile << lookupBooks[i].pageNo << "\t" << lookupBooks[i].lineNo << "\t"
//                   << lookupBooks[i].index << "\t" << lookupBooks[i].c << std::endl;*/
    //  }
//    outputFile.close();
    std::cout << "olmadi" << std::endl;
}

