//
// Created by baris on 8.09.2020.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <list>
#include <stack>
#include <queue>
#include <iostream>

enum variables {
    Farmer, Rabbit, Carrot, Fox
};

class Node {
public:
    std::string east[4], west[4];
    int no;

    static Node create(int, int, int, variables, variables, variables, variables);
};


class Graph {
    std::list<class Node> *node_list;
    int visitedNodes;
    int movCount;
public:
    Graph() { // constructor
        node_list = new std::list<class Node>[11];
        visitedNodes = 0;
        movCount = 0;
    };

    void insert(int, const class Node &);

    int *BFS(int s);

    int *DFS(int s);

    static void print_path(std::list<int>, class Node *);

    //helper methods
    static void print_stack(std::stack<int>);

    static void print_queue(std::queue<int>);

    void create_example_graph(class Node *nodes);
};


#endif //GRAPH_H
