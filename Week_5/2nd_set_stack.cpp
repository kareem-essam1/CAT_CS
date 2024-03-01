#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>

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

    // other way
    // void insert_bottom(int x,int i=-1){
    //     if(isFull())
    //         return;
    //     else if(i==top+1)
    //     {
    //         top++;
    //         return;
    //     }
    //     int temp=arr[i+1];
    //     arr[i+1]=x;
    //     insert_bottom(temp,++i);
    // }

    void insert_bottom(int x){
        if(isEmpty())
            push(x);
        else
        {
            int cur=pop();
            insert_bottom(x);
            push(cur);
        }
    }
    void reverse(){
        if(isEmpty())
            return;
        int cur=pop();
        reverse();
        insert_bottom(cur);
    }
    ~Stack(){delete[] arr;}
};
vector<int> astroid_collision(vector<int> r){
    Stack s(r.size());
    vector<int> res;
    for(int i=0;i<r.size();)
    {
        if(r[i]<0&&!s.isEmpty()&&s.peek()>0)
        {
            if(-r[i]==s.peek())
            {
                s.pop(); ++i; 
            }
            else if(-r[i]>s.peek())
                s.pop();
            else ++i;
        }
        else
        s.push(r[i]); ++i;
    }
    while(!s.isEmpty())
        res.insert(res.begin(),s.pop());
    return res;
}
int score(string line){
    Stack s(line.size());
    s.push(0);
    for(int i=0;i<line.size();++i)
    {
        if(line[i]=='(')
            s.push(0);
        else
        {
            int last=s.pop();
            if(last==0)
                last=1;
            else
                last*=2;
            
            s.push(last+s.pop());
        }
    }
    return s.peek();
    }
void next_greater(vector<int>& v){
    Stack s(v.size());
    for(int i=0;i<v.size();i++)
    {
        while(!s.isEmpty()&&v[i]>v[s.peek()])
            v[s.pop()]=v[i];
        s.push(i);
    }
    while(!s.isEmpty())
        v[s.pop()]=-1;
}
int main()
{
    vector<int> r={1,5,3,6};
    next_greater(r);
    for (auto it:r)
        cout<<it<<" ";
}