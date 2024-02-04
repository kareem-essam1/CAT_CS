#include <iostream>
#include <vector>
#include <cctype>

using namespace std;
int lengthOfLastWord(string s){
    vector<int> vals;
    int temp = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if (!isspace(s[i]))
                temp++;
        else if (temp > 0)
        {
            vals.push_back(temp);
            temp = 0;
        }
    }

    if (temp > 0)
        vals.push_back(temp);

    return vals.back();
    }

int main()
{   
    cout<<lengthOfLastWord("hello world")<<endl;
    cout<<lengthOfLastWord("   fly me   to   the moon  ")<<endl;
    cout<<lengthOfLastWord("luffy is still joyboy")<<endl;
}
