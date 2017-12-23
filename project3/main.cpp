#include "p3list.h"

int main() {
    int M = 131071;

    List list;

    Book *inputBooksforList = new Book[M];
    inputBooksforList->insertInputFile(inputBooksforList);
    list.insertToList(list.bookList, inputBooksforList);
    for(int j=0; j < M-1; j++)
        std::cout << list.bookList[j].key << "\t" << list.bookList[j].c << std::endl;

    return 0;
}