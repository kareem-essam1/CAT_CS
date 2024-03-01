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
string reverse_subwords(string line){
    line+=' ';
    string res;
    Stack s(line.size());
    for(int i=0;i<line.size();++i)
    {
        if(line[i]==' ')
        {
            while(!s.isEmpty())
                res+=s.pop();
            res+=' ';
        }
        else
            s.push(line[i]);
    }
    return res;
}
int reverse_number(int num){
    Stack s(20);
    while(num)
    {
        s.push(num%10);
        num/=10;
    }
    int tens=1;
    while(!s.isEmpty())
    {
        num+=s.pop()*tens;
        tens*=10;
    }
    return num;
}
char get_match(char ch){
    if(ch==')')
        return '(';
    else if(ch=='}')
        return '{';
    return '[';
}
bool isValid(string line){
    Stack s(line.size());
    for(int i=0;i<line.size();i++)
    {
        if(line[i]=='('||line[i]=='{'||line[i]=='[')
            s.push(line[i]);
        else if(s.isEmpty()||s.pop()!=get_match(line[i]))
            return false;
    }
    return s.isEmpty();
}
string remove_duplicates(string line){
    Stack s(line.size());
    string res="";
    for(int i=line.size()-1;i>=0;i--)
    {
        if(s.isEmpty()||line[i]!=s.peek())
            s.push(line[i]);
        else
            s.pop();
    }
    return s.out_string();
}
int main()
{ 
    string line="addcaacab";
    cout<<remove_duplicates(line)<<"\n";
}