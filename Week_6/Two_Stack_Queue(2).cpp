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
class Queue{
    private:
    int size;
    int added_elements=0;
    Stack s1;
    Stack s2;
    public:
    Queue(int n):size(n){};
    void move(Stack &s1,Stack &s2){
        while(!s1.isEmpty())
            s2.push(s1.pop());
    }
    void Enqueue(int val){
        s1.push(val);
        added_elements++;
    }
    int Dequeue(){
        move(s1,s2);
        int val=s2.pop();
        move(s2,s1);
        --added_elements;
        return val;
    }
    bool isEmpty(){
        return added_elements==0;
    }
};
int main()
{
    Queue qu(6);
    for (int i = 1; i <= 3; ++i)
        qu.Enqueue(i);
    cout<<qu.Dequeue()<<"\n";
    while(!qu.isEmpty())
        cout<<qu.Dequeue()<<" ";
}