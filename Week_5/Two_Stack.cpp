#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;
class Stack{
private:
    int size;
    int* arr=nullptr;
    int top=-1;
    int back=size;
    
public:
    Stack(int n):size(n){arr=new int[size]{};}
    void push(int id,int num){
        assert(!isFull());
        if(id==1)
        arr[++top]=num;
        else
        arr[--back]=num;
    }
    int pop(int id){
        assert(!isEmpty());
        if(id==1)
        return arr[top--];
        else
        return arr[back++];
    }
    int peek(int id){
        assert(!isEmpty());
        if(id==1)
        return arr[top];
        else
        return arr[back];
    }
    void display(){
        for(int i=top;i>=0;--i)
            cout<<arr[i]<<" ";
        cout<<"\n";
        for(int i=back;i<size;++i)
            cout<<arr[i]<<" ";
        cout<<"\n";
    }
    bool isFull(){
        if(top==size-1)
            return true;
        return false;
    }
    bool isEmpty(){
        if(top==-1)
            return true;
        return false;
    }

    ~Stack(){delete[] arr;}
};

int main()
{
    Stack s(10);
    s.push(1,10);
    s.push(1,20);
    s.push(2,5);
    s.push(2,7);
    s.display();
    s.pop(1);
    s.pop(2);
    s.peek(1);
    s.peek(2);
    s.display();
}