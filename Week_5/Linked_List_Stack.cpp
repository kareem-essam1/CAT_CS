#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;
class Stack{
private:
    struct Node{
        int data {};
        Node* next {};
        Node(int n):data(n){};
    };
    Node* head{};
    
public:
    void push(int val){
        Node* item=new Node(val);
        item->next=head;
        head=item;
        
    }
    int pop(){
        assert(!isEmpty());
        Node* temp=new Node(head->data);
        int element=temp->data;
        head=head->next;
        delete temp;
        return element;
    }
    int peek(){
        assert(!isEmpty());
        return head->data;
    }
    bool isEmpty(){
        return !head;
    }

};

int main()
{
    
}