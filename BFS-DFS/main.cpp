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

#include <iostream>
#include <queue>
#include <list>
#include <stack>
#include <ctime>

enum variables {
    Farmer, Rabbit, Carrot, Fox
};

class Node {
public:
    std::string east[4], west[4];
    int no{};

    static Node create(int, int, int, variables, variables, variables, variables);
};

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

class Graph {
    std::list<class Node> *list;
    int visitedNodes;
    int movCount;
public:
    Graph(); //constructor
    void insert(int, const class Node &);

    int *BFS(int s);

    int *DFS(int s);

    static void print_path(std::list<int>, class Node *);

    //helper methods
    static void print_stack(std::stack<int>);

    static void print_queue(std::queue<int>);

    void create_example_graph(class Node *nodes);
};

Graph::Graph() {
    list = new std::list<class Node>[11];
    visitedNodes = 0;
    movCount = 0;
}

void Graph::insert(int from, const class Node &x) {
    list[from].push_back(x);  //add node x to the end of list[from]
}

int *Graph::BFS(int s) {
    std::list<class Node>::iterator it;
    std::list<class Node> temp;
    std::queue<int> queue;
    int u;
    int *parent = new int[11];  //its necessary for backtracking
    bool discovered[11];

    //initially, parents are -1 and all nodes aren't discovered yet
    for (int i = 0; i < 11; i++) {
        discovered[i] = false;
        parent[i] = -1;
    }

    queue.push(s);
    discovered[s] = true;
    while (!queue.empty()) {
//        print_queue(queue);

        u = queue.front();
        queue.pop();
        for (it = list[u].begin(); it != list[u].end(); ++it) {  //parsing the list[u]
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

int *Graph::DFS(int s) {
    std::list<class Node>::iterator it;
    std::stack<int> stack;
    int u;
    int *parent = new int[11];  //it's necessary for backtracking
    bool discovered[11];

    //initially, parents are -1 and all nodes aren't discovered yet
    for (int i = 0; i < 11; i++) {
        discovered[i] = false;
        parent[i] = -1;
    }
    //pushing s to the stack and mark it discovered
    stack.push(s);
    discovered[s] = true;

    while (!stack.empty()) {
//        print_stack(stack) ;

        u = stack.top();
        stack.pop();
        if (discovered[u]) {} else discovered[u] = true;
        for (it = list[u].begin(); it != list[u].end(); ++it) {  //parsing adjacency list[u]
            if (discovered[(*it).no]) {}
            else {  //if list[u] has a node that not discovered, push it to stack, set parent of the node
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

void Graph::print_path(std::list<int> ls, class Node *nodes) {
    std::list<int>::iterator it;
    std::list<int>::iterator prev;

    for (it = ls.begin(), prev = ls.end();
         it != ls.end(); prev = it, ++it) { //parsing nodes according to path, prev is the previous node
        if (prev != ls.end()) {    //if there is previous node
            std::cout << "(Farmer, ";

            //if farmer is at east now, that means he comes from west alone or with fox,carrot or rabbit
            if (nodes[*it].east[0] == " Farmer" || nodes[*it].east[1] == " Farmer" || nodes[*it].east[2] == " Farmer" ||
                nodes[*it].east[3] == " Farmer") {
                for (auto &i : nodes[*it].east) {
                    if (!i.empty() && i != " Farmer") { //continue if east[i] is not empty or farmer
                        for (auto &j : nodes[*prev].west) {  //check the thing which was at west before, and it is at east now
                            if (i == j) { //if it's found, print it and break inner loop
                                std::cout << i << ", ";
                                break;
                            }
                        }
                    }
                }
                std::cout << "<)";
            } else {  //if he is at west now, that means he was east side of the river
                for (auto & i : nodes[*it].west) {
                    if (!i.empty() &&  i != " Farmer") { //continue if west[i] is not empty or farmer
                        for (auto & j : nodes[*prev].east) {  //check the thing which was at east before, and it is at west now
                            if (i == j) {  //if it's found, print it and break inner loop
                                std::cout << i << ", ";
                                break;
                            }
                        }
                    }
                }
                std::cout << ">)";
            }
        }
        std::cout << std::endl << nodes[*it].east[0] << nodes[*it].east[1] << nodes[*it].east[2] << nodes[*it].east[3]
                  << " ||" << nodes[*it].west[0] << nodes[*it].west[1] << nodes[*it].west[2] << nodes[*it].west[3]
                  << std::endl;
    }
}

void Graph::print_stack(std::stack<int> s) {
    while (!s.empty()) {
        std::cout << s.top();
        s.pop();
    }
}

void Graph::print_queue(std::queue<int> q) {
    while (!q.empty()) {
        std::cout << q.front();
        q.pop();
    }
}

void Graph::create_example_graph(class Node *nodes) {
    /**creating nodes, first parameter of them are on the east of the river, second parameter
    of them are on the west of the river, third parameter is the node number, and last 4 parameters
     are order of them. For example, 3,1, Farmer, Rabbit,Carrot,Fox means that Farmer,Rabbit and Carrot
     are on the east side of the river and Fox is on the west side of the river**/
    nodes[0] = nodes[0].create(4, 0, 0, Farmer, Rabbit, Carrot, Fox);
    nodes[1] = nodes[1].create(3, 1, 1, Rabbit, Carrot, Fox, Farmer);
    nodes[2] = nodes[0].create(2, 2, 2, Carrot, Fox, Farmer, Rabbit);
    nodes[3] = nodes[0].create(3, 1, 3, Farmer, Carrot, Fox, Rabbit);
    nodes[4] = nodes[0].create(1, 3, 4, Carrot, Fox, Rabbit, Farmer);
    nodes[5] = nodes[0].create(1, 3, 5, Fox, Farmer, Rabbit, Carrot);
    nodes[6] = nodes[0].create(3, 1, 6, Farmer, Rabbit, Carrot, Fox);
    nodes[7] = nodes[0].create(3, 1, 7, Farmer, Rabbit, Fox, Carrot);
    nodes[8] = nodes[0].create(1, 3, 8, Rabbit, Farmer, Carrot, Fox);
    nodes[9] = nodes[0].create(2, 2, 9, Farmer, Rabbit, Carrot, Fox);
    nodes[10] = nodes[0].create(0, 4, 10, Farmer, Rabbit, Carrot, Fox);

    /**Creating the graph by connecting the nodes*/
    (*this).insert(0, nodes[1]);
    (*this).insert(1, nodes[0]);

    (*this).insert(0, nodes[2]);
    (*this).insert(2, nodes[0]);

    (*this).insert(2, nodes[3]);
    (*this).insert(3, nodes[2]);

    (*this).insert(3, nodes[4]);
    (*this).insert(4, nodes[3]);

    (*this).insert(3, nodes[5]);
    (*this).insert(5, nodes[3]);

    (*this).insert(4, nodes[6]);
    (*this).insert(6, nodes[4]);

    (*this).insert(5, nodes[7]);
    (*this).insert(7, nodes[5]);

    (*this).insert(6, nodes[8]);
    (*this).insert(8, nodes[6]);

    (*this).insert(7, nodes[8]);
    (*this).insert(8, nodes[7]);

    (*this).insert(8, nodes[9]);
    (*this).insert(9, nodes[8]);

    (*this).insert(9, nodes[10]);
    (*this).insert(10, nodes[9]);
}

int main(int argc, char *argv[]) {
    std::string method = argv[1];
    std::list<int> path;
    int *p = nullptr;
    int i;
    Node *nodes = new Node[11];
    Graph g;    //creating adjacency list
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