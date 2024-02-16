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
    if (node->next)
        node->next->prev = node;
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
    Node* get_nth(int n) 
    {
		int cnt = 0;
		for (Node* cur = head; cur; cur = cur->next)
			if (++cnt == n)
				return cur;

		return nullptr;	
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
        if(!cur->prev)
        {
            delete_front();
            return nullptr;
        }
        Node* ret=cur->prev;
        link(cur->prev,cur->next);
        delete_node(cur);
        verify();
        return ret;
    }
    void delete_all_with_key(int val)
    {
        Node* cur=head;
        while(cur)
        {
            if(val==head->data)
            {
                cur=cur->next;
                delete_front();
                continue;
            }
            if(cur->data==val)
            {
               cur=delete_and_link(cur);
            }
            else
            {
                cur=cur->next;
            }
        }
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
    void delete_even_position()
    {
        for(Node* cur=head;cur&&cur->next;cur=cur->next)
        {
            delete_and_link(cur->next);
            if(!cur->next)
            tail=cur;
        }

    }
    void delete_odd_position()
    {   
        //-my solution-
        // Node* cur=head->next;
        // while(cur->next&&cur->next->next)
        // {
        //     delete_and_link(cur->prev);
        //     cur=cur->next->next;
        //     if(cur==tail)
        //         delete_and_link(cur->prev);
        //     else if(cur->next==tail)
        //     {
        //         delete_and_link(cur->prev);
        //         delete_and_link(cur->next);
        //         tail=cur;
        //         tail->next=nullptr;
        //     }
        // }
        insert_front(-1);
        delete_even_position();
        delete_front();
        
        verify();
    }
    int find_middle()
    {
        if(head==nullptr)
            return -1;
        Node* first=head;
        Node* last=tail;
        while(first!=last&&last->prev!=first)
        {
            first=first->next;
            last=last->prev;
        }
        return last->data;
    }
    int s_find_middle()
    {
        if(head==nullptr)
            return -1;
        while(head->next!=tail&&head->next != nullptr)
        {
            delete_front();
            delete_end();
        }
        if(head->next==tail)
        return head->next->data;
        else
        return head->data;
    }
    void swap_with_key(int k)
    {
        int k_back=length-k+1;
        if(k==0||k==1)
            swap_head_tail();
        else if(k>length)
            return;
        else if(k>k_back)
            swap(k,k_back);
        Node* first = get_nth(k);
		Node* second = get_nth(k_back);

        Node* f_next = first->next;
        Node* f_prev = first->prev;
        Node* s_next = second->next;
        Node* s_prev = second->prev;
        if(k+1==k_back)
        {
            link(first,s_next);
            link(f_prev,second);
            link(second,first);
        }
        else
        {
            link(first,s_next);
            link(f_prev,second);
            link(second,f_next);
            link(s_prev,first);
        }
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
    bool is_palindrome()
    {
        Node* first=head;
        Node* last=tail;
        bool is=1;
        while(is&&first!=last)
        {
            if(first->data==last->data)
            {
                first=first->next;
                last=last->prev;
            }
            else
            {
                is=0;
            }
        }
        return is;
    }
    void merge_2sorted_lists(LinkedList &other)
    {
        if(other.length==0)
            return;
        else if(length==0)
            {head=other.head; tail=other.tail; length=other.length;}
        else
        {
            Node* cur2=other.head;
        while(cur2)
        {
            insert_sorted(cur2->data);
            print();
            cur2=cur2->next;
        }
        }
        
    }
    void reverse()
    {
        for(Node* cur=head;cur;cur=cur->prev)
        {
            swap(cur->next,cur->prev);
        }
        swap(head,tail);
        head->prev=nullptr;
        tail->next=nullptr;
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
    LinkedList list2;

    list1.insert_end(10);
    list1.insert_end(20);
    list1.insert_end(30);
    list1.insert_end(40);
    list1.insert_end(50);

    list2.insert_end(15);
    list2.insert_end(17);
    list2.insert_end(22);
    list2.insert_end(24);
    list2.insert_end(35);

    list1.merge_2sorted_lists(list2);
    list1.print();
}
