/*  Developed by Bayram Baris Sari
*   E-mail: bayrambariss@gmail.com
*   Tel No: +90 539 593 7501    
*
*	This project aims to solve closest
*	pair in 3D space problem. Instead of brute
*	force, it uses divide-and-conquer method.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>
#include <vector>

int total_calculation = 0;

class Coordinate{
private:
    int x,y,z;
public:
//    int num = 0;  // total number of distance calculation
    int setx(int setX){ x = setX; }
    int sety(int setY){ y = setY; }
    int setz(int setZ){ z = setZ; }
    int getx(){ return x;}
    int gety(){ return y;}
    int getz(){ return z;}
    void divide(std::vector<Coordinate>, std::vector<Coordinate>&, std::vector<Coordinate>&);
    double distance(Coordinate, Coordinate);
    double find_min(std::vector<Coordinate>&);
    double helper_min(std::vector<Coordinate>);
    std::vector<Coordinate> eliminate_points(std::vector<Coordinate>, double);
    void print(std::vector<Coordinate>);
};

double Coordinate::distance(Coordinate c1, Coordinate c2) {
    // Distance = sqrt( (x1-x2)^2 + (y1-y2)^2 + (z1-z2)^2)
    return sqrt(pow(c1.getx()-c2.getx(),2)+(pow(c1.gety()-c2.gety(),2))+(pow(c1.getz()-c2.getz(),2)));
}

void Coordinate::divide(std::vector<Coordinate> orig, std::vector<Coordinate> &sub1, std::vector<Coordinate> &sub2) {
    int median = orig.size()/2;
    int i=0;
    std::vector<Coordinate>::iterator it;
    // parse the original vector and divide it into sub1,sub2 from the median
    for(it = orig.begin(); it != orig.end(); ++it){
        if(i < median){
            sub1.push_back(*it);
        }else{
            sub2.push_back(*it);
        }
        i++;
    }
//    print(sub1);
//    print(sub2);
//    std::cout << "sub1: " << sub1.size() << "\tsub2: " << sub2.size() << std::endl;
}

double Coordinate::helper_min(std::vector<Coordinate> c) {
    double dist=0, min= 1000000;
    std::vector<Coordinate>::iterator i;
    std::vector<Coordinate>::iterator j;

    //check all point pairs and find the minimum distance
    for(i = c.begin(); i != c.end(); ++i) {
	// j is set to the next element of c, i. e. after i
	j = i;
	++j;
        for (; j != c.end(); ++j) {
            dist = distance(*i, *j);
            if (dist <= min) {
                min = dist;
            }
        }
        total_calculation++;
    }
    return min;
}

double Coordinate::find_min(std::vector<Coordinate> &c) {
    std::vector<Coordinate> eliminated;
    double min, min_left=0, min_right=0, min_lr=0;

    if(c.size() <= 4)
        return helper_min(c);

    // divide the vector of point pairs until its size is less than 5
    std::vector<Coordinate> temp1;
    std::vector<Coordinate> temp2;
    divide(c, temp1, temp2);
    min_left = find_min(temp1);
    min_right = find_min(temp2);

    // min = (smallest distance in left, smallest distance in right)
    min = min_right;
    if(min_left<min_right)
        min = min_left;

    /** Lets say the distance between x1 and x2 are the smallest and x1 is on the left, x2 is on the right
     *  We should create a new vector for this possibility. Points that at most 'min' far away from the median
     *  are added to eliminated and then are set to helper_min function     */
    eliminated = eliminate_points(c, min);
    min_lr = helper_min(eliminated);

    //find the minimum
    if (min_lr<min)
        min = min_lr;

    return min;
}

std::vector<Coordinate> Coordinate::eliminate_points(std::vector<Coordinate> c, double min) {
    std::vector<Coordinate> temp;
    std::vector<Coordinate>::iterator it;
    int median = c[c.size()/2].getx();
    // parse the vector c and add the point pairs that are most 'min' far away from the median
    for(it = c.begin(); it != c.end(); ++it){
        if(std::abs((*it).getx()-median) < min){
            temp.push_back(*it);
        }
    }
    return temp;
}

void Coordinate::print(std::vector<Coordinate> c) {
    std::vector<Coordinate>::iterator it;
    for(it = c.begin(); it != c.end(); ++it) { //I have used this for testing whether the result is true or not
          std::cout << (*it).getx() << " " << (*it).gety() << " " << (*it).getz() << std::endl;
      }
}

int partition(std::vector<Coordinate> &c, int first, int last){
    Coordinate temp;
    Coordinate pivot = c[last]; //selecting the last element as pivot
    int i = first-1;
    for(int j=first; j<last; j++){
        if(c[j].getx()< pivot.getx()){
            i++;
            //swapping A[i] and A[j]
            temp = c[i];
            c[i] = c[j];
            c[j] = temp;
        }
    }
    //swapping A[i+1] and A[last]
    temp = c[i+1];
    c[i+1] = c[last];
    c[last] = temp;

    return i+1;
}

void quickSort(std::vector<Coordinate> &c,int first_index, int last_index){

    if (first_index < last_index){
        int q = partition(c,first_index,last_index);
        quickSort(c, first_index, q-1);
        quickSort(c, q+1, last_index);
    }
}

int main(int argc, char* argv[]) {
    std::string file_name = argv[1];
    std::string line, line2;
    int x, y, z;
    int i=0; //counter
    int num_input = 0;
    double min = 0, tmp=0;
    std::vector<Coordinate> c;
    Coordinate temp;

    std::ifstream infile(file_name.c_str());
    getline(infile,line);   //read first line and learn the size of the data
    std::stringstream iss(line);
    iss >> num_input;
    while(getline(infile, line)){
        std::stringstream iss(line);
        iss >> x >> y >> z;
        temp.setx(x);
        temp.sety(y);
        temp.setz(z);
        c.push_back(temp);
    }
    infile.close();

    clock_t begin = clock();
    quickSort(c,0,c.size()-1);  //data is sorted by x coordinate, it takes O(nlogn)
    min = c[0].find_min(c);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC *1000;

    std::cout << "Number of Inputs: " << num_input << std::endl;
    std::cout << "Execution time: " << elapsed_secs << " ms" << std::endl;
    std::cout << "Total distance calculation: " << total_calculation << std::endl;
    std::cout << "Minimum Distance: " << min << std::endl;

    return 0;
}
