/*  Developed by Bayram Baris Sari
*   E-mail: bayrambariss@gmail.com
*   Tel No: +90 539 593 7501    
*
*	This is the implementation of merge sort and
*	insertion sort for a deck of Hearthstone.
*	There are two types of filtering full and
*	normal: 
*	Full sort classifies according to "Class",
* 	if they are the same, according to "Cost", and if
*	they are both same, by "Name".
*	Normal sort classifies according to "Class"
*	Example input has this format:
*	Name+"\t"+Class+"\t"+Rarity+"\t"+Set+"\t"+Type+"\t"+Cost\n
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

class Card {
public:
    Card();
    std::string Name;
    std::string Class ;
    std::string Rarity;
    std::string Set;
    std::string Type;
    int Cost;
};
Card::Card() {
    Name = "";
    Class = "";
    Rarity = "";
    Set = "";
    Type = "";
    Cost = 0;
}

class CardManager {
public:
    Card *myCards;
    CardManager(); //default constructor
    void set_strings(std::string,std::string,int);
    void FullSort();
    void FilterSort();

    std::string sortingProcedure;
private:
    std::string sortingType;
    int CardsSize;
};

CardManager::CardManager() {
    myCards = NULL;
}

void CardManager::set_strings(std::string FullorFilter,std::string InsertOrMerge,int size) {
    sortingProcedure = FullorFilter;
    sortingType = InsertOrMerge;
    CardsSize = size;
}

//Merge Sort
void mergeFilter(Card *Cards, int left, int medium, int right) {
    int leftSize = medium - left + 1;
    int rightSize = right - medium; //calculating size of cards
    int i, j; //iteration variables
    Card *leftCards= new Card[leftSize];
    Card *rightCards = new Card[rightSize];  //allocating memory with the size calculated above
    for (i = 0; i < leftSize; ++i)
        leftCards[i] = Cards[left + i];
    for (j = 0; j < rightSize; ++j)
        rightCards[j] = Cards[medium + j + 1];  //assigning "leftCards" and "rightCards" temporary structures
    j = 0;
    i = 0;
    int k = left;
    while (i < leftSize && j < rightSize) { //merge back to the original structure "Cards"
        if (leftCards[i].Type <= rightCards[j].Type)
            Cards[k++] = leftCards[i++];
        else
            Cards[k++] = rightCards[j++];
    }
    //copying the rest to the original structure
    while (i < leftSize)
        Cards[k++] = leftCards[i++];
    while (j < rightSize)
        Cards[k++] = rightCards[j++];
    //cleaning memory
    delete[] leftCards;
    delete[] rightCards;
}
void mergeFilterSort(Card *Cards, int lowLimit, int upLimit) {
    int middle;
    if (lowLimit < upLimit) { //splitting structures to two parts from the middle
        middle = (lowLimit + upLimit) / 2;
        mergeFilterSort(Cards, lowLimit, middle);
        mergeFilterSort(Cards, middle + 1, upLimit);
        mergeFilter(Cards, lowLimit, middle, upLimit); //merging to original structure with applying sorting rules
    }
}

void mergeFull(Card *Cards, int left, int medium, int right) {
    int leftSize = medium - left + 1;
    int rightSize = right - medium; //calculating size of cards
    int i, j; //iteration variables
    Card *leftCards= new Card[leftSize];
    Card *rightCards = new Card[rightSize];  //allocating memory with the size calculated above
    for (i = 0; i < leftSize; ++i)
        leftCards[i] = Cards[left + i];
    for (j = 0; j < rightSize; ++j)
        rightCards[j] = Cards[medium + j + 1];  //assigning "leftCards" and "rightCards" temporary structures
    j = 0;
    i = 0;
    int k = left;
    while (i < leftSize && j < rightSize) { //merge back to the original structure "Cards"
        if (leftCards[i].Class < rightCards[j].Class)
            Cards[k++] = leftCards[i++];
        else if (leftCards[i].Class ==
                 rightCards[j].Class) { //this is a special situation,when "Classes" are the same,program first checks "Costs"
            if (leftCards[i].Cost < rightCards[j].Cost)
                Cards[k++] = leftCards[i++];
            else if (leftCards[i].Cost == rightCards[j].Cost) { //if "Costs" are also the same, program checks Names
                if (leftCards[i].Name <= rightCards[j].Name)
                    Cards[k++] = leftCards[i++];
                else
                    Cards[k++] = rightCards[j++];
            } else
                Cards[k++] = rightCards[j++];
        } else
            Cards[k++] = rightCards[j++];
    }

    //Copying the rest to the original structure
    while (i < leftSize)
        Cards[k++] = leftCards[i++];
    while (j < rightSize)
        Cards[k++] = rightCards[j++];
    //cleaning memory
    delete[] leftCards;
    delete[] rightCards;
}
void mergeFullSort(Card *Cards, int lowLimit, int upLimit) {
    int middle;
    if (lowLimit < upLimit) { //splitting structures to two parts from the middle
        middle = (lowLimit + upLimit) / 2;
        mergeFullSort(Cards, lowLimit, middle);
        mergeFullSort(Cards, middle + 1, upLimit);
        mergeFull(Cards, lowLimit, middle, upLimit); //merging to original structure with applying sorting rules
    }
}

//Insertion Sort
void insertionFilterSort(Card *Cards,int size){
    int i;
    Card key;
    for (int j = 1; j < size; j++) { //it starts from the 1st indice of Cards
        key = Cards[j];
        i = j - 1;
        while (i >= 0 && key.Type < Cards[i].Type) { //it checks and swaps until key's type is greater or equal to Cards[i]'s type
            Cards[i + 1] = Cards[i]; //swap process
            i = i - 1;
            Cards[i + 1] = key;      //swap process
        }
    }
}
void insertionFullSort(Card *Cards,int size){
    int i;
    Card key;
    for (int k = 1; k < size; k++) {
        key = Cards[k];
        i = k - 1;
        while (i >= 0 && (key.Class < Cards[i].Class || (key.Class == Cards[i].Class && key.Cost < Cards[i].Cost) ||
                          (key.Cost == Cards[i].Cost && key.Name < Cards[i].Name))) {   //it checks and swaps if one of the conditions for full sort is true
            Cards[i + 1] = Cards[i];    //swap process
            i = i - 1;
            Cards[i + 1] = key;         //swap process
        }
    }
}

void CardManager::FullSort() {
    if (sortingType == "-i")
        insertionFullSort(myCards,CardsSize);
    else if (sortingType == "-m")
        mergeFullSort(myCards,0,CardsSize);
    else
    	std::cout << "Invalid sorting algorithm!" << std::endl;
}
void CardManager::FilterSort() {
    if (sortingType == "-i")
        insertionFilterSort(myCards,CardsSize);
    else if (sortingType == "-m")
        mergeFilterSort(myCards, 0, CardsSize);
    else
    	std::cout << "Invalid sorting algorithm!" << std::endl;
}

int main(int argc, char* argv[]) {
    CardManager Manager;
    Card *myList;
    std::string inputName = argv[3]; //input file name
    std::string outputName = argv[4]; //output file name
    std::ifstream infile(inputName);
    std::string line,line2;
    int size=0,i=0; //counters
    while(getline(infile,line))   //calculating number of lines in the text infile
        size++;
    myList = new Card[size]; //allocating memory for the structure
    Manager.set_strings(argv[1],argv[2],size); //full or filter sort
    infile.clear();
    infile.seekg(0,infile.beg); //returning to the beginning of infile
    while(getline(infile,line)){ //reading lines with changed istream function
        std::stringstream iss(line);
        while(std::getline(iss,line2,'\t'))
            iss >> myList[i].Name >> myList[i].Class >> myList[i].Rarity >> myList[i].Set >> myList[i].Type >> myList[i].Cost;
        i++;
    }
    infile.close();
    Manager.myCards = myList;
    clock_t begin = clock();
    if(Manager.sortingProcedure == "-f")
        Manager.FullSort();
    else if(Manager.sortingProcedure == "-n")
        Manager.FilterSort();
    else
    	std::cout << "Invalid sorting procedure!" << std::endl;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    std::ofstream outputFile(outputName);
    for (int j = 0; j < size; ++j) { //writing output
        outputFile << Manager.myCards[j].Name<<"\t"<< Manager.myCards[j].Class<<"\t"<<Manager.myCards[j].Rarity<<"\t"<<Manager.myCards[j].Set<<"\t"<<Manager.myCards[j].Type<<"\t"<<Manager.myCards[j].Cost<<std::endl;
    }
    outputFile << "Execution time: " << elapsed_secs << " s";
    outputFile.close();
    std::cout << "Execution time: " << elapsed_secs << " s";
    delete[] myList;

    return 0;
}
