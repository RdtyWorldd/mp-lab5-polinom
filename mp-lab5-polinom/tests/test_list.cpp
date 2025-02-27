#include "gtest.h"
#include "../mp-lab5-polinom/List.h"

TEST(List, can_create_list)
{
  ASSERT_NO_THROW(List<int>());
}

TEST(List, created_list_is_empty)
{
  List<int> list;
  EXPECT_TRUE(list.isEmpty());
}

TEST(List, can_create_copied_list)
{
  List<int> l1;
  for(int i = 0; i < 10; i++)
    l1.pushBack(i);
  ASSERT_NO_THROW(List<int> l2(l1));
}

TEST(List, copied_list_is_equal_to_source_one)
{
  List<int> l1;
  for(int i = 0; i < 10; i++)
    l1.pushBack(i);
  List<int> l2(l1);
  EXPECT_EQ(l1, l2);
}

TEST(List, copied_list_has_its_own_memory)
{
  List<int>* l1 = new List<int>();
  for(int i = 0; i < 10; i++)
    l1->pushBack(i);
  List<int> l2(*l1);
  delete l1;
  ASSERT_NO_THROW(l2.get(0));
}

TEST(List, isEmpty_return_false_when_list_isnt_full)
{
  List<int> l;
  l.pushBack(0);
  EXPECT_FALSE(l.isEmpty());
}

TEST(List, cleared_list_isEmpty)
{
  List<int> l;
  for (int i = 0; i < 3; i++)
	  l.pushBack(i);
  l.clear();
  EXPECT_TRUE(l.isEmpty());
}


TEST(List, push_back_added_element_to_end)
{
  List<int> l;
  for(int i =0; i < 10; i++)
  {
    l.pushBack(i);
  }
  l.pushBack(0);
  EXPECT_EQ(l.get(l.getSize()-1), 0);
}

TEST(List, push_back_element_change_size)
{
  List<int> l;
  for (int i = 0; i < 10; i++)
    l.pushBack(i);
  EXPECT_EQ(l.getSize(), 10);
}

TEST(List, push_front_added_element_to_front)
{
  List<int> l;
  for(int i =0; i < 10; i++)
  {
    l.pushBack(i);
  }
  l.pushFront(10);
  EXPECT_EQ(l.get(0), 10);
}

TEST(List, push_front_element_change_size)
{
  List<int> l;
  for (int i = 0; i < 10; i++)
    l.pushFront(i);
  EXPECT_EQ(l.getSize(), 10);
}

TEST(List, can_add_element_in_any_position)
{
  List<int> l1, l2;
  for(int i =0;i < 5; i++)
    l2.pushBack(0);
  l2.pushBack(1);
  for(int i = 0; i < 5; i++)
    l2.pushBack(0);

  for(int i = 0; i < 10; i++)
    l1.pushBack(0);
  l1.add(5, 1);
  EXPECT_EQ(l1, l2);
}

TEST(List, add_element_change_size)
{
  List<int> l;
  for (int i = 0; i < 10; i++)
    l.add(i, 0);
  EXPECT_EQ(l.getSize(), 10);
}

TEST(List, can_remove_element)
{
  List<int> l;
  for(int i = 0; i < 10; i++)
    l.pushBack(i);
  l.remove(2);
  EXPECT_EQ(l.get(2), 3);
}

TEST(List, remove_element_change_size)
{
  List<int> l;
  for (int i = 0; i < 10; i++)
    l.pushBack(i);
  
  l.remove(2);
  EXPECT_EQ(l.getSize(), 9);
}

TEST(List, removed_first_element_change_pFirst)
{
  List<int> l;
  for (int i = 0; i < 10; i++)
    l.pushBack(i);
  l.remove(0);
  EXPECT_EQ(l.get(0), 1);
}

TEST(List, removed_last_element_change_pLast)
{
  List<int> l;
  for (int i = 0; i < 10; i++)
    l.pushBack(i);
  l.remove(l.getSize()-1);
  EXPECT_EQ(l.get(l.getSize()-1), 8);
}



