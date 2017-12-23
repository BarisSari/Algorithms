/*  Bayram Baris Sari
*   150130123
*   Project II    */

#include <iostream>
#include <fstream>
#include <ctime>

class Residence{
public:
    Residence();
    int population;
    int minimum_age;
    int maximum_age;
    std::string gender;
    int zipcode;
    std::string geo_id;
};

Residence::Residence() { //Constructor
    population=0;
    minimum_age=0;
    maximum_age=0;
    zipcode=0;
    gender="";
    geo_id="";
}

int partition(Residence *R, int first, int last){
    Residence temp;
    Residence pivot = R[last]; //selecting the last element as pivot
    int i = first-1;
    for(int j=first; j<last; j++){
        if(R[j].population< pivot.population || (R[j].population==pivot.population && R[j].geo_id<pivot.geo_id)){
            i++;
            //swapping A[i] and A[j]
            temp = R[i];
            R[i] = R[j];
            R[j] = temp;
        }
    }
    //swapping A[i+1] and A[last]
    temp = R[i+1];
    R[i+1] = R[last];
    R[last] = temp;

    return i+1;
}

void quickSort(Residence *R,int first_index, int last_index){

    if (first_index < last_index){
        int q = partition(R,first_index,last_index);
        quickSort(R, first_index, q-1);
        quickSort(R, q+1, last_index);
    }
}

int main(int argc, char* argv[]) {
    int N = std::atoi(argv[1]);
    int i = 0;
    Residence *residences = new Residence[N];
    std::string pop,min,max,gend,zip,geo,skipLine;

    std::ifstream infile("/home/baris/CLionProjects/project2/population_by_zip_2010.csv");
    //for(int j=0;j<56097;j++)  //I used this to skip rows randomly and select different data for finding average running time
    getline(infile, skipLine); //skipping first row

    while (getline(infile, pop, ',') && getline(infile, min, ',') && getline(infile, max, ',') &&
           getline(infile, gend, ',') && getline(infile, zip, ',') && getline(infile, geo, '\n') && i < N) {
        residences[i].population = atoi(pop.c_str());
        residences[i].minimum_age = atoi(min.c_str());
        residences[i].maximum_age = atoi(max.c_str());
        residences[i].gender = gend;
        residences[i].zipcode = atoi(zip.c_str());
        residences[i].geo_id = geo;
        i++;

    }

    infile.close();
    clock_t begin = clock();
    quickSort(residences, 0, N-1); //sorting
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC; //calculating sorting time
    std::cout << "Execution time: " << elapsed_secs << " s" << std::endl;

/*  std::ofstream output("output.csv"); //I have used it for writing the result in a different file which is used for worst-case.
    for (int j = 0; j < 1622831; ++j) {
        output << residences[j].population << "," << residences[j].minimum_age << "," << residences[j].maximum_age
                  << "," << residences[j].gender << "," << residences[j].zipcode << "," << residences[j].geo_id << std::endl;
    }*/

    /*for (int j = 0; j < N; ++j) { //I have used this for testing whether the result is true or not
        std::cout << residences[j].population << " " << residences[j].minimum_age << " " << residences[j].maximum_age
               << " " << residences[j].gender << " " << residences[j].zipcode << " " << residences[j].geo_id << std::endl;
    }*/

    return 0;
}