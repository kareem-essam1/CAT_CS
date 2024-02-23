#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;
bool isValid(string s) {
    stack<char>cur;
    cur.push('a');
    int ctr=0;
        for(auto it: s)
        {
            switch (it)
            {
            case ')':
                if(cur.top()=='(')
                {cur.pop();
                ctr--;}
                else
                return false;
                break;
            case ']':
                if(cur.top()=='[')
                {cur.pop();
                ctr--;}
                else
                return false;
                break;
            case '}':
                if(cur.top()=='{')
                {cur.pop();
                ctr--;}
                else
                return false;
                break;
            
            default:
            cur.push(it);
            ctr++;
                break;
            }
        }
        if(ctr==0)
        return true;
        else
        return false;
    }

int main()
{ 
  string s="{}";
  cout<<isValid(s);
}