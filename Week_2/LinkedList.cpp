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
        vector<Node*> debug_data;	// add/remove nodes you use

	void debug_add_node(Node* node) {
		debug_data.push_back(node);
	}
	void debug_remove_node(Node* node) {
		auto it = find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}
    public:
    LinkedList() {
	}
	LinkedList(const LinkedList&) = delete;
	LinkedList &operator=(const LinkedList &another) = delete;
    void debug_print_address() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur << "," << cur->data << "\n";
		cout << "\n";
	}
	void debug_print_node(Node* node, bool is_seperate = false) {
		if (is_seperate)
			cout << "Sep: ";
		if (node == nullptr) {
			cout << "nullptr\n";
			return;
		}
		cout << node->data << " ";
		if (node->next == nullptr)
			cout << "X ";
		else
			cout << node->next->data << " ";

		if (node == head)
			cout << "head\n";
		else if (node == tail)
			cout << "tail\n";
		else
			cout << "\n";
	}
	void debug_print_list(string msg = "") {
		if (msg != "")
			cout << msg << "\n";
		for (int i = 0; i < (int) debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		cout << "************\n"<<flush;
	}
    void delete_node(Node* node) 
    {
		--length;
		delete node;
	}
    void delete_next_node(Node* node) 
    {
		assert(node);

		Node* to_delete = node->next;
		bool is_tail = to_delete == tail;
		node->next = node->next->next;
		delete_node(to_delete);
		if (is_tail)
			tail = node;
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
            tail->next=item;
            tail = item;
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
            item->next=head;
            head=item;
        }
        length++;
        verify();
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
    Node* get_nth_back(int id)
    {
        assert(id<length);
        if(id==0)
            return head;
        int ctr=0;
        get_nth(length-id+1);
        verify();
    }
    int search(int val)
    {
        int ctr=0;
        for(Node* cur=head;cur; cur=cur->next ,ctr++)
        {
            if(cur->data==val)
                return ctr;
        }
        return -1;
    }
    int search_im(int val)
    {
        int ctr=0;
        Node* prev=nullptr;
        for(Node* cur=head;cur;cur=cur->next,ctr++)
        {
            if(cur->data==val)
               {
                if(!prev)
                {
                  return ctr;  
                }
                swap(cur->data,prev->data);
                return ctr-1;
               } 
            prev = cur;
        }
        return -1;
    }
    void delete_with_key(int val)
    {
        int ctr=0;
        for(Node* cur = head ; cur ; cur = cur->next,ctr++)
        {
            if(cur->data==val)
            {
            delete_nth(ctr);
            return;  
            }
        }
        return;
    }
    void delete_nth(int id)
    {
        //cout<<id<<"\n";
        assert(id<length);
        if(id==0)
        {
            delete_front();
            return;
        }
        else if(id==length-1)
        {
            delete_end();
            return;
        } 
        else
        {
                int ctr=0;
                Node* prev=nullptr;
            for(Node* cur=head;cur&&ctr<=id;cur=cur->next,ctr++)
            {
                if(ctr==id)
                {
                    prev->next=prev->next->next;
                    delete cur;
                    break;
                }
                prev = cur;
            } 
        }
        if(!head)
            tail=nullptr;
        length--;
        verify();
    }
    void delete_end()
    {
        if(length<=1)
        {
            delete_front();
            return;
        }
        Node* prev=get_nth(length-2);
        delete tail;
        tail=prev;
        tail->next=nullptr;
        length--;
        verify();  
    }
    void delete_front()
    {
        if(!head)
            return;
        else
        {
        Node* temp=head;
        head=head->next;
        delete temp;
        length--;
        }
        verify();
        
    }
    bool is_same(const LinkedList &slist)
    {
        if(length!=slist.length)
        return false;

        Node* cur=head;
        Node* sec=slist.head;
        
        while(cur && sec)
        {
            if(cur->data!=sec->data)
            return false;
            cur=cur->next;
            sec=sec->next;
        }
        return true;
    }
    void swap_pairs()
    {
        for(Node* cur=head;cur;cur=cur->next->next)
            {
                if(!cur->next)
                return;
                swap(cur->data,cur->next->data);
            }  
        verify();
    }
    void swap_head_tail()
    {
        if(!head || length==1)
            return;
        Node* first=head;
        Node* last=tail;
        last->next=head->next;
        get_nth(length-2)->next=first;
        tail=first;
        tail->next=nullptr;
        head=last;
        verify();
    }
    void insert_sorted(int val)
    {
        if(!head)
        {
            insert_end(val);
            return;
        }
        Node* prev=nullptr;
        Node* item=new Node(val);
        for(Node* cur = head ; cur ; cur = cur->next)
        {
            if(val<=cur->data)
            {
                if(cur==head)
                {
                    insert_front(val);
                    return;
                }
                prev->next=item;
                item->next=cur;
                length++;
                verify();
                return;
            }
            if(cur==tail)
            {
                insert_end(val);
                return;
            }
            prev=cur;
        }
    }
    void rotate_left(int steps)
    {
        steps%=length;
        tail->next=head;
        head=get_nth(steps);
        for(Node* cur=head;cur;cur=cur->next)
            {
                if(cur->next==head)
                {
                    tail=cur;
                    tail->next=nullptr;
                    break;
                }
            } 
        verify();
    }
    void remove_duplicates()
    {
        for(Node* cur = head ; cur ; cur = cur->next)
        {
           for(Node* cur2 = cur->next,*prev=cur; cur2 ;)
        {
            if(cur->data==cur2->data)
            {
                delete_next_node(prev);
                cur2=prev->next;
            }
            else
            {
                prev=cur2;cur2=cur2->next;
            }
        } 
        }
        verify();
    }
    void remove_last(int val)
    {
        int ctr=0;
        int last=-1;
        for(Node* cur=head;cur;cur=cur->next,ctr++)
            {
                if(cur->data==val)
                    last=ctr;
            }
            if(last!=-1)
            delete_nth(last);

    }
    void push_to_end(int val)
    {
        Node* prev=nullptr;
        for(Node* cur=head;cur;cur=cur->next)
            {
                if(cur->data==val)
                {
                    if(!prev)
                        head=cur->next;
                    else
                        prev->next=cur->next;
                    
                    tail=cur;
                    tail->next=nullptr;
                }
                prev=cur;
            }
            verify();
    }
    int Max(Node* cur)
    {
        int max=0;
        if(max<cur->data)
        {
            max=cur->data;
        }
        max=Max(cur->next);
        if(cur==tail)
        return max;
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

void print1(Node* head)
{
    while(head != nullptr)
    {
        cout<<head->data<<"\n";
        head=head->next;
    }
}
void print2(Node* head)
{
    //recusive printing
    if(head != nullptr)
    {
        cout<<head->data<<"\n";
        print2(head->next);
    }
}
void print3(Node* head)
{
    //reverse printing
    if(head != nullptr)
    {
        print3(head->next);
        cout<<head->data<<"\n";
    }
}

int main()
{   
    LinkedList list1;
    LinkedList list2;
    list1.insert_end(1);
    list1.insert_end(4);
    list1.insert_end(3);
    list1.insert_end(1);
    list1.insert_end(2);
    list1.insert_end(4);
    list1.insert_end(1);
    list1.insert_end(7);
    list1.insert_end(1);
    list1.insert_end(8);
    list1.insert_end(1);
    list1.push_to_end(1);
    list1.print();
}
