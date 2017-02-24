/**
* @file wl.h
* @author Skyler Norris <skynorris1@gmail.com>
* @version 1.0
*
* @section LICENSE
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
*
* @section DESCRIPTION
*
* This file loads in a text file.  After loading in the text file, this program stores
* every word in that file in a BST.  It can then locate any word in the file and return
*  how far into the file (the wordocunt) of any word.  It can also tell you where the specific
*  occurence of that word is.
*/

#ifndef __WL_H_INCLUDED__
#define __WL_H_INCLUDED__



#include <cxxabi.h>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iterator>

using namespace std;

/**
* @brief A simple Node struct
* @author Skyler Norris
 *
* @
*
* This is a simple node struct that contains pointers to its
 * left and riht child, as well as a name field which repersents the
 * string it corresponds to and a wordcount field which says how far into
 * the file the string is.
*/
typedef struct Node
{
    string name; /*!< stirng name of word node corresponds to */
    int wordCount; /*!< where the word occurs in file */
    struct Node* left; /*!< left child */
    struct Node* right; /*!< right child */
}Node;

/**
* @brief A BST tree
* @author Skyler Norris
*
* This is a the BST tree we will use.  It points the root node.
*/
typedef struct
{
    Node* root; /*!< pointer to root node of tree */
}RBtree;


/**
* This method finds the wordcount of a particular word and its
* occurence number in the file.  If the word doesnt exist in the
* file it returns 0.  It is recursive.
*
* @param root the root of the tree to pass in
* @param word which word you want to look uo
* @param occurence the ith occurence of the word in the file
* @param pt points to an int vairbale that keeps track of which
* occurence you are at in the tree
*
* @return returns the word count of the node you are looking for.
* Returns 0 if the word is not found.
*/
int lookup(Node* root, string word, int occurence, int* pt);


/**
* This method inserts a node into the BST tree.  It is recursive.
*
* @param root the root of the tree to pass in
* @param new_node the node you are inserting to the tree.
*/
void Insert(Node *root, Node *new_node);


/**
* This method loads in a file.  First it checks if the file
* to be loaded is valid.  Then it inserts all of the words from
* the file into the BST to build the tree.
*
* @param file the name of the file in string format.  Absolute or
* relative path accepted.
*/
void loadFile(string file);

/**
* This method loads take a string and outputs whether every
 * character in that string is a digit.
*
* @param s the string to look at
* @return true if the string is a number, false otherwise.
*/
bool is_number(string s);


/**
* This method frees all of the nodes in the BST.  It recursively
* frees them from bottum up.
*
* @param root  the root of the BST.
*/
void freeTree(Node* root);

#endif