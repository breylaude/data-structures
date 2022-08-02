#include <iostream>
#include "../Timer/timer.cpp"
#include "linkedList.h"
using namespace std;

LinkedList::LinkedList()
{
    this->head = nullptr;
    this->tail = nullptr;
}

LinkedList::~LinkedList()
{
    while (head != nullptr)
        pop_front();
}

bool LinkedList::isEmpty()
{
    if (head == nullptr)
    {
        return true;
    }
    return false;
}

void LinkedList::printList()
{
    ListNode *temp = head;
    if (temp == nullptr)
    {
        cout << "List is empty!\n";
        return;
    }

    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
}

// Add element at the end
void LinkedList::push_back(int data)
{
    ListNode *newNode = new ListNode(data);
    if (head == nullptr)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Add element at the beginning
void LinkedList::push_front(int data)
{
    ListNode *newNode = new ListNode(data);
    if (head == nullptr)
    {
        head = tail = newNode;
    }
    else
    {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
}

// Delete element from the position
void LinkedList::deleteFromPos(int position)
{

    ListNode *temp = head;
    for (int i = 0; temp != nullptr && i < position; i++)
    {
        temp = temp->next;
    }

    pop_node(temp);
}

// Pop the last node
void LinkedList::pop_back()
{
    pop_node(tail);
}

// Pop the first node
void LinkedList::pop_front()
{
    pop_node(head);
}

// Insert element at the position
void LinkedList::insert(int value, int position)
{

    ListNode *temp = head;
    if (position == 0)
        push_front(value);

    for (int i = 0; temp != nullptr && i < position - 3; i++)
    {
        temp = temp->next;
    }

    if (temp == nullptr)
        return;

    ListNode *newNode = new ListNode(value);
    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next = newNode;
    if (newNode->next != nullptr)
    {
        newNode->next->prev = newNode;
    }
}

// Delete the particular node
void LinkedList::pop_node(ListNode *node)
{
    if (node == nullptr)
        return;
    if (node->prev)
        node->prev->next = node->next;
    else
        head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        tail = node->prev;

    free(node);
}

ListNode *LinkedList::findElement(int val)
{

    ListNode *temp = head;

    if (head == nullptr)
        return nullptr;

    while (temp != nullptr)
    {
        if (temp->data == val)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
