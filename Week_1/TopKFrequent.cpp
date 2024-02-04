#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> topKFrequent(vector<int>& nums, int k) 
{
    vector<int> res;
    int max = *max_element(nums.begin(), nums.end()) + 1;
    vector<int> f(max, 0);

    for (int i : nums)
        f[i]++;
    
    vector<pair<int, int>> freq;

    for (int i = 0; i < max; i++) {
        if (f[i] > 0) {
            freq.push_back({f[i], i});
        }
    }

    sort(freq.rbegin(), freq.rend());
    for (int i = 0; i < k ; ++i)
        res.push_back(freq[i].second);

    return res;
}

int main()
{   
    vector<int> test {1,1};
    vector<int> result = topKFrequent(test, 1);
    for (int i : result)
    {
        cout<<i<<" ";
    }


    return 0;
}
