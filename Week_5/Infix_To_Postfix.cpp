#include <iostream>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>

using namespace std;
class Stack{
private:
    struct Node{
        int data {};
        Node* next {};
        Node(int n):data(n){};
    };
    Node* head{};
    
public:
    void push(int val){
        Node* item=new Node(val);
        item->next=head;
        head=item;
        
    }
    int pop(){
        assert(!isEmpty());
        Node* temp=new Node(head->data);
        int element=temp->data;
        head=head->next;
        delete temp;
        return element;
    }
    int peek(){
        assert(!isEmpty());
        return head->data;
    }
    bool isEmpty(){
        return !head;
    }
};
// bool higher(char a,char b){
//     if((a=='*'||a=='/')&&(b=='+'||b=='-'))
//         return true;
//     return false;
// }
// string infixToPostfix(string& line){
//     Stack op;
//     string post="";
//     for(int i=0;i<line.size();++i)
//     {
//         if(isdigit(line[i]))
//             post+=line[i];
//         else
//         {
//             if(op.isEmpty()||higher(line[i],op.peek()))
//                 op.push(line[i]);
//             else
//             {
//                 while(!op.isEmpty()&&!higher(line[i],op.peek()))
//                     post+=op.pop();
//                 op.push(line[i]); 
//             }   
//         }
//     }
//     while(!op.isEmpty())
//         post+=op.pop();
//     return post;
// }

int val(char op){
    if (op == '+' || op == '-')
		return 1;
    if(op =='^')
        return 3;
	if (op == '*' || op == '/') //|| op == '('
		return 2;
	return 0;
}
bool RToL(char a,char b){
    if(a=='^'&&b=='^')
        return true;
    return false;
}
string infixToPostfix(string& line){
    Stack op;
    string post="";
    line+='-';
    op.push('#');
    for(int i=0;i<line.size();++i)
    {
        if(isdigit(line[i])||isalpha(line[i]))
            post+=line[i];
        else if(line[i] == '(')
            op.push(line[i]);
        else if(line[i] == ')')
            {
                while(op.peek()!='(')
                post+=op.pop();
                op.pop();
            }
        else
        {
            while(val(line[i])<=val(op.peek())&&!RToL(line[i],op.peek()))//&&op.peek()!='('
                post+=op.pop();

            op.push(line[i]);
        }
    }
    return post;
}
void eval(Stack &s,char op){
    int sec=s.pop(),first=s.pop();
    switch (op)
    {
    case '-':
        s.push(first-sec);
        break;
    case '+':
        s.push(first+sec);
        break;
    case '*':
        s.push(first*sec);
        break;
    case '/':
        s.push(first/sec);
        break;
    case '^':
        s.push(pow(first,sec));
        break;
    }
}
double evaluate_post(string post){
    Stack nums;
    for(int i=0;i<post.size();++i)
    {
        if(isdigit(post[i]))
            nums.push(post[i] - '0');
        else
        {
            eval(nums,post[i]);
        }
    }
    return nums.pop();
}
int main()
{
    string s="12+3+";
    cout<<evaluate_post(s);
}