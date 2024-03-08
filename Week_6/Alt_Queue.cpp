#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;
class Queue{
private:
    int size;
    int front {0};
    int rear {0};
    int* arr=nullptr;
    
public:
    Queue(int size):size(size+1){arr=new int[size]{};};
    int next(int pos){
        ++pos;
        if(pos==size)
            return 0;
        return pos;
    }
    bool isFull(){
        return next(rear)==front;
    }
    bool isEmpty(){
        return front==rear;
    }
    void Enqueue(int val){
        assert(!isFull());
        arr[rear]=val;
        rear=next(rear);
    }
    int Dequeue(){
        assert(!isEmpty());
        int val=arr[front];
        front=next(front);
        return val;
    }
    void display(){
        if(isFull())
            cout<<"full"<<"\n";
        else  if(isEmpty()){
            cout<<"empty"<<"\n";
            return;
        }
        for (int cur = front;cur!=rear;cur=next(cur))
        {
            cout<<arr[cur]<<" ";
        }
        cout<<"\n";
    }

    
};

int main()
{
    Queue s(5);
    s.Enqueue(1);
    s.Enqueue(2);
    s.Enqueue(3);
    s.Enqueue(4);
    s.Enqueue(5);
    cout<<s.Dequeue()<<" "<<s.Dequeue()<<"\n";
    s.display();
}