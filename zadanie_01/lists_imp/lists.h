template <typename T>
class Lists
{
public:
    Lists();
    Lists(T first);
    template <typename... Args> Lists(...);
    ~Lists();
    void push_front(T val);
    void push_back(T val);
    void pop_front();
    void pop_back();
    void front();
    void back();

    Lists<T> operator=(T val);

private:
    struct Node
    {
        T value;
        Node *next;
    };
    Node head;
    Node tail;
    Node *newNode(T value, Node *n=nullptr);
    void deleteNode();
    void initiate();
};

template <typename T>
class twoWayList : public Lists<T>
{
public:
    /*there will be a two-way list here
               x
    .-. _______|
    |=|/     /  \
    | |_____|_""_|
    |_|_[X]_|____|
    */

private:
    struct Node
    {
        T value;
        Node *next;
        Node *prev;
    };
    Node *newNode(T value, Node *prev);
};

template <typename T>
class cyclicList : public Lists<T>
{
public:
    /*there will be a cyclic list here
     _   |~  _
    [_]--'--[_]
    |'|""`""|'|
    | | /^\ | |
    |_|_|I|_|_|
    */

private:
    void updateCycle(){};
};

#include "lists.cpp"
