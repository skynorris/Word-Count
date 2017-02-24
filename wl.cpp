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
#include <string.h>


//
using namespace std;

typedef struct Node
{
    string name;
    int wordCount;
    struct Node* left;
    struct Node* right;
}Node;

typedef struct
{
    Node* root;
}RBtree;

//new tree
RBtree* wordTree = new RBtree;

int lookup(Node* root, string word, int occurence, int* pt){

    //fields
    if (root == NULL) {
        *pt = 1;
        return 0;
    }

    //base case 
    if (word == root->name) {


        if(*pt == occurence ){
            *pt = 1;
            return root->wordCount;
        }else{
            *pt = *pt +1;
            return lookup(root->right, word, occurence, pt);
        }

    }

    else if (word < root->name) {
        return lookup(root->left, word, occurence, pt);
    }

    else if (word > root->name) {
        return lookup(root->right, word, occurence, pt);
    }
}

void Insert(Node *root, Node *new_node) {


    if (new_node->name < root->name) {
        if (root->left == NULL)
            root->left = new_node;
        else
            Insert(root->left, new_node);
    }

    else {
        if (root->right == NULL)
            root->right = new_node;
        else
            Insert(root->right, new_node);
    }
}

void loadFile(string file){

    //fields
    string wordRaw;

    //attempt to open file
    ifstream infile(file.c_str());

    //load in new file nd add to array


    int count = 1;
    while (infile >> wordRaw)
    {
        //word to be added
        string word;
        Node* addWord = new Node;

        //get rid of punctuation and convert to lower case
        remove_copy_if(wordRaw.begin(), wordRaw.end(), back_inserter(word), ptr_fun<int, int>(&std::ispunct));
        wordRaw.erase (wordRaw.begin(), wordRaw.end());
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        //intialize fields
        addWord ->name = word;
        addWord->wordCount = count;
        addWord->left = NULL;
        addWord->right = NULL;

        //insert node
        if(wordTree->root == NULL){
            wordTree->root = addWord;
        }else {
            Insert(wordTree->root, addWord);
        }

        count ++;
    }


}

bool is_number(string s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void freeTree(Node* root){

    if(root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);

    delete root;
}

int main()
{

    //intiialize
    wordTree->root = NULL;

    bool done = false;
    string last;
    while(!done) {
        //promt user
        cout << ">";

        //get user input
        string input;
        getline(cin, input);
        transform(input.begin(), input.end(), input.begin(), ::tolower);


        //fields
        istringstream iss(input);
        bool bad = false;
        vector<string> inputVec;
        string command;

        //get rid of white space
        copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             back_inserter(inputVec));


        command = inputVec[0];

        if (command == "load") {


            //file
            ifstream infile(inputVec[1].c_str());

            if (inputVec.size() != 2) {
                bad = true;

            }if(!infile){
                bad = true;
            }if(wordTree->root != NULL && last != "load"){
                bad = true;
            }

            if(bad == false){

                loadFile(inputVec[1].c_str());
            }

        } else if (command == "locate") {

            if (inputVec.size() != 3 || !is_number(inputVec[2])) {
                bad = true;
            } else {

                //for lookup
                int occurence = atoi(inputVec[2].c_str());
                int i = 1;
                int* pt = &i;

                if( lookup(wordTree->root, inputVec[1], occurence, pt) == 0){
                    cout << "No matching entry." << endl;
                }else{
                    cout << lookup(wordTree->root, inputVec[1], occurence, pt) <<endl;
                }
            }

        } else if (command == "new") {
            if (inputVec.size() != 1) {
                bad = true;
            } else {

                freeTree(wordTree->root);
                wordTree->root = NULL;


            }

        } else if (command == "end") {
            if (inputVec.size() != 1) {
                bad = true;
            } else {
                done = true;
                freeTree(wordTree->root);
            }
        } else {
            bad = true;
        }


        if (bad) {
            cout << "ERROR: Invalid command" << endl;
        }
        last = inputVec[0];
    }

    //free pointers
    delete wordTree;

    return 0;
}
