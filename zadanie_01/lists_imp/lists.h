class Lists
{
public:
    Lists(...);
    ~Lists();
    void push_front();
    void push_back();
    void pop_front();
    void pop_back();
    void front();
    void back();

private:
    struct Node
    {
        int value;
        Node *next;
        Node *prev;
    };
    Node head;
    Node tail;
    Node *newNode(int value, Node *prev);
    void deleteNode();
    void initiate();
};

class oneWayList : public Lists
{
public:
    /*there will be a one-way list here
       +
       A_
      /\-\
     _||"|_
    ~^~^~^~^
    */
   
private:
};

class twoWayList : public Lists
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
};

class cyclicList : public Lists
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
};
