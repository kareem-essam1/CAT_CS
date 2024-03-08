#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

class LinkedList
{
    private:
    struct Node{
    int data {};
    Node* next {};
    Node(int d):data(d){}
    ~Node() {}
    };
        Node* head =nullptr;
        Node* tail =nullptr;
        int length=0;
    public:
    LinkedList() {
	}
	LinkedList(const LinkedList&) = delete;
	LinkedList &operator=(const LinkedList &another) = delete;
    void print()
    {
        Node* temp_h=head;
        while(temp_h != nullptr)
        {
            cout<<temp_h->data<<" ";
            temp_h=temp_h->next;
        }
        cout<<"\n";
    }
    void insert_end(int val)
    {
        Node* item = new Node(val);
        if(head==nullptr)
            head = tail = item;  
        else
        {
            tail->next=item;
            tail = item;
        }
        length++;
        verify();
    }
    int delete_front()
    {
        int val=-1;
        if(!head)
            return val;
        else
        {
        Node* temp=head;
        head=head->next;
        val=temp->data;
        delete temp;
        length--;
        }
        verify();
        return val;
    }
    int size(){
        return length;
    }
    void verify()
    {
        if(length==0)
            assert(head == nullptr && tail == nullptr);
        else
        {
            assert(head!=nullptr && tail != nullptr);
        if(length==1)
        assert(head == tail);
        else
         {
            int ctr=0;
            for (Node* cur=head;cur;cur=cur->next,ctr++);
            assert(ctr==length);
         }
        } 
    }
    ~LinkedList() 
    {
        for(Node* cur = head ; cur ;)
        {
            Node* next=cur->next;
            delete cur;
            cur=next;
        }
        length=0;
        head=tail=nullptr;
	}
};
class Queue{
private:
    LinkedList list;
public:
    void Enqueue(int val){
        list.insert_end(val);
    }
    int Dequeue(){
       return list.delete_front();
    }
    void display(){
        list.print();
    }
    bool isEmpty(){
        return list.size()==0;
    }
};

int main()
{
    Queue s;
    s.Enqueue(1);
    s.Enqueue(2);
    s.Enqueue(3);
    s.Enqueue(4);
    s.Enqueue(5);
    s.Enqueue(6);
    s.display();

}