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
    LinkedList() {
	}
	LinkedList(const LinkedList&) = delete;
	LinkedList &operator=(const LinkedList &another) = delete;
    void link(Node* first,Node* second)
    {
        if(first)
            first->next=second;
        if(second)
            second->prev=first;

    }
    void embed_after(Node* before,int val)
    {
        Node* item=new Node(val);
        link(item,before->next);
        link(before,item);
        length++;
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
            link(tail,item);
            tail=item;
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
    void insert_sorted(int val)
    {
        if(length==0 || head->data>=val)
            insert_front(val);
        else if(val>=tail->data)
            insert_end(val);
        else
        {
        for(Node* cur = head ; cur ; cur = cur->next)
        {
            if(val<=cur->data)
            {
                embed_after(cur->prev,val);
                verify();
                return;
            }
        }
        }
        
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
        if(!length)
            return;
        else if(head->data==val)
            delete_front();
        else
        {
            for(Node* cur=head;cur; cur=cur->next)
            {
                if(cur->data==val)
                {
                    cur=delete_and_link(cur);
                    if(!cur->next)
                        tail=cur;
                    return;
                }
            }
        }
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
        if(!head)
            return;
        else
        {
        Node* temp=tail;
        tail=tail->prev;
        delete_node(temp);
        }
        if(tail)
            tail->next=nullptr;
        else if(!length)
            head=nullptr;
        verify();  
    }
    Node* delete_and_link(Node* cur)
    {
        Node* ret=cur->prev;
        link(cur->prev,cur->next);
        delete_node(cur);
        verify();
        return ret;
    }
    void delete_front()
    {
        if(!head)
            return;
        else
        {
        Node* temp=head;
        head=head->next;
        delete_node(temp);
        }
        if(head)
            head->prev=nullptr;
        else if(!length)
            tail=nullptr;
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


int main()
{   
    LinkedList list1;
    
}
