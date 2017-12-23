#ifndef UNTITLED_P3CHAR_H
#define UNTITLED_P3CHAR_H

#include <iostream>

class Book{

public:
    int pageNo;
    int lineNo;
    int index;
    char c[2];
    int key;
    std::string generateKey(int a, int b, int c);
    void insertInputFile(Book *books);
    void insertLookupFile(Book *books);
    Book();
//    ~Book();
};

#endif //UNTITLED_P3CHAR_H
