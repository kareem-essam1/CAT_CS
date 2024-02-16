#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;
struct Node
{
    string data="";
    Node* next {};
    Node* prev {};
    Node(string d):data(d){}
    ~Node() {}
};
class BrowserHistory {

private:
    Node* head=nullptr;
    Node* tail=nullptr;
    Node* cur =nullptr;
public:
    BrowserHistory(string homepage) {
        head=new Node(homepage);
        tail=head;
        tail->next=nullptr;
        head->prev=nullptr;
        cur=tail;
    }
    
    void visit(string url) {
        Node* item=new Node(url);
        cur->next=item;
        item->prev=cur;
        tail=item;
        tail->next=nullptr;
        cur=cur->next;
    }
    
    string back(int steps) {
        while(steps--&& cur->prev)
        {
            cur=cur->prev;
        }
        return cur->data;
    }
    
    string forward(int steps) {
        while(steps--&& cur->next)
        {
            cur=cur->next;
        }
        return cur->data;
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */
int main()
{   
    BrowserHistory* obj = new BrowserHistory("leetcode.com");
    obj->visit("url1");
    obj->visit("url2");
    obj->visit("url3");
    cout<<obj->back(1)<<"\n";
    cout<<obj->back(1)<<"\n";
    cout<<obj->forward(1)<<"\n";
    obj->visit("url4");
    cout<<obj->forward(2)<<"\n";
    cout<<obj->back(2)<<"\n";
    cout<<obj->back(7)<<"\n";
}