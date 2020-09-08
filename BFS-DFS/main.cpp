/*  Developed by Bayram Baris Sari
*   E-mail: bayrambariss@gmail.com
*   Tel No: +90 539 593 7501    
*
*   This is the implementation of Breadth First
*   Search and Depth First Search.
*   It solves the famous river problem. There are
*   Farmer, Rabbit, Carrow and Fox that want to cross
*   the river but there are many restrictions such as
*   only farmer can row, Fox east rabbit, rabbit eats
*   carrot if they stay alone etc.
*   This algorithm handles all possible situations, and
*   then applies BFS and DFS.
*/

#include "graph.h"
#include <iostream>
#include <list>
#include <ctime>


int main(int argc, char *argv[]) {
    std::string method = argv[1];
    std::list<int> path;
    int *p = nullptr;
    int i;
    Node *nodes = new Node[11];
    Graph g;    //creating adjacency node_list
    g.create_example_graph(nodes);

    clock_t begin = clock();
    if (method == "bfs") {
        std::cout << "Method : BFS" << std::endl;
        p = g.BFS(0);
    } else if (method == "dfs") {
        std::cout << "Method : DFS" << std::endl;
        p = g.DFS(0);
    } else
        std::cout << "Invalid argument!" << std::endl;

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    std::cout << "The number of nodes kept in memory: 11" << std::endl;  //Size of class Node objects
    std::cout << "Execution time: " << elapsed_secs << " s" << std::endl;

    path.push_front(10); //inserting the final node first, because parents will be pushed front
    i = p[10];
    while (p[i] != -1) {    //backtracking by using parent nodes
        path.push_front(i);
        i = p[i];   //p[x] is parent node of x
    }
    path.push_front(i); //inserting the first node
    g.print_path(path, nodes);

    delete p;
    return 0;
}