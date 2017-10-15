#pragma once
#include "stdafx.h"

class Solution1 {
public:
	vector<int> twoSum(vector<int>& numbers, int target) {

		int begin = 0, end = numbers.size() - 1;
		vector<int> res = { 0,0 };
		int sum = numbers[begin] + numbers[end];
		while (sum != target) {
			sum = numbers[begin] + numbers[end];
			if (sum > target) {
				if (numbers[begin + 1] <= numbers[begin]) {
					++begin;
					continue;
				}
				else if (numbers[end - 1] <= numbers[end]) {
					--end;
					continue;
				}
			}
			else if (sum < target) {
				if (numbers[begin + 1] >= numbers[begin]) {
					++begin;
					continue;
				}
				else if (numbers[end - 1] >= numbers[end]) {
					--end;
					continue;
				}
			}
			else break;
		}
		if (begin == end) {
			if (begin != 0 && numbers[begin] == numbers[begin - 1]) --begin;
			else if (numbers[begin] == numbers[begin + 1]) ++begin;
			else if (numbers[end] == numbers[end - 1]) --end;
			else if (numbers[end] == numbers[end + 1]) ++end;
		}
		res[0] = begin + 1;
		res[1] = end + 1;
		return res;
/*		int begin = 0, end = nums.size();
		vector<int> res = { 0,0 };
		int sum = 0;
		for (; begin < end - 1; ++begin) {
			for (int i = begin + 1; i < end; i++)
			{
				sum = nums[begin] + nums[i];
				if (sum == target) {
					res[0] = begin;
					res[1] = i;
					return res;
				}
			}
		}*/
	}
};