#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;
int strStr(string haystack, string needle) {
        if(needle.size()>haystack.size())
          return -1;
        for(int i=0;i<haystack.size();++i)
        {
          if (haystack.substr(i,needle.size())==needle)
            return i;
        }
        return-1;
    }

int main()
{ 
  string s="a";
  string s2="a";
  cout<<strStr(s,s2);
}