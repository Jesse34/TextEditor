//
// Created by nscc on 1/26/18.
//

#ifndef ASS1_TEXTEDITOR_LINKEDLIST_H
#define ASS1_TEXTEDITOR_LINKEDLIST_H

#include "Node.h"

using namespace std;

class LinkedList
{
private:
    Node *first;

public:
    LinkedList();

    virtual ~LinkedList();

    void Add(string line);

    //void DeleteValue(string line);

    void DeleteNode(int nodenum);

    //void InsertAfterValue(string value, int num);

    void InsertBeforeNode(int nodenum, string data);

    Node* GetNodeById(int nodenum);

    int size();


    friend ostream& operator<<(ostream& output, LinkedList& list);
};


#endif //ASS1_TEXTEDITOR_LINKEDLIST_H
