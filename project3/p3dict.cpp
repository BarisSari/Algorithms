#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include "p3char.cpp"


class Dictionary{
public:
    unsigned long key;
    struct Book value;
    bool isEmpty = true;
    bool insert(unsigned long k, struct Book structBook, struct Dictionary *dict);
    bool lookup(struct Book structBook, struct Dictionary dict);
};

bool Dictionary::insert(unsigned long k, struct Book structBook, struct Dictionary *dict) {
    if(dict[k].isEmpty) {
        dict[k].value = structBook;
        dict[k].key = k;
//      std::cout << dict.value.pageNo << " " << dict.value.lineNo << " " << dict.value.index << " " << dict.value.c << std::endl;
        dict[k].isEmpty = false;
        return true;
    } else{
        return false;
    }
}

bool Dictionary::lookup(struct Book structBook, struct Dictionary dict) {
    return dict.value.key == structBook.key;
}


int main() {
    int M = 131071;
    double A = (std::sqrt(5)-1)/2;
    double modulo = 0;

    Book *inputBooks = new Book[M];
    Book *lookupBooks = new Book[M];
    Dictionary *dict = new Dictionary[M];
    List list;
    std::string line, line2, tempKey;
    std::string outputNameForList = "ds-output-list1.txt";
    std::string outputNameForDictionary = "ds-output-dictionary.txt";
    int i=0, j=0; //counters
    double insertionForDict = 0;
    double insertionForList = 0;
    double lookupForDict = 0;
    double lookupForList = 0;
    unsigned long tempHashKey = 0;
    double averageCacheCollision = 0;
    double numberOfCollision = 0;
    double thousandItems = 0;
    double tenThousandItems = 0;
    double hundredThousandItems = 0;

    std::string inputFileName = "/home/baris/CLionProjects/proje3/ds-set-input.txt";
    std::string lookupFileName = "/home/baris/CLionProjects/proje3/ds-set-lookup.txt";




    /**Insert to Dictionary**/
    std::cout << "\nDICTIONARY" << std::endl;
    begin = clock();

    for(i=0; i<M-1; i++) {
        modulo = std::fmod((A * inputBooks[i].key), 1);
        for(j=0; j<M-1; j++) {
            tempHashKey = ((std::ceil(modulo * M)) + 7 * j + 3 * j * j);
            if (dict->insert(tempHashKey, inputBooks[i], dict)) {
                numberOfCollision = numberOfCollision + j;
                break;
            }
        }
//        std::cout << dict[(int)tempHashKey].key << "\t" <<dict[(int)tempHashKey].value.key << "\t" << dict[(int)tempHashKey].value.c << std::endl;
        averageCacheCollision = averageCacheCollision + numberOfCollision;
        switch(i){
            case 1000:
                thousandItems = averageCacheCollision/i;
            case 10000:
                tenThousandItems = averageCacheCollision/i;
            case 100000:
                hundredThousandItems = averageCacheCollision/i;
            default:
                break;
        }
    }
    end = clock();
    insertionForDict = double(end - begin) / CLOCKS_PER_SEC; //calculating sorting time
    std::cout << "Insertion finished after " << insertionForDict << " seconds." << std::endl;

    averageCacheCollision = averageCacheCollision / M;
    std::cout << "\nAverage number of collisions first (1000)   \t| " << thousandItems << std::endl;
    std::cout << "Average number of collisions first (10,000) \t| " << tenThousandItems << std::endl;
    std::cout << "Average number of collisions first (100,000)\t| " << hundredThousandItems << std::endl;
    std::cout << "Average number of collisions overall        \t| " << averageCacheCollision << std::endl;



    /**Lookup for Dictionary**/
    begin = clock();
    for(i=0; i<M-1; i++) {
        modulo = std::fmod((A * lookupBooks[i].key), 1);
        for (j = 0; j < M - 1; j++) {
            tempHashKey = ((std::ceil(modulo * M)) + 7 * j + 3 * j * j);
//            std::cout << i << "\t" << lookupBooks[i].key << "\t" << dict[(int)tempHashKey].value.key << std::endl;
            if (lookupBooks[i].key == dict[tempHashKey].value.key) {
                lookupBooks[i].c[1] = dict[(int) tempHashKey].value.c[1];
                lookupBooks[i].c[0] = dict[(int) tempHashKey].value.c[0];
                break;
            }
        }
    }
    end = clock();
    lookupForDict = double(end - begin) / CLOCKS_PER_SEC; //calculating sorting time
    std::cout << "Lookup finished after " << lookupForDict << " seconds." << std::endl;
    std::ofstream outputFile(outputNameForDictionary);
    for (i = 0; i < M-1; i++) { //writing output
        outputFile << lookupBooks[i].pageNo<<"\t"<< lookupBooks[i].lineNo<<"\t"
                   <<lookupBooks[i].index<<"\t" <<lookupBooks[i].c <<std::endl;
    }
    outputFile.close();


    return 0;
}