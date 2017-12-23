/*  Bayram Baris Sari
*   150130123
*   Project IV    */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

enum gender {FEMALE, MALE};
enum color{RED, BLACK};

struct Person{
    std::string name;
    int age;
    gender gend;
    int color;
    Person *left,*right, *parent;

    //augmenting the tree
    int man;
    int woman;
};

// Red Black tree
class RedBlackTree{
public:
    RedBlackTree() { root = NULL;};
    Person *root;
    void insertion(std::string name, int age, gender gender);
    void leftRotation(Person *parent);
    void rightRotation(Person *grandpa);
    int depth(Person *rt, Person *node);
    int inOrder(Person *node);

    //augmented methods
    std::string num_woman(Person *node, int x);
    std::string num_man(Person *node, int x);
    int size(Person *node, gender g);
};

void RedBlackTree::insertion(std::string name, int age, gender gender) {
    Person *temp;
    Person *current = NULL;
    /*Creating new node*/
    Person *p = new Person;
    p->age = age;
    p->name = name;
    p->gend = gender;
    p->left = NULL;
    p->right = NULL;
    p->parent = NULL;
    p->color = RED;
    if(gender == FEMALE){
        p->man = 0;
        p->woman = 1;
    }else {
        p->man = 1;
        p->woman = 0;
    }

    if (root == NULL){
        root = p;
    } else {
        current = root;
        //traversing the tree until finding where to insert the node
        while (current) {
            temp = current;
            if (p->name > current->name) {
                current->woman = size(current, FEMALE) + p->woman;
                current->man = size(current, MALE) + p->man;
                current = current->right;
            }else{
                current->woman = size(current, FEMALE) + p->woman;
                current->man = size(current, MALE) + p->man;
                current = current->left;
            }
        }
        //inserting as right child or left child
        if (p->name > temp->name)
            temp->right = p;
        else
            temp->left = p;

        p->parent = temp;
        //checking Red Black Tree's 3 rules
        while (p != root && p->parent->color == RED && p->parent->parent != NULL) {

            if (p->parent == p->parent->parent->left) {     //if parent node is the left child

                if (p->parent->parent->right != NULL && p->parent->parent->right->color == RED) {
                    //if uncle of p exists and its color is red
                    //case#1 - recoloring nodes - parent and uncle turn BLACK and parent of parent turns into RED
                    p->parent->parent->right->color = BLACK;
                    p->parent->color = BLACK;
                    if (p->parent->parent != root) { //checks if parent of parent node is root or not because root has to be always black
                        p->parent->parent->color = RED;
                        p = p->parent->parent;  //p becomes its parent of parent node
                    }

                } else {
                    if (p == p->parent->right) {   //if node is a right child
                        //case#2 - parent node and node is red, we need to use left rotation for solving this problem
                        p = p->parent;  //p becomes its parent node
                        leftRotation(p);
                        //size of woman and man of the node and its parent node are changed, so we need to recompute them
                        p->woman = size(p, FEMALE);
                        p->man = size(p, MALE);
                        p->parent->woman = size(p->parent, FEMALE);
                        p->parent->man = size(p->parent, MALE);

                    }
                    /*case#3 - node is the left child of its parent and they both are red,
                     * we need to use right rotation for solving this problem*/
                    p->parent->color = BLACK; //first we need to change color of parent node and parent of parent node
                    p->parent->parent->color = RED;
                    rightRotation(p->parent->parent);
                    //size of woman and man of parent and uncle nodes are changed, so we need to recompute them
                    p->parent->woman = size(p->parent, FEMALE);
                    p->parent->man = size(p->parent, MALE);
                    p->parent->right->woman = size(p->parent->right, FEMALE);
                    p->parent->right->man = size(p->parent->right, MALE);
                }

            } else {
                if (p->parent->parent->left != NULL && p->parent->parent->left->color == RED) {
                    //if uncle of p exists and its color is red
                    //case#1 - recoloring nodes - parent and uncle turn BLACK and parent of parent turns into RED
                    p->parent->parent->left->color = BLACK;
                    p->parent->color = BLACK;
                    if (p->parent->parent != root) { //checks if parent of parent node is root or not because root has to be always black
                        p->parent->parent->color = RED;
                        p = p->parent->parent;  //p becomes its parent of parent node
                    }

                } else {
                    if (p == p->parent->left) {   //if node is a left child
                        //case#2 - parent node and node is red, we need to use left rotation for solving this problem
                        p = p->parent;  //p becomes its parent node
                        rightRotation(p);

                        //size of woman and man of the node and its parent node are changed, so we need to recompute them
                        p->woman = size(p, FEMALE);
                        p->man = size(p, MALE);
                        p->parent->woman = size(p->parent, FEMALE);
                        p->parent->man = size(p->parent, MALE);
                    }
                    /*case#3 - node is the left child of its parent and they both are red,
                     * we need to use right rotation for solving this problem*/
                    p->parent->parent->color = RED; //first we need to change color of parent node and parent of parent node
                    p->parent->color = BLACK;
                    leftRotation(p->parent->parent);
                    //size of woman and man of parent and uncle nodes are changed, so we need to recompute them
                    p->parent->woman = size(p->parent, FEMALE);
                    p->parent->man = size(p->parent, MALE);
                    p->parent->left->woman = size(p->parent->left, FEMALE);
                    p->parent->left->man = size(p->parent->left, MALE);
                }

            }
        }
    }
    root->color = BLACK;    //root is always black
    delete[] current;   //freeing memory
}

/**I have implemented this function according to the pseudocode from "Introduction to Algorithms"
  LEFT-ROTATE(T, x)
  1   y = x.right             // set y
  2   x.right = y.left        // turn y’s left subtree into x’s right subtree

  3   if y.left != T.nil
  4       y.left.p = x
  5   y.p = x.p               // link x’s parent to y

  6   if x.p == T.nil
  7       T.root = y

  8   elseif x == x.p.left
  9       x.p.left = y

  10  else x.p.right = y

  11  y.left = x              // put x on y’s left
  12  x.p = y**/
void RedBlackTree::leftRotation(Person *parent) {
    if(parent == NULL || parent->right == NULL)
        return;
    Person *y;
    y = parent->right;
    parent->right = y->left;

    if (y->left != NULL){
        y->left->parent = parent->parent;
    }
    y->parent = parent->parent;
    if(parent->parent == NULL){
        root = y;
    } else if(parent == parent->parent->left){
            parent->parent->left = y;
    }else{
            parent->parent->right = y;
    }
    y->left = parent;
    parent->parent = y;
}

/**I have again implemented this function according to the pseudocode from "Introduction to Algorithms"
  RIGHT-ROTATE(T, x)
  1   y = x.left
  2   x.left = y.right

  3   if y.right != T.nil
  4       y.right.p = x
  5   y.p = x.p

  6   if x.p == T.nil
  7       T.root = y

  8   elseif x == x.p.right
  9       x.p.right = y

  10  else x.p.left = y

  11  y.right = x
  12  x.p = y **/
void RedBlackTree::rightRotation(Person *grandpa){
    if(grandpa == NULL || grandpa->left == NULL)
        return;

    Person *y;
    y = grandpa->left;
    grandpa->left = y->right;
    if(y->right != NULL) {
        y->right->parent = grandpa;
    }
    y->parent = grandpa->parent;
    if(grandpa->parent == NULL){
        root = y;
    } else if(grandpa == grandpa->parent->right){
        grandpa->parent->right = y;
    } else {
        grandpa->parent->left = y;
    }
    y->right = grandpa;
    grandpa->parent = y;
}


int RedBlackTree::depth(Person *rt, Person *node) {
    //it computes the depth of the node
    int d = 0;
    if(rt == NULL)
        return 0;
    else if (rt == node)
        return 1 + d;
    else if ((d = (depth(rt->left, node))) > 0)
        return 1 + d;
    else if ((d = (depth(rt->right, node))) > 0)
        return 1 + d;
}

/** I have used this pseudo code from the book and have modified print x.key part
INORDER-TREE-WALK(x)
    if x != NIL

        INORDER-TREE-WALK(x.left)
        print x.key
        INORDER-TREE-WALK(x.right)  **/
int RedBlackTree::inOrder(Person *node) {
    Person *p;
    int distance = 0;
    p = node;
    if(p != NULL){
        if(p->left) inOrder(p->left);

        distance = depth(root, p); //finds the level of depth and put tabs according to that
        for (int i = 0; i < distance-1; ++i)
            std::cout << "\t";

        if(p == root){}
        else if(p == p->parent->left)  {std::cout << "┌───";}
        else   {std::cout << "└───";}

        std::cout << (node->color == BLACK ? "(B)" : "(R)");
        std::cout << p->name << "-" << p->age << "-";
        std::cout << (p->gend == FEMALE ? "F" : "M") << std::endl;

        if(p->right)    inOrder(p->right);
    }
    return 0;
}


int RedBlackTree::size(Person *node, gender g){
    if(node == NULL)
        return 0;

    if(node->gend == g) {
        if (node->left == NULL && node->right == NULL)
            return 1;
        else if (node->left == NULL)
            return size(node->right, g) + 1;
        else if (node->right == NULL)
            return size(node->left, g) + 1;
        else
            return size(node->left, g) + size(node->right, g) + 1;
    } else {
        if (node->left == NULL && node->right == NULL)
            return 0;
        else if (node->left == NULL)
            return size(node->right, g);
        else if (node->right == NULL)
            return size(node->left, g);
        else
            return size(node->left, g) + size(node->right, g);
    }
}

/** I have modified this pseudocode from the book for the next 2 methods
 OS-SELECT(x, i)
 r = size[left[x]]+1
 if i = r

then return x
 elseif i < r

then return OS-SELECT (left[x], i)
 else return OS-SELECT (right[x], i−r) **/
std::string RedBlackTree::num_woman(Person *node, int x) {
    int k;

    if(node->left) //check if left child of the node exists or not
        k = node->left->woman + 1;
    else
        k = node->woman;

    if(x == k && node->gend == FEMALE)  return node->name;  //it's found
    if(x < k)   return num_woman(node->left, x);
    else{
        if (node->gend == FEMALE)
            return num_woman(node->right, x-k);
        else
            return num_woman(node->right, x-k+1);
    }
}

std::string RedBlackTree::num_man(Person *node, int x) {
    int k;
    if(node->left)  //check if left child of the node exists or not
        k = node->left->man + 1;
    else
        k = node->man;

    if(x == k && node->gend == MALE)    return node->name;  //it's found
    if(x < k)   return num_man(node->left, x);
    else{
        if (node->gend == MALE)
            return num_man(node->right, x-k);
        else
            return num_man(node->right, x-k+1);
    }
}

int main(int argc, char* argv[]) {
    RedBlackTree tree;

    std::string inputFileName = argv[1];
    std::string line;
    std::string tempName;
    char tempGender;
    gender tmpGender;
    int tempAge;

    std::ifstream infile(inputFileName);
    while (std::getline(infile, line)) { //reading the file line-by-line
        std::stringstream iss(line);
        iss >> tempName >> tempGender >> tempAge;

        if(tempGender == 'F')
            tmpGender = FEMALE;
        else
            tmpGender = MALE;

        tree.insertion(tempName, tempAge, tmpGender);
    }
    infile.close();

    tree.inOrder(tree.root);

    std::string name = tree.num_woman(tree.root, 3);
    std::cout << std::endl << "3th woman name is " << name << std::endl;

    std::string name2 = tree.num_man(tree.root, 4);
    std::cout << "4th man name is " << name2 << std::endl;

    return 0;
}