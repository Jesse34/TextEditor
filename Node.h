//
// Created by nscc on 1/26/18.
//

#ifndef ASS1_TEXTEDITOR_NODE_H
#define ASS1_TEXTEDITOR_NODE_H


#include <string>
using std::string;

class Node
{
public:
    string data;
    Node *next;

    Node() : next(nullptr), data("") {}
};


#endif //ASS1_TEXTEDITOR_NODE_H
