#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;
class Queue{
private:
    int size;
    int front {0};
    int rear {0};
    int added_elements {0};
    int* arr=nullptr;
    
public:
    Queue(int size):size(size){arr=new int[size]{};};
    int next(int pos){
        ++pos;
        if(pos==size)
            return 0;
        return pos;
    }
    int prev(int pos){
        --pos;
        if(pos==-1)
            pos=size-1;
        return pos;
    }
    bool isFull(){
        return added_elements==size;
    }
    bool isEmpty(){
        return added_elements==0;
    }
    void Enqueue(int val){
        assert(!isFull());
        arr[rear]=val;
        rear=next(rear);
        added_elements++;
    }
    int Dequeue(){
        assert(!isEmpty());
        int val=arr[front];
        front=next(front);
        added_elements--;
        return val;
    }
    int Dequeue_t(){
        assert(!isEmpty());
        int val=arr[rear-1];
        rear=prev(rear);
        added_elements--;
        return val;
    }
    int front_val(){
        return arr[front];
    }
    void display(){
        if(isFull())
            cout<<"full"<<"\n";
        else  if(isEmpty()){
            cout<<"empty"<<"\n";
            return;
        }
        for (int cur = front,step=0; cur < added_elements;)
        {
            cout<<arr[cur]<<" ";
            cur=next(cur);
            step++;
        }
        cout<<"\n";
    }
};

class Stack{
private:
    Queue q;
    int added_elements=0;
public:
    Stack(int n):q(n){};
    void push(int val){
        int s=added_elements;
        q.Enqueue(val);
        while(s--)
            q.Enqueue(q.Dequeue());
        added_elements++;
    }
    int pop(){
        added_elements--;
        return q.Dequeue();
    }
    int peek(){
        return q.front_val();
    }
    bool isEmpty(){
        return added_elements==0;
    }
};

int main()
{
    Stack s(7);
    cout<<s.isEmpty()<<"\n";
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    cout<<s.pop()<<"\n";
    cout<<s.peek()<<"\n";
}