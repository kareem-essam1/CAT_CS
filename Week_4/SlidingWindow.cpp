#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int>res;
        int n=nums.size();
        auto x1=nums.begin();
        auto x2=x1+k;
        for(int i=0;i<n-k+1;++i,++x1,++x2)
        {
            res.push_back(*max_element(x1,x2));
        }
        return res;
    }

int main()
{
    int k=1;
    vector<int>nums={1};
    vector<int>res=maxSlidingWindow(nums,k);
    for(auto it:res)
        cout<<it<<" ";
}