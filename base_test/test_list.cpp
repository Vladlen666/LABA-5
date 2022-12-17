#include "list.h"
#include <gtest.h>

TEST(TList, can_create_list)
{
  ASSERT_NO_THROW(TList<int> ls);
}

TEST(TList, new_list_is_empty)
{
  TList<int> ls;
  EXPECT_EQ(ls.is_empty(), true);
}

TEST(TList, can_get_size)
{
  TList<int> ls;
  EXPECT_EQ(ls.get_size(), 0);
}

TEST(TList, size_changes_when_insert_first)
{
  TList<int> ls;
  ls.insert_first(3);
  EXPECT_EQ(ls.get_size(), 1);
  ls.insert_first(5);
  EXPECT_EQ(ls.get_size(), 2);
}

TEST(TList, size_changes_when_insert_last)
{
  TList<int> ls;
  ls.insert_last(3);
  EXPECT_EQ(ls.get_size(), 1);
  ls.insert_last(5);
  EXPECT_EQ(ls.get_size(), 2);
}

TEST(TList, size_changes_when_insert_in_order)
{
  TList<int> ls;
  ls.insert_in_order(5);
  EXPECT_EQ(ls.get_size(), 1);
  ls.insert_in_order(6);
  EXPECT_EQ(ls.get_size(), 2);
  ls.insert_in_order(4);
  EXPECT_EQ(ls.get_size(), 3);
}

TEST(TList, size_changes_when_insert_in_pos)
{
  TList<int> ls;
  ls.insert_in_pos(5, 0);
  EXPECT_EQ(ls.get_size(), 1);
  ls.insert_in_pos(8, 1);
  EXPECT_EQ(ls.get_size(), 2);
}

TEST(TList, empty_after_clear_list)
{
  TList<int> ls;
  ls.insert_first(7);
  ls.insert_first(9);
  ls.insert_first(11);
  ls.clear();
  EXPECT_EQ(ls.is_empty(), true);
}

TEST(TList, throws_when_insert_in_non_existent_pos)
{
  TList<int> ls;
  ASSERT_ANY_THROW(ls.insert_in_pos(5, 2));
}

TEST(TList, can_insert_in_first_pos)
{
  TList<int> ls;
  ASSERT_NO_THROW(ls.insert_in_pos(5, 0));
}

TEST(TList, can_insert_in_last_pos)
{
  TList<int> ls;
  ls.insert_first(3);
  ASSERT_NO_THROW(ls.insert_in_pos(5, 1));
}

TEST(TList, throws_when_insert_in_too_large_pos)
{
  TList<int> ls;
  ls.insert_first(7);
  ASSERT_ANY_THROW(ls.insert_in_pos(7, 5));
}

TEST(TList, throws_when_insert_in_too_small_pos)
{
  TList<int> ls;
  ls.insert_first(7);
  ASSERT_ANY_THROW(ls.insert_in_pos(7, -3));
}

TEST(TList, throws_when_delete_in_pos_in_empty_list)
{
  TList<int> ls;
  ASSERT_ANY_THROW(ls.delete_in_pos(0));
}

TEST(TList, throws_when_delete_in_too_large_pos)
{
  TList<int> ls;
  ls.insert_first(7);
  ASSERT_ANY_THROW(ls.delete_in_pos(5));
}

TEST(TList, throws_when_delete_in_too_small_pos)
{
  TList<int> ls;
  ls.insert_first(7);
  ASSERT_ANY_THROW(ls.delete_in_pos(-3));
}

TEST(TList, can_delete_first_elem)
{
  TList<int> ls;
  ls.insert_first(5);
  ls.insert_first(7);
  ls.insert_first(9);
  ls.insert_first(11);
  ASSERT_NO_THROW(ls.delete_first());
  EXPECT_EQ(ls[0], 9);
}

TEST(TList, can_delete_last_elem)
{
  TList<int> ls;
  ls.insert_first(5);
  ls.insert_first(7);
  ls.insert_first(9);
  ls.insert_first(11);
  ASSERT_NO_THROW(ls.delete_last());
  EXPECT_EQ(ls[ls.get_size() - 1], 7);
}
