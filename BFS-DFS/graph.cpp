//
// Created by baris on 9.09.2020.
//
#include "graph.h"


Node Node::create(int e, int w, int number, variables vr, variables vr1, variables vr2, variables vr3) {
    Node n;
    std::string str[4];
    variables array[4] = {vr, vr1, vr2, vr3};
    for (int i = 0; i < 4; i++) {
        if (array[i] == Farmer)
            str[i] = " Farmer";
        else if (array[i] == Rabbit)
            str[i] = " Rabbit";
        else if (array[i] == Carrot)
            str[i] = " Carrot";
        else
            str[i] = " Fox";
    }
    for (int j = 0; j < e; j++)
        n.east[j] = str[j];
    for (int k = 0; k < w; k++)
        n.west[k] = str[3 - k];
    n.no = number;
    return n;
}

void Graph::insert(int from, const class Node &x) {
    node_list[from].push_back(x);  //add node x to the end of node_list[from]
}
