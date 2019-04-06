//
// Created by nscc on 1/26/18.
//

#include "LinkedList.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList() : first(nullptr) {};

LinkedList::~LinkedList()
{
    Node *node = first;

    while (node != nullptr)
    {
        Node *temp = node;

        node = node->next;

        delete temp;
    }
}

void LinkedList::Add(string line)
{
    Node *node = new Node();
    node->data = line;

    if (first == nullptr)
    {
        first = node;
    }
    else
    {
        Node *currNode = first;
        Node *prevNode = nullptr;

        while (currNode != nullptr)
        {
            prevNode = currNode;
            currNode = currNode->next;
        }

        if (prevNode != nullptr)
        {
            prevNode->next = node;
        }
    }
}

void LinkedList::DeleteNode(int nodenum)
{
    int index = 0;

    Node *node = first;
    Node *prev = nullptr;

    while (node != nullptr)
    {
        index++;

        if (index == nodenum)
        {
            break;
        }

        prev = node;
        node = node->next;
    }

    if (index >= 0)
    {
        if (node == first)
        {
            first = node->next;
        }
        else
        {
            prev->next = node->next;
        }

        delete node;
    }
}

void LinkedList::InsertBeforeNode(int nodenum, string data)
{
    int index = -1;
    Node *newnode = new Node();
    newnode->data = data;
    Node *node = first;
    Node *prev = first;

    //If nodenum is 0, prevent an endless loop and leave the method.
    if(nodenum == 0)
    {
        first = newnode;
        newnode->next = prev;
        return;
    }

    //Loop through the LinkedList until the correct node is found.
    while (node != nullptr)
    {
        index++;

        if (index == nodenum)
        {
            break;
        }

        prev = node;
        node = node->next;
    }

    // insert node into list
    if (first == nullptr)
    {
        first = newnode;
    }
    else
    {
        if (node != nullptr)
        {
            prev->next = newnode;
            newnode->next = node;
        }
        else
        {
            // could not find the node to insert after
            // so defaulting to Add function
            Add(data);
        }
    }
}

Node *LinkedList::GetNodeById(int nodenum)
{
    Node* currNode = first;
    Node* prevNode = nullptr;

    for (int i=1;currNode != nullptr;i++)
    {
        if (i == nodenum)
        {
            return currNode;
        }

        prevNode = currNode;
        currNode = currNode->next;
    }
    return currNode;
}

int LinkedList::size()
{
    int size = 0;
    Node* currNode = first;

    //Begin at the top of the list and count till the end of the list is reached.
    while(currNode != nullptr)
    {
        //Move to next node and check if nullptr
        size++;
        currNode = currNode->next;
    }

    return size;
}

ostream& operator<<(ostream& output, LinkedList& list)
{
    int lineNumber = 1;

    Node *currNode = list.first;

    while (currNode != nullptr)
    {
        output << "[" << lineNumber << "] " << currNode->data << endl;

        lineNumber++;

        currNode = currNode->next;
    }
    return output;
}



