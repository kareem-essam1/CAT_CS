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

int main()
{
    Queue s(7);
    s.Enqueue(1);
    s.Enqueue(2);
    s.Enqueue(3);
    s.Enqueue(4);
    s.Enqueue(5);
    s.Enqueue(6);
    s.display();

}