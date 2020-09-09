//
// Created by baris on 9.09.2020.
//
#include "graph.h"


int *Graph::BFS(int s) {
    std::list<class Node>::iterator it;
    std::list<class Node> temp;
    std::queue<int> queue;
    int u;
    int *parent = new int[11];  //its necessary for backtracking
    bool discovered[11];

    //initially, parents are -1 and not any node is discovered yet
    for (int i = 0; i < 11; i++) {
        discovered[i] = false;
        parent[i] = -1;
    }

    queue.push(s);
    discovered[s] = true;
    while (!queue.empty()) {
        print_queue(queue);
        u = queue.front();
        queue.pop();
        for (it = node_list[u].begin(); it != node_list[u].end(); ++it) {  //parsing the node_list[u]
            if (!discovered[(*it).no]) {    //if a node hasn't been discovered yet, mark it discovered, set parent and push it to the queue
                discovered[(*it).no] = true;
                parent[(*it).no] = u;
                queue.push((*it).no);
                movCount++;
            }
            visitedNodes++;
        }
    }
    std::cout << "Number of visited nodes: " << visitedNodes << std::endl;
    std::cout << "Solution move count: " << movCount << std::endl;
    return parent;
}
