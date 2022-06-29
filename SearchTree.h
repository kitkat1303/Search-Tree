/*
 * @file SearchTree.h
 * @author Katarina McGaughy
 * SearchTree class: The SearchTree class takes in a Comparable Object and 
 * creates a BST based on Comparable objects and orderes them based on ASCII.
 * The purpose of this class is to store Comparable objects in ASCII order and keep
 * count of the number of times a character is found in a file. 
 *
 * Features:
 * -store Comparables in a BST 
 * -copy constructor
 * -assignment operator
 * -equality and inequality operator overload
 * -insert, delete, retrieve, get the height and depth of a node, and delete all contents 
 * of BST
 * -output stream (frequency of character and characters inorder)
 *
 * Assumptions:
 * -create a BST from Comparables 
 * -output will be inorder
 * -ASCII order determines the order of BST
 *
 * @version 0.1
 * @date 2022-1-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "Comparable.h"
using namespace std;
class SearchTree
{
    /**
    * Overloaded output operator for SearchTree class
    * Preconditions: SearchTree object character must be initialized
    * Postconditions: the BST inorder data and count is sent to the output stream
    * @param tree: SearchTree object
    * @param os: output stream
    * @return: output stream
    */
    friend ostream& operator<<(ostream& os, SearchTree& tree);

private:
    /**
    * Node struct contains a pointer to a Comparable object called data, a pointer to 
    * right child node and left child node, and a count for the frequency of the Comparable
    */
    struct Node {

        //pointer to Comparable object 
        Comparable* data = nullptr;

        //pointer to right child
        Node* rightChild = nullptr;

        //pointer to left child
        Node* leftChild = nullptr;

        //count of number of times char appears
        int count = 0;
    };

    //pointer to root of BST
    Node* root_;

    //keeps track of the number of nodes in the BST 
    int numberOfNodes;


    /**
    * comparingHelper
    * this function takes in a pointer to root of the current SearchTree and 
    * another one and compares both tree nodes 
    * Preconditions: There must be another SearchTree initialized to compare
    * Postconditions: returns true if both trees consist of the same nodes
    * @param otherRoot: node pointer to other ST root
    * @param thisRoot: node pointer to current root
    * @return: true if they consist of the same nodes
    */
    bool comparingHelper(Node* otherRoot, Node* thisRoot) const;

    /**
     * copyHelper
     * this function is a recursive function that copies the current tree 
     * Preconditions: There must be another SearchTree initialized 
     * Postconditions: helps create a copy of the current tree
     * @param copyRoot: node pointer to the tree that the copy will be assigned to 
     * @param thisRoot: node pointer to current root
     */
    void copyHelper(Node* copyRoot, Node*& thisRoot);


    /**
      * makeEmptyHelper
      * this is a recursive function that deletes all nodes in a tree 
      * Preconditions: none
      * Postconditions: empty SearchTree
      * @param root: pointer to root of SearchTree
      */
    void makeEmptyHelper(Node*& root);

    /**
      * insertHelper
      * this is a recursive function that finds the correct position to 
      * insert new Node with pointer to data 
      * Preconditions: none
      * Postconditions: either a new node is inserted in the tree with 
      * the Comparable data and true is returned or the node that 
      * holds the Comparable data is incremented by one and false is returned 
      * @param root: pointer to root of SearchTree
      * @param data: pointer to a Comparable object 
      * @return: true if a new node is inserted and false if a node is incremented
      */
    bool insertHelper(Node*& root, Comparable* data);

    /**
      * deleteNode
      * this is a recursive function that finds the correct position to
      * insert new Node with pointer to data
      * Preconditions: none
      * Postconditions: either a new node is inserted in the tree with
      * the Comparable data and true is returned or the node that
      * holds the Comparable data is incremented by one and false is returned
      * @param root: pointer to root of SearchTree
      * @param data: pointer to a Comparable object
      * @return: true if a new node is inserted and false if a node is incremented
      */
    bool deleteNode(Node*& root, const Comparable& data);


    void deleteRoot(Node*& root);


    Comparable* findAndDeleteMostLeft(Node*& root);


    const Comparable* retrieveHelper(const Node* root, const Comparable& data) const;


    int depthHelper(Node* root, const Comparable& data) const;

    int heightHelper(Node* root, const Comparable& data,
	int& height) const;


public:

    SearchTree();


    ~SearchTree();


    SearchTree(const SearchTree& copyTree);


    const SearchTree& operator=(const SearchTree& rhs);


    bool operator==(const SearchTree& rhs) const;


    bool operator!=(const SearchTree& rhs) const;


    void inorderPrint(Node* root);


    bool insert(Comparable* data);


    bool remove(const Comparable& data);


    void makeEmpty();


    const Comparable* retrieve(const Comparable& data) const;


    int depth(const Comparable& data) const;


    int height(const Comparable& data) const;


};

