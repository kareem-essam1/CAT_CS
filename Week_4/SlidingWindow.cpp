#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int>res;
        deque<int>max;
        int n=nums.size();
        for(int i=0;i<k;++i)
        {
            if(max.empty()||nums[i]>max.back())
                max.push_back(nums[i]);
        }
        res.emplace_back(max.back());
        for(int i=k;i<n;++i)
        {
            if(max.front() == nums[i - k])//if number out of window
                max.pop_front();
            if(max.empty())
                max.push_back(nums[i]);
                
            if(nums[i]>max.back())
            {
                max.push_back(nums[i]);
                max.pop_front();
            }
            res.emplace_back(max.back());
        }
        return res;
    }

int main()
{
    int k=2;
    vector<int>nums={7,2,4};
    vector<int>res=maxSlidingWindow(nums,k);
    for(auto it:res)
        cout<<it<<" ";
}