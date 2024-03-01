#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;
class Stack{
private:
    int size;
    int* arr=nullptr;
    int top=-1;
    
public:
    Stack(int n):size(n){arr=new int[size]{};}
    void push(int num){
        assert(!isFull());
        arr[++top]=num;
    }
    int len(){
        return top;
    }
    int pop(){
        assert(!isEmpty());
        return arr[top--];
    }
    int peek(){
        assert(!isEmpty());
        return arr[top];
    }
    void display(){
        for(int i=top;i>=0;--i)
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
    string out_string(){
        string out="";
        for(int i=top;i>=0;--i)
            out+=arr[i];
        return out;
    }

    ~Stack(){delete[] arr;}
};

int main()
{
    Stack stk(3);
    stk.push(10);
    stk.push(20);
    stk.push(30);
    cout<<stk.isFull()<<"\n";
    cout<<stk.peek()<<"\n";
    stk.pop();
    cout<<stk.isFull()<<"\n";
    stk.display();
}