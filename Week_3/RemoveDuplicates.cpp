#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

struct Node
{
    int data {};
    Node* next {};
    Node* prev {};
    Node(int d):data(d){}
    ~Node() {}
};
class LinkedList
{
    private:
        Node* head =nullptr;
        Node* tail =nullptr;
        int length=0;
        vector<Node*> debug_data;	// add/remove nodes you use

	public:
    LinkedList() {}
	LinkedList(const LinkedList&) = delete;
	LinkedList &operator=(const LinkedList &another) = delete;
    void debug_print_address() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur << "," << cur->data << "\n";
		cout << "\n";
	}
    void link(Node* first,Node* second)
    {
        if(first)
            first->next=second;
        if(second)
            second->prev=first;

    }
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
            link(tail,item);
            tail=item;
            tail->next=nullptr;
        }
        length++;
        verify();
    }
    void insert_front(int val)
    {
        Node* item = new Node(val);
        if(head==nullptr)
            head = tail = item;
        else
        {
            link(item,head);
            head=item;
        }
        length++;
        verify();
    }
    void remove_duplicates()
    {
        for(Node* cur=head;cur&&cur->next;)
        {
            if(cur->data==cur->next->data)
            {
                Node* temp=cur->next;
                link(cur,cur->next->next);
                delete temp;
                length--;
            }
            else
            cur=cur->next;
        }
        verify();
    }
    string out_string()
    {
        if (length == 0)
			return "";
        ostringstream res;
        for(Node* cur=head;cur;cur=cur->next)
        {
            res << cur->data;
            if(cur->next)
            res<<" ";
        }
        return res.str();
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
int main()
{   
    LinkedList list1;

    list1.insert_end(10);
    list1.insert_end(10);
    list1.insert_end(20);
    list1.insert_end(30);
    list1.insert_end(30);
    list1.insert_end(40);
    list1.insert_end(50);
    list1.insert_end(50);

    list1.remove_duplicates();
    list1.print();
}
