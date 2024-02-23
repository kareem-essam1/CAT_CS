#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;
vector<int> productExceptSelf(vector<int>& nums) {
      int n=nums.size();
      vector<int> res(n,1);
      int right=1,left=1;
      for(int i=0;i<n;++i)
      {
        res[i]=left;
        left*=nums[i];
      }
      for(int i=n-1;i>=0;--i)
      {
        res[i]*=right;
        right*=nums[i];
      }

      return res;
    }

int main()
{ 
  vector<int>nums = {0,0};
  vector<int>res=productExceptSelf(nums);
  for(auto it:res)
    cout<<it<<" ";
}