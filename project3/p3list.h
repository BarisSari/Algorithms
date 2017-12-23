#ifndef UNTITLED_P3LIST_H
#define UNTITLED_P3LIST_H

#include <vector>
#include "p3char.h"

class List{
public:
    std::vector<Book> bookList;
    void insertToList(std::vector<Book> ls, Book *books);
    void lookupList(std::vector<Book> ls, Book *books);
};

#endif //UNTITLED_P3LIST_H
