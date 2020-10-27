#ifndef PriorityQueue_H
#define PriorityQueue_H
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
class FullQueue {};

class EmptyQueue {};

template <class ItemType>
struct QNode {
    ItemType info;
    int priority;
    QNode<ItemType>* next;
};

template <class ItemType>
class PriorityQueue {
   public:
    // Class constructor.
    PriorityQueue();

    ~PriorityQueue();
    // Class destructor.

    void enqueue(ItemType newItem, int priority);
    // Function: Adds newItem into the queue based on its priority.
    // A lower priority means the head is placed earlier in the queue
    // towards the front.
    // Post: If (queue is full) FullQueue exception is thrown
    //       else newItem is inserted into the proper location in queue.

    void enqueue(ItemType newItem);
    // Function: Adds newItem to the the queue.
    // This adds newItem with a priority of 0
    // Post: If (queue is full) FullQueue exception is thrown
    //       else newItem is inserted into queue.

    void dequeue(ItemType& item);
    // Function: deletes Item from the front of the queue and returns
    // it in item.
    // Post: If List is empty, EmptyQueue exception is thrown and item
    //       is undefined.
    //       else front item is dequeued and returned in item.

    ItemType peek() const;
    // returns the item at the front of the queue without
    // removing the item from the queue

    int peekPriority() const;
    // returns the priority of the  item at the front
    // of the queue without removing the item from the queue

    int length() const;
    // Function: returns the number of head in the queue
    // pre: List is initialized.
    // post: Function value = number of elements in the queue.
    //       and queue is unchanged.

    void printQueue(ofstream& stream);
    // Function: Prints the list to a file
    // pre: List is initialized
    // post: List is not changed

    void makeEmpty();
    // Function: Deallocates all list QNodes, and reinitializes the list to its empty state.
    // Pre: List is initialized
    // Post: list is empty.

    bool isEmpty() const;
    // Function: Determines whether the list is empty.
    // Pre: List is initialized
    // Post: Function value = (list is empty)

    bool isFull() const;
    // Function: Determines whether the list is full.
    // Pre: List is initialized
    // Post: Function value = (list is full)

   private:
    QNode<ItemType>* head;
    int Length;
    void findPred(int priority, QNode<ItemType>*& predecessor);
    // Finds the pred node based on priority
};
#endif