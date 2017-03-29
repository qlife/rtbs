#include<cstdio>
#include<climits>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
	// Make the list sorted.
	std::sort(nums.begin(), nums.end());
	int current_closet_sum = 0;
	int min_diff = INT_MAX;

	// Two pointers trick
	for(int i = 0; i < nums.size()-1; ++i) {
	    int start, end, sum;
	    start = i+1;
	    end = nums.size() - 1;

	    while(start<end) {
		sum = nums[i] + nums[start] + nums[end];
		cout << nums[i] << " " << nums[start] << " " << nums[end] << endl;
		if(sum == target) {
		    min_diff = 0;
		    current_closet_sum = sum;
		    return current_closet_sum;
		} else if(sum < target) {
		    int temp = target - sum;
		    if(temp < min_diff) {
			min_diff = temp;
			current_closet_sum = sum;
		    }
		    start ++;
		} else {
		    // assert sum > target
		    int temp = sum - target;
		    if(temp < min_diff) {
			min_diff = temp;
			current_closet_sum = sum;
		    }
		    end --;
		}
	    }
	}
	return current_closet_sum;
    }
};

int main()
{
//    int n[6] = { 1, 2, 3, 4, 5, -7 };
    std::vector<int> nums({1,2,3,4,5,-7});
    int target = 2;
    Solution sol;
    std::cout << sol.threeSumClosest(nums, target) << std::endl;
}
