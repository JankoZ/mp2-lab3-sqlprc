#include "Lex.h"
#include <gtest.h>

TEST(tests, calculation)
{
    Queue<Lexema> lex_res = lex("(53 + 32 * 2) - 40 / 20");
    vector <Lexema> polska = ReversePolska(lex_res);

    EXPECT_EQ(Calculate(polska), (53 + 32 * 2) - 40 / 20);
}

TEST(tests, bracket_check1)
{
    Queue<Lexema> lex_res = lex("((53 + 32 * 2) - 40 / 20");

    ASSERT_ANY_THROW(ReversePolska(lex_res));
}

TEST(tests, bracket_check2)
{
    Queue<Lexema> lex_res = lex("(53 + 32 * 2)) - 40 / 20");

    ASSERT_ANY_THROW(ReversePolska(lex_res));
}

TEST(tests, empty_stack_pop)
{
    Stack<int> stack;

    ASSERT_ANY_THROW(stack.Pop());
}

TEST(tests, empty_stack_top)
{
    Stack<int> st;
    ASSERT_ANY_THROW(st.Top());
}