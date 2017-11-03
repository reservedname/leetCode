#pragma once
#include "stdafx.h"

/**
 *
 * Given an array with n integers, your task is to check 
 * if it could become non-decreasing by modifying at most 1 element.
 * We define an array is non-decreasing if array[i] <= array[i + 1] holds for every i (1 <= i < n).
 *
 * Example 1:
 * Input: [4,2,3]
 * Output: True
 * Explanation: You could modify the first
 *	4
 *	to
 *	1
 * to get a non-decreasing array.
 *
 * Example 2:
 * Input: [4,2,1]
 * Output: False
 * Explanation: You can't get a non-decreasing array by modify at most one element.
 *
 */
class Solution21 {
public:
	// 我这里用的是这个推论：修改的那个值最小为与它相邻的前一个值或后一个值，开始没考虑有两种情况，
	// 所以"2 3 3 2 4"这种情况过不了。这里还用了一个小技巧，就是设flag为2，每满足一种情况则减一，如果有任何一种
	// 情况没满足则flag为真，避免了复杂的逻辑运算
	bool checkPossibility(vector<int>& nums) {
		int flag = 2;
		if (nums.size() <= 2) return true;
		for (auto i = nums.begin() + 1; i < nums.end(); i++)
		{
			if (*i < *(i - 1)) {
				if (i + 1 == nums.end()) return true;
				int pre = *(i - 1), rer = *(i + 1);
				*(i - 1) = *i;
				for (auto j = nums.begin() + 1; j < nums.end(); j++)
				{
					if (*j < *(j - 1)) {
						--flag;
						break;
					}
				}
				*(i - 1) = pre;
				*i = pre;
				for (auto j = nums.begin() + 1; j < nums.end(); j++)
				{
					if (*j < *(j - 1)) {
						--flag;
						break;
					}
				}
				if (!flag) return false;
				return true;
			}
		}
		return true;
	}
};

/*
struct String {
	char s[1024];
	int lenth;
	char *head;
};

void cacu_chr_num(String* inputStr) {
	String* str = inputStr;
	int chr[256] = { 0 };
	char priorChr = 0;
	for (int i = 0; i < str->lenth; i++)
	{
		chr[str->s[i]]++;
	}
	int sum = 0;

	for (int i = 0; i < 256; i++)
	{
		if (chr[i] != 0) {
			sum++;
			cout << (char)i << ": " << chr[i] << endl;
		}
	}
	cout << "一共有" << sum << "个不同的单词" << endl;
}*/

/**
 *
 * The set S originally contains numbers from 1 to n. But unfortunately, due to the data error,
 * one of the numbers in the set got duplicated to another number in the set, 
 * which results in repetition of one number and loss of another number.
 *
 * Given an array nums representing the data status of this set after the error. 
 * Your task is to firstly find the number occurs twice and then find the number that is missing. 
 * Return them in the form of an array.
 *
 * Example 1:
 * Input: nums = [1,2,2,4]
 * Output: [2,3]
 * Note:
 * The given array size will in the range [2, 10000].
 * The given array's numbers won't have any order.
 *
 */
class Solution22 {
public:
	vector<int> findErrorNums(vector<int>& nums) {
		int allNum[10001] = { 0 };
		vector<int> res = { 0,0 };
		int n = nums.size();

		for (auto i = nums.begin(); i != nums.end(); i++)
		{
			allNum[*i]++;
		}
		for (int i = 1; i <= n; i++)
		{
			if (allNum[i] == 2) res[0] = i;
			else if (allNum[i] == 0) res[1] = i;
		}
		return res;
	}
};

/**
 *
 * Suppose you have a long flowerbed in which some of the plots are planted and some are not.
 * However, flowers cannot be planted in adjacent plots - they would compete for water and both would die.
 *
 * Given a flowerbed (represented as an array containing 0 and 1, 
 * where 0 means empty and 1 means not empty), and a number n, 
 * return if n new flowers can be planted in it without violating the no-adjacent-flowers rule.
 *
 * Example 1:
 * Input: flowerbed = [1,0,0,0,1], n = 1
 * Output: True
 * Example 2:
 * Input: flowerbed = [1,0,0,0,1], n = 2
 * Output: False
 * Note:
 * The input array won't violate no-adjacent-flowers rule.
 * The input array size is in the range of [1, 20000].
 * n is a non-negative integer which won't exceed the input array size.
 *
 */
class Solution23 {
public:
	bool canPlaceFlowers(vector<int>& flowerbed, int n) {
		int len = flowerbed.size();
		int hasPlaced = 0;

		for (int i = 0; i < len && hasPlaced < n; i++)
		{
			if (flowerbed[i] == 0) {
				if (i == 0 && flowerbed[i + 1] != 1) {
					flowerbed[i] = 1;
					++hasPlaced;					
				}
				else if (i == len - 1 && flowerbed[i - 1] != 1) {
					flowerbed[i] = 1;
					++hasPlaced;
				}
				else if (flowerbed[i - 1] == 0 && flowerbed[i + 1] == 0) {
					flowerbed[i] = 1;
					++hasPlaced;
				}
			}
		}
		if (hasPlaced < n) return false;
		return true;
	}
};

/**
 *
 * You're now a baseball game point recorder.
 *
 * Given a list of strings, each string can be one of the 4 following types:
 *
 * 1. Integer (one round's score): Directly represents the number of points you get in this round.
 * 2. "+" (one round's score): Represents that the points you get in this round are the sum of 
 *    the last two valid round's points.
 * 3. "D" (one round's score): Represents that the points you get in this round are the doubled data of 
 *    the last valid round's points.
 * 4. "C" (an operation, which isn't a round's score): Represents the last valid round's points 
 *    you get were invalid and should be removed.
 * 5. Each round's operation is permanent and could have an impact on the round before and the round after.
 *
 * You need to return the sum of the points you could get in all the rounds.
 *
 * Example 1:
 * Input: ["5","2","C","D","+"]
 * Output: 30
 * Explanation: 
 * Round 1: You could get 5 points. The sum is: 5.
 * Round 2: You could get 2 points. The sum is: 7.
 * Operation 1: The round 2's data was invalid. The sum is: 5.  
 * Round 3: You could get 10 points (the round 2's data has been removed). The sum is: 15.
 * Round 4: You could get 5 + 10 = 15 points. The sum is: 30.
 * Example 2:
 * Input: ["5","-2","4","C","D","9","+","+"]
 * Output: 27
 * Explanation: 
 * Round 1: You could get 5 points. The sum is: 5.
 * Round 2: You could get -2 points. The sum is: 3.
 * Round 3: You could get 4 points. The sum is: 7.
 * Operation 1: The round 3's data is invalid. The sum is: 3.  
 * Round 4: You could get -4 points (the round 3's data has been removed). The sum is: -1.
 * Round 5: You could get 9 points. The sum is: 8.
 * Round 6: You could get -4 + 9 = 5 points. The sum is 13.
 * Round 7: You could get 9 + 5 = 14 points. The sum is 27.
 * Note:
 * The size of the input list will be between 1 and 1000.
 * Every integer represented in the list will be between -30000 and 30000.
 *
 */
class Solution24 {
public:
	int calPoints(vector<string>& ops) {
		int sum = 0;
		int allNum[1024] = { 0 };
		int validPoint = -1;

		int num = 0;
		for (auto i = ops.begin(); i != ops.end(); i++)
		{
			if (*i == "+") {
				num = allNum[validPoint] + allNum[validPoint - 1];
				allNum[validPoint + 1] = num;
				validPoint++;
			}
			else if (*i == "D") {
				num = allNum[validPoint] * 2;
				allNum[validPoint + 1] = num;
				validPoint++;
			}
			else if (*i == "C") {
				allNum[validPoint] = 0;
				--validPoint;
			}
			else
			{
				num = atoi((*i).c_str());
				allNum[validPoint + 1] = num;
				validPoint++;
			}
		}
		for (int i = 0; i <= validPoint; i++)
		{
			sum += allNum[i];
		}
		return sum;
	}
};

/**
 *
 * Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.
 *
 * Example 1:
 * Input: "aba"
 * Output: True
 * Example 2:
 * Input: "abca"
 * Output: True
 * Explanation: You could delete the character 'c'.
 * Note:
 * The string will only contain lowercase characters a-z. The maximum length of the string is 50000.
 *
 */
class Solution25 {
public:
	bool validPalindrome(string s) {
		int len = s.size();
		if (len == 2) {
			return true;
		}
		if (len == 3) {
			int i = 1;
			if (s[0] == s[2]) return true;
			else
			{
				if (s[0] == s[1] || s[1] == s[2]) return true;
				return false;
			}
		}
		int p, q;
		int flag = 1;
		if (len % 2 == 0) {
			q = len / 2;
			p = q - 1;
			while (p >= 0) {
				if (s[p] != s[q]) {	//valid fail, need to delete
					int center = (len - 1) / 2;
					int new_p = center - 1;
					int new_q = center + 1;
					while (new_p >= 0) {
						if (s[new_p] != s[new_q]) {
							if (flag) {
								++new_q;
								flag = 0;
								continue;
							}
							else
							{
								new_p = center;
								new_q = center + 2;
								flag = 1;
								int sign = 1;
								while (new_p >= sign) {
									if (s[new_p] != s[new_q]) {
										if (flag) {
											--new_p;
											--sign;
											flag = 0;
											continue;
										}
										else return false;
									}
									++new_q;
									--new_p;
								}
							}
						}
						--new_p;
						++new_q;
					}
					return true;
				}
				--p;
				++q;
			}
			return true;
		}
		else
		{
			int center = len / 2;
			p = center - 1;
			q = center + 1;
			while (p >= 0) {
				if (s[p] != s[q]) {
					int new_q = center;
					int new_p = center - 1;
					while (new_p >= 0) {
						if (s[new_p] != s[new_q]) {
							if (flag) {
								++new_q;
								flag = 0;
								continue;
							}
							else
							{
								flag = 1;
								new_p = center;
								new_q = center + 1;
								int sign = 1;
								while (new_p >= sign) {
									if (s[new_p] != s[new_q]) {
										if (flag) {
											--new_p;
											--sign;
											flag = 0;
											continue;
										}
										else return false;
									}
									++new_q;
									--new_p;
								}
								return true;
							}
						}
						--new_p;
						++new_q;
					}
					return true;
				}
				--p;
				++q;
			}
			return true;
		}
	}
};

/**
 *
 * Given two strings A and B, find the minimum number of times A has to be repeated
 * such that B is a substring of it. If no such solution, return -1.
 *
 * For example, with A = "abcd" and B = "cdabcdab".
 * Return 3, because by repeating A three times (“abcdabcdabcd”),
 * B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").
 *
 * Note:
 * The length of A and B will be between 1 and 10000.
 *
 */
class Solution26 {
public:
/*	int isPrior(string son, string str, int site) {
		int len = son.size() - 1;
		if (site == 0) return -1;
		int i = site - 1;
		while (i >= 0) {
			if (son[len] != str[i]) return 0;
			--len;
			--i;
		}
		return 1;
	}
	int isRear(string son, string str, int site) {
		int len = son.size();
		int length = str.size();
		if (site == length) return -1;
		int i = 0;
		while (site < length) {
			if (son[i] != str[site]) return 0;
			++i;
			++site;
		}
		return 1;
	}
	int repeatedStringMatch(string A, string B) {
		string a = A, b = B;
		int len_a = A.size(), len_b = B.size();
		int temp = B.find(A);
		if (len_b > len_a) {
			if (temp < 0 || temp > len_b) return -1;
		}
		int matchSite = 0;
		int i = 0, j = 0;
		while (A.size() < len_b) {
			A += a;
			++j;
		}
		while (i < 10020) {
			++i;
			matchSite = A.find(B);
			if (matchSite >= 0 && matchSite < A.size()) return i + j;
			if()
			A += a;
		}
		return -1;
	}*/
	int isPrior(string son, string str, int site) {
		int len = son.size() - 1;
		if (site == 0) return -1;
		int i = site - 1;
		while (i >= 0) {
			if (son[len] != str[i]) return 0;
			--len;
			--i;
		}
		return 1;
	}
	int isRear(string son, string str, int site) {
		int len = son.size();
		int length = str.size();
		if (site == length) return -1;
		int i = 0;
		while (site < length) {
			if (son[i] != str[site]) return 0;
			++i;
			++site;
		}
		return 1;
	}
	int repeatedStringMatch(string A, string B) {
		int len_a = A.size(), len_b = B.size();
		int flag = -2;


		if (len_a > len_b) {
			flag = A.find(B);
			if (flag >= 0 && flag < A.size()) return 1;
			string a = A + A;
			flag = a.find(B);
			if (flag < 0 || flag > a.size()) return -1;
			else return 2;
		}
		else if (len_a == len_b && A == B) return 1;

		int count = 0, first_match = -1, next_match = -1, now_match = -1, match_site = 0;
		
		first_match = B.find(A);
		if (first_match >= len_b) return -1;
		if (first_match < len_a) {
			flag = isPrior(A, B, first_match);
			if (flag == 1) ++count;
			else if (flag == 0) return -1;
		}
		else return -1;

		next_match = first_match;
		while (next_match < len_b && next_match >= 0) {
			++count;
			match_site = next_match + len_a;
			next_match = B.find(A, match_site);
		}
		if (len_b - match_site > len_a) return -1;
		flag = isRear(A, B, match_site);
		if (flag == 1) ++count;
		else if (flag == 0) return -1;
		return count;
	}
};

/**
 *
 * Given a positive integer num, write a function which returns True if num is a perfect square else False.
 *
 * Note: Do not use any built-in library function such as sqrt.
 *
 * Example 1:
 *
 * Input: 16
 * Returns: True
 * Example 2:
 *
 * Input: 14
 * Returns: False
 *
 */
class Solution27 {
public:
	bool isPerfectSquare(int num) {
		if (num == 0 || num == 1) return true;
		int p = 1, q = num, mid = (p + q) / 2;
		int n = 0;
		if (num == 2147483647) return false;
		if (mid > 46340) mid = 46340;
		while (p <= q) {
			n = mid*mid;
			if (n == num) return true;
			else if (n > num) q = mid - 1;
			else p = mid + 1;
			mid = (p + q) / 2;
		}
		return false;
	}
};

/**
 * 
 * Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.
 *
 * For example:
 * Given the below binary tree and sum = 22,
 *             5
 *            / \
 *           4   8
 *          /   / \
 *         11  13  4
 *        /  \      \
 *       7    2      1
 * return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
 *
 */
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class UnSoluted {
public:
	bool findSum(TreeNode* root, int sum, int num) {
		if (root == NULL) return num == sum;
		int new_num = num + root->val;
		if (findSum(root->left, sum, new_num) == true) return true;
		else return findSum(root->right, sum, new_num);
	}

	bool hasPathSum(TreeNode* root, int sum) {
		if (root == nullptr) return false;
		return findSum(root, sum, 0);
	}
};

/**
 *
 * Given an integer (signed 32 bits), write a function to check whether it is a power of 4.
 *
 * Example:
 * Given num = 16, return true. Given num = 5, return false.
 *
 * Follow up: Could you solve it without loops/recursion?
 */
class Solution28 {
public:
	bool isPowerOfFour(int num) {
		if (num < 0) return false;
		double n = num;
		if (n < 4) {
			if (n == 1) return true;
			return false;
		}
		while (n > 1) {
			n /= 4;
		}
		if (n == 1) return true;
		return false;
	}
};

/**
 *
 * Count the number of segments in a string, where a segment is defined to be a 
 * contiguous sequence of non-space characters.
 *
 * Please note that the string does not contain any non-printable characters.
 * Example:
 *
 * Input: "Hello, my name is John"
 * Output: 5
 *
 */
class Solution29 {
public:
	int countSegments(string s) {
		int length = s.size();
		if (length == 1 && s[0] != ' ')return 1;
		int count = 0;
		int flag = 0;
		for (int i = 0; i < length; i++)
		{
			if (s[i] == ' ' && flag) {
				++count;
			}
			if (s[i] != ' ') flag = 1;
			else flag = 0;
		}
		if (flag) ++count;
		return count;
	}
};

/**
 *
 * Given a positive 32-bit integer n, you need to find the smallest 32-bit integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive 32-bit integer exists, you need to return -1.
 *
 * Example 1:
 * Input: 12
 * Output: 21
 * Example 2:
 * Input: 21
 * Output: -1
 *
 */
class Solution {
public:
	bool isLimited(int a[], int n) {
		int max[] = { 4,2,9,4,9,6,7,2,9,5 };
		if (n > 10) return false;
		if (n < 10) return true;
		for (int i = n - 1; i >= 0; i--)
		{
			if (a[i] > max[9 - i]) return false;
		}
		return true;
	}
	int nextGreaterElement(int n) {
		int num = 0;
		int res = 0;
		int a[20];
		int len = 0;
		while (n) {
			a[len++] = n % 10;
			n /= 10;
		}
		for (int i = 0; i < len; i++)
		{
			int side = 0, max = 0, site = 0;
			int flag = 0;
			for (int j = i - 1; j >= 0; j--)
			{
				if (j == i - 1) {
					max = a[j] - a[i];
					site = j;
				}
				side = a[j] - a[i];
				if (side > 0 && side <= max) {
					flag = 1;
					site = j;
					max = side;
				}
			}
			if (flag) {
				swap(a[site], a[i]);
				for (int k = i - 1; k >= 0; k--)
				{
					max = a[k] - a[0];
					site = 0;
					for (int m = 0; m < k; m++)
					{
						side = a[k] - a[m];
						if (side > 0 && side > max) {
							max = side;
							site = m;
						}
					}
					if(max > 0) swap(a[site], a[k]);
				}
				if (isLimited(a, len)) {
					i = len;
					while (i > 0) {
						res += a[--i];
						res *= 10;
					}
					res /= 10;
					return res;
				}
			}
		}
		return -1;
	}
};