#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <numeric>

double final_ave(std::vector<int> homeworks, int exam)
{
	return (std::accumulate(homeworks.begin(), homeworks.end(), 0.0) / homeworks.size()) * 0.4 + exam * 0.6;
}

TEST(FinalResultAverageTest, WithGoodInput) {
	std::vector<int> vec1 = { 1,2,3 };
	std::vector<int> vec2 = { 8,4,6 };
	double exam1 = 8;
	double exam2 = 9;
	EXPECT_EQ(final_ave(vec1, exam1), 5.6);
	EXPECT_EQ(final_ave(vec2, exam2), 7.8);
}