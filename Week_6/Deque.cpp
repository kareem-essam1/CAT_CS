#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;
struct Node
{
    int data {};
    Node* next {};
    Node(int d):data(d){}
    ~Node() {
	//cout<<"Destroy value: "<<data<<" at address "<<this<<"\n";
	}
};
class LinkedList
{
    private:
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
    int delete_end()
    {
        int val=tail->data;
        if(length<=1)
        {
           return delete_front();
        }
        Node* prev=get_nth(length-2);
        delete tail;
        tail=prev;
        tail->next=nullptr;
        length--;
        verify();
        return val;
    }
    Node* get_nth(int id)
    {
        int ctr=0;
        for(Node* cur = head ; cur ; cur = cur->next,ctr++)
        {
            if(ctr==id)
            return cur;
        }
        return nullptr;
    }
    void insert_front(int val)
    {
        Node* item = new Node(val);
        if(head==nullptr)
            head = tail = item;
        else
        {
            item->next=head;
            head=item;
        }
        length++;
        verify();
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
    void Enqueue_rear(int val){
        list.insert_end(val);
    }
    void Enqueue_front(int val){
        list.insert_front(val);
    }
    int Dequeue_rear(){
       return list.delete_end();
    }
    int Dequeue_front(){
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
    s.Enqueue_rear(10);
    s.Enqueue_rear(20);
    s.Enqueue_front(30);
    s.Enqueue_front(40);
    s.display();
    cout<<s.Dequeue_front()<<"  "<<s.Dequeue_rear();

}