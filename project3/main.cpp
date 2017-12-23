#include "p3dict.h"
#include "p3list.h"

int main() {
    int M = 131071;
    Book inputBooksforDictionary[M];
    Dictionary dict[M];
    List list;
    /*Insertion for Dictionary*/
    inputBooksforDictionary->insertInputFile(inputBooksforDictionary);
    dict->insertionProcess(dict, inputBooksforDictionary);
    /*Lookup for Dictionary*/
    Book *lookupBooksforDictionary = new Book[M];
    lookupBooksforDictionary->insertLookupFile(lookupBooksforDictionary);
    dict->lookupProcess(dict, lookupBooksforDictionary);
    /*Insertion for List*/
    Book *inputBooksforList = new Book[M];
    inputBooksforList->insertInputFile(inputBooksforList);
    list.bookList = list.insertToList(list.bookList, inputBooksforList);
    /*Lookup for List*/
    Book *lookupBooksforList = new Book[M];
    lookupBooksforList->insertLookupFile(lookupBooksforList);
    list.lookupList(list.bookList, lookupBooksforList);

    return 0;
}