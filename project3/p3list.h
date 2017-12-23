#ifndef P3LIST_H
#define P3LIST_H

#include <vector>
#include "p3char.h"

class List{
public:
    std::vector<Book> bookList;
    std::vector<Book> insertToList(std::vector<Book> ls, Book *books);
    void lookupList(std::vector<Book> ls, Book *books);
};

#endif //P3LIST_H
