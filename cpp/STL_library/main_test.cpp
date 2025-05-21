#include "s21_array/test.cpp"
#include "s21_list/test.cpp"
#include "s21_map/map_test.cpp"
#include "s21_multiset/multiset_test.cpp"
#include "s21_queue/test.cpp"
#include "s21_set/set_test.cpp"
#include "s21_stack/test.cpp"
#include "s21_vector/test.cpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
