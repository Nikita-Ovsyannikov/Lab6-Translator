#include "gtest.h"
#include "translator.h"

TEST(Translator_tests, simple_addition) 
{
    Translator expr("2 + 3");
    ASSERT_EQ(expr.calculate(), 5);
}

TEST(Translator_tests, simple_subtraction)
{
    Translator expr("2 - 3");
    ASSERT_EQ(expr.calculate(), -1);
}

TEST(Translator_tests, simple_multiplication)
{
    Translator expr("2 * 3");
    expr.printRes();
    ASSERT_EQ(expr.calculate(), 6);
}

TEST(Translator_tests, simple_division)
{
    Translator expr("10 / 2");
    ASSERT_EQ(expr.calculate(), 5);
}

TEST(Translator_tests, simple_raising_to_power)
{
    Translator expr("10 ^ 2");
    ASSERT_EQ(expr.calculate(), 100);
}

TEST(Translator_tests, complex_expression) 
{
    Translator expr("(2 + 3) * 4 - 1");
    ASSERT_DOUBLE_EQ(expr.calculate(), 19);
    ASSERT_EQ(expr.getPostfixExpression(), "2 3 + 4 * 1 -");
}

TEST(Translator_tests, expression_with_spaces) 
{
    Translator expr(" 2  +  3 *  4 ");
    ASSERT_DOUBLE_EQ(expr.calculate(), 14);
    ASSERT_EQ(expr.getPostfixExpression(), "2 3 4 * +");
}

TEST(Translator_tests, decimal_numbers) 
{
    Translator expr("2.5 + 3.5 * 2");
    ASSERT_DOUBLE_EQ(expr.calculate(), 9.5);
    ASSERT_EQ(expr.getPostfixExpression(), "2.5 3.5 2 * +");
}

TEST(Translator_tests, division_by_zero) 
{
    Translator expr("5 / 0");
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(translator_tests, invalid_expression_1) 
{ 
    Translator expr("2 +* 3");
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(translator_tests, invalid_expression_3) 
{
    Translator expr("(2 + 3");
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(translator_tests, invalid_expression_4) { 
    Translator expr("2 + 3)");
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(translator_tests, mismatched_parentheses) {
    Translator expr("(2 + 3 * (4 - 1"); 
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(translator_tests, not_enough_operands) 
{
    Translator expr("+");
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(translator_tests, not_enough_operands_after_operator) 
{
    Translator expr("2 +");
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(translator_tests, invalid_number) 
{
    Translator expr("2 + 1.2.3");
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(translator_tests, empty_expression) 
{
    Translator expr("");
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(translator_tests, starting_with_operator) 
{
    Translator expr("* 2 3");
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(translator_tests, ending_with_operator) 
{
    Translator expr("2 3 + *");
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(translator_tests, consecutive_operators) 
{
    Translator expr("2 ++ 3");
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(translator_tests, point_at_start) 
{
    Translator expr(".2 + 3");
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(translator_tests, point_at_end) 
{
    Translator expr("2. + 3");
    ASSERT_ANY_THROW(expr.calculate());
}