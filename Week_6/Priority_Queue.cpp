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
class P_queue{
    private:
    Queue q1,q2,q3;
    int added_elements=0;
    public:
    P_queue(int sz):q1(sz),q2(sz),q3(sz){};
    void Enqueue(int id,int pr){
        if(pr==1)
            q1.Enqueue(id);
        else if(pr==2)
            q2.Enqueue(id);
        else if(pr==3)
            q3.Enqueue(id);
        ++added_elements;
    }
    int Dequeue(){
        assert(!isEmpty());
        --added_elements;
        if(!q3.isEmpty())
            return q3.Dequeue();
        else if(!q2.isEmpty())
            return q2.Dequeue();
        else 
            return q1.Dequeue();
    }
    void Display(){
        cout<<"#3 ";
        q3.display();
        cout<<"#2 ";
        q2.display();
        cout<<"#1 ";
        q1.display();
    }
    bool isEmpty(){
        return added_elements==0;
    }
};
int main()
{
    P_queue tasks (8);
tasks. Enqueue (1131, 1);
tasks. Enqueue (3111, 3);
tasks. Enqueue (2211, 2);
tasks. Enqueue (3161, 3);
tasks. Display ();
}