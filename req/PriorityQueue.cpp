#include "PriorityQueue.h"

// Class constructor.
template <class ItemType>
PriorityQueue<ItemType>::PriorityQueue() {
    head = NULL;
    Length = 0;
}

// Class destructor.
template <class ItemType>
PriorityQueue<ItemType>::~PriorityQueue() {
    makeEmpty();
}

// Function: Adds newItem into the queue based on its priority.
// A lower priority means the head is placed earlier in the queue
// towards the front.
// Post: If (queue is full) FullQueue exception is thrown
//       else newItem is inserted into the proper location in queue.
template <class ItemType>
void PriorityQueue<ItemType>::enqueue(ItemType newItem, int priority) {
    // Check for full list
    if(isFull()) {
        throw FullQueue();
    }

    // predecessor QNode
    QNode<ItemType>* pred;
    findPred(priority, pred);

    // Attemp to insert item
    QNode<ItemType>* newQNode = new QNode<ItemType>;
    newQNode->info = newItem;
    newQNode->priority = priority;
    if(pred == NULL) {
        // special case for inserting at beginning
        newQNode->next = head;
        head = newQNode;
    } else {
        // regular case, insert a new QNode in middle or at end of list
        newQNode->next = pred->next;
        pred->next = newQNode;
    }
    Length++;
}

// Function: Adds newItem to the the queue.
// This adds newItem with a priority of 0
// Post: If (queue is full) FullQueue exception is thrown
//       else newItem is inserted into queue.
template <class ItemType>
void PriorityQueue<ItemType>::enqueue(ItemType newItem) {
    enqueue(newItem, 1);
}

// Function: deletes Item from the front of the queue and returns
// it in item.
// Post: If List is empty, EmptyQueue exception is thrown and item
//       is undefined.
//       else front item is dequeued and returned in item.
template <class ItemType>
void PriorityQueue<ItemType>::dequeue(ItemType& item) {
    if(isEmpty()) {
        throw EmptyQueue();
    }

    // delete first element
    QNode<ItemType>* loc = head;
    item = head->info;
    head = head->next;
    loc->next = NULL;
    delete loc;
    Length--;
}

// returns the item at the front of the queue without
// removing the item from the queue
template <class ItemType>
ItemType PriorityQueue<ItemType>::peek() const {
    if(isEmpty()) {
        throw EmptyQueue();
    }
    return head->info;
}

// returns the priority of the  item at the front
// of the queue without removing the item from the queue
template <class ItemType>
int PriorityQueue<ItemType>::peekPriority() const {
    if(isEmpty()) {
        throw EmptyQueue();
    }
    return head->priority;
}

// Function: returns the number of head in the queue
// pre: List is initialized.
// post: Function value = number of elements in the queue.
//       and queue is unchanged.
template <class ItemType>
int PriorityQueue<ItemType>::length() const {
    return Length;
}

// Function: Prints the list to a file
// pre: List is initialized
// post: List is not changed
template <class ItemType>
void PriorityQueue<ItemType>::printQueue(ofstream& stream) {
    QNode<ItemType>* temp = head;
    stream << "Queue: ";
    while(temp != NULL) {
        stream << temp->info << " ";
        temp = temp->next;
    }
    stream << endl;
}

// Function: Deallocates all list QNodes, and reinitializes the list to its empty state.
// Pre: List is initialized
// Post: list is empty.
template <class ItemType>
void PriorityQueue<ItemType>::makeEmpty() {
    QNode<ItemType>* tempPtr;
    while(head != NULL) {
        tempPtr = head;
        head = head->next;
        delete tempPtr;
    }
    Length = 0;
}

// Function: Determines whether the list is empty.
// Pre: List is initialized
// Post: Function value = (list is empty)
template <class ItemType>
bool PriorityQueue<ItemType>::isEmpty() const {
    return head == NULL;
}

// Function: Determines whether the list is full.
// Pre: List is initialized
// Post: Function value = (list is full)
template <class ItemType>
bool PriorityQueue<ItemType>::isFull() const {
    // Try to allocate a new QNode, if not possible then list if full
    try {
        QNode<ItemType>* temp = new QNode<ItemType>;
        delete temp;
        return false;
    } catch(std::bad_alloc) {
        return true;
    }
}

// Function: Searches the list for priority and returns a pointer to item's predecessor QNode.
// pre: list is initialized
// post: (1) predecessor contains the address of item's predecessor QNode
//        i.e. QNode with largest priority < param priority
//        if no predescessor exit and predecessor is set to NULL.
template <class ItemType>
void PriorityQueue<ItemType>::findPred(int priority, QNode<ItemType>*& predecessor) {
    predecessor = NULL;
    QNode<ItemType>* location = head;
    while(location != NULL && location->priority <= priority) {
        predecessor = location;
        location = location->next;
    }
}
