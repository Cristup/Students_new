#include <gtest/gtest.h>
#include <iostream>

#include "../include/libs.h"
#include "../include/objects.h"



TEST(RecordTest, Initialization) {
	Record rec;
	EXPECT_EQ(rec.input, 0.0);
	EXPECT_EQ(rec.sorting, 0.0);
	EXPECT_EQ(rec.categorising, 0.0);
	EXPECT_EQ(rec.output, 0.0);
	EXPECT_EQ(rec.total, 0.0);
	EXPECT_EQ(rec.count, 0);
}

TEST(StudentTest, ParametrizedConstructor) {
	student object("Jonas", "Jonaitis", { 10, 9, 8 }, 7);

	EXPECT_EQ(object.name(), "Jonas");
	EXPECT_EQ(object.surname(), "Jonaitis");
	EXPECT_EQ(object.exam(), 7);
	EXPECT_EQ(object.homeworks(), std::vector<int>({ 10, 9, 8 }));
}

TEST(StudentTest, CopyAssignmentOperator) {
	student source("Jonas","Jonaitis", { 10, 9, 8 }, 7);
	student target;
	target = source;

	EXPECT_EQ(target.name(), "Jonas");
	EXPECT_EQ(target.surname(), "Jonaitis");
	EXPECT_EQ(target.homeworks(), std::vector<int>({ 10, 9, 8 }));
	EXPECT_EQ(target.exam(), 7);
	EXPECT_DOUBLE_EQ(target.final_average(), source.final_average());
	EXPECT_DOUBLE_EQ(target.final_median(), source.final_median());
}

TEST(StudentTest, FinalResult) {
	student source("Jonas", "Jonaitis", { 10, 9, 8 }, 7);

	double expectedResult = 0.4 * 9 + 0.6 * 7;
	EXPECT_EQ(source.final_average(), expectedResult);
	EXPECT_EQ(source.final_median(), expectedResult);
}

TEST(IsDigitsTest, ValidStrings) {
    EXPECT_TRUE(is_digits("123"));
    EXPECT_TRUE(is_digits("000"));
    EXPECT_TRUE(is_digits("456789"));
    EXPECT_TRUE(is_digits("0"));
}

TEST(IsDigitsTest, InvalidStrings) {
    EXPECT_FALSE(is_digits("abc"));  
    EXPECT_FALSE(is_digits("123a"));  
    EXPECT_FALSE(is_digits("12#45"));
    EXPECT_FALSE(is_digits("12.45"));
    EXPECT_FALSE(is_digits("12 45"));
}