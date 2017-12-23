#ifndef P3DICT_H
#define P3DICT_H

#include "p3char.h"

class Dictionary{
public:
    unsigned long key;
    Book value;
    bool isEmpty = true;
    bool insert(unsigned long k, struct Book structBook, struct Dictionary *dict);
    void insertionProcess(Dictionary *dict, Book *inputBooks);
    void lookupProcess(Dictionary *dict, Book *inputBooks);
    //    bool lookup(struct Book structBook, struct Dictionary dict);

};

#endif //P3DICT_H
