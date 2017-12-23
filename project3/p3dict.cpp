#include "p3dict.h"
#include <cmath>
#include <ctime>
#include <fstream>

bool Dictionary::insert(unsigned long k, Book structBook, struct Dictionary *dict) {
    if(dict[k].isEmpty) { //if index k of the dictionary is empty, structBook is inserted
        dict[k].value = structBook;
        dict[k].key = k;    //k is hash key
        dict[k].isEmpty = false;    //now, index k of the dictionary is occupied
        return true;
    } else{
        return false;
    }
}

/*bool Dictionary::lookup(Book structBook, struct Dictionary dict) {
    return dict.value.key == structBook.key;
}*/

void Dictionary::insertionProcess(Dictionary *dict, Book *inputBooks) {
    int M = 131071;
    double A = (std::sqrt(5)-1)/2;
    double modulo = 0;
    double insertionForDict = 0;
    unsigned long tempHashKey;
    double numberOfCollision = 0;
    double averageCacheCollision = 0;
    double totalCacheCollision = 0;
    double thousandItems = 0;
    double tenThousandItems = 0;
    double hundredThousandItems = 0;

    std::cout << "\nDICTIONARY" << std::endl;
    clock_t begin = clock();

    for(int i=0; i<M-1; i++) {  //For all elements of input file
        modulo = std::fmod((A * inputBooks[i].key), 1);     //modulo part of the hash function( k*A(mod 1) ).
        for(int j=0; j<M-1; j++) {  //quadratic probing function
            tempHashKey = ((std::ceil(modulo * M)) + 7 * j + 3 * j * j);
            if (dict->insert(tempHashKey, inputBooks[i], dict)) {  //if it's inserted, breaks the inner for loop
                numberOfCollision = numberOfCollision + j;
                break;
            }
        }
        totalCacheCollision = totalCacheCollision + numberOfCollision;
        switch(i){      //values which are used for showing number of collisions
            case 1000:
                thousandItems = totalCacheCollision/i;
            case 10000:
                tenThousandItems = totalCacheCollision/i;
            case 100000:
                hundredThousandItems = totalCacheCollision/i;
            default:
                break;
        }
    }
    clock_t end = clock();
    insertionForDict = double(end - begin) / CLOCKS_PER_SEC; //calculating time
    std::cout << "Insertion finished after " << insertionForDict << " seconds." << std::endl;

    averageCacheCollision = totalCacheCollision / M;
    std::cout << "\nAverage number of collisions first (1000)   \t| " << thousandItems << std::endl;
    std::cout << "Average number of collisions first (10,000) \t| " << tenThousandItems << std::endl;
    std::cout << "Average number of collisions first (100,000)\t| " << hundredThousandItems << std::endl;
    std::cout << "Average number of collisions overall        \t| " << averageCacheCollision << std::endl;

}

void Dictionary::lookupProcess(Dictionary *dict, Book *lookupBooks) {
    unsigned long tempHashKey = 0;
    double lookupForDict = 0;
    std::string outputNameForDictionary = "ds-output-dictionary.txt";
    int M = 131071;
    double A = (std::sqrt(5)-1)/2;
    double modulo = 0;

    clock_t begin = clock();
    for(int i=0; i<M-1; i++) {   //For all elements of the lookup file
        modulo = std::fmod((A * lookupBooks[i].key), 1);    //modulo part of the hash function( k*A(mod 1) ).
        for (int j = 0; j < M - 1; j++) {   //quadratic probing function
            tempHashKey = ((std::ceil(modulo * M)) + 7 * j + 3 * j * j);
            if (lookupBooks[i].key == dict[tempHashKey].value.key) {    //if it's found, updates the character and breaks the inner for loop
                lookupBooks[i].c[1] = dict[(int) tempHashKey].value.c[1];
                lookupBooks[i].c[0] = dict[(int) tempHashKey].value.c[0];
                break;
            }
        }
    }
    clock_t end = clock();
    lookupForDict = double(end - begin) / CLOCKS_PER_SEC; //calculating time
    std::cout << "Lookup finished after " << lookupForDict << " seconds." << std::endl;
    std::ofstream outputFile(outputNameForDictionary);
    for (int i = 0; i < M-1; i++) { //writing output
        outputFile << lookupBooks[i].pageNo<<"\t"<< lookupBooks[i].lineNo<<"\t"
                   <<lookupBooks[i].index<<"\t" <<lookupBooks[i].c <<std::endl;
    }
    outputFile.close();
}
