//
// Created by baris on 9.09.2020.
//
#include "graph.h"

int *Graph::DFS(int s) {
    std::list<class Node>::iterator it;
    std::stack<int> stack;
    int u;
    int *parent = new int[11];  //it's necessary for backtracking
    bool discovered[11];

    //initially, parents are -1 and not any node is discovered yet
    for (int i = 0; i < 11; i++) {
        discovered[i] = false;
        parent[i] = -1;
    }
    //pushing s to the stack and mark it discovered
    stack.push(s);
    discovered[s] = true;

    while (!stack.empty()) {
        print_stack(stack) ;
        u = stack.top();
        stack.pop();
        if (discovered[u]) {} else discovered[u] = true;
        for (it = node_list[u].begin(); it != node_list[u].end(); ++it) {  //parsing adjacency node_list[u]
            if (discovered[(*it).no]) {}
            else {  //if node_list[u] has a node that not discovered, push it to stack, set parent of the node
                stack.push((*it).no);
                movCount++;
                parent[(*it).no] = u;
            }
            visitedNodes++;
        }
    }
    std::cout << "Number of visited nodes: " << visitedNodes << std::endl;
    std::cout << "Solution move count: " << movCount << std::endl;

    return parent;
}

