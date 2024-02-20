#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        for(int i=0;i<nums.size()-1;++i)
          if(nums.at(i)==nums.at(i+1))
            return true;
        
        return false;
  }

int main()
{ 
  vector<int> myVector = {1, 2, 3, 4, 5};
  cout<<containsDuplicate(myVector);
}