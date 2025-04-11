#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int64_t ret = 0, l = 0, r = height.size() - 1;
        while (l < r) {
            ret = max<int64_t>(ret, (r - l) * min(height[l], height[r]));
            if (height[l] < height[r]) l ++;
            else r --;
        }
        return ret;
    }
};