#include <gtest/gtest.h>

#include <iostream>

#include <string>

#include "Allocator.h"

// тест проверяет, что класс работает нормально: выделяется память нужного размера и
// в нее можно записывать
TEST(ALLOCATOR_TESTS, baseTest) {
  Allocator allocator;
  allocator.makeAllocator(10);
  char* mem1 = allocator.alloc(10);
  mem1 = "123456789";
  std::string str2(mem1);
  ASSERT_EQ("123456789", str2);
}
// тест проверяет, что если попытаться выделить alloc слишком большое количество байт, то вернется nullptr
TEST(ALLOCATOR_TESTS, nullptrAllocTest) {
  Allocator allocator;
  allocator.makeAllocator(10);
  char* mem1 = allocator.alloc(11);
  ASSERT_EQ(mem1, nullptr);
}
// тест проверяет, что можно вызывать alloc несколько раз
TEST(ALLOCATOR_TESTS, manyAllocTest) {
  Allocator allocator;
  allocator.makeAllocator(10);
  char* mem1 = allocator.alloc(6);
  char* mem2 = allocator.alloc(4);
  mem2 = "abc";
  mem1 = "abcde";
  ASSERT_EQ(mem1,"abcde");
  ASSERT_EQ(mem2,"abc");
}
// тест проверяет работу метода reset
TEST(ALLOCATOR_TESTS, resetTest) {
  Allocator allocator;
  allocator.makeAllocator(10);
  char* mem1 = allocator.alloc(6);
  allocator.reset();
  char* mem2 = allocator.alloc(4);
  ASSERT_EQ(mem1,mem2);
}
// тест проверяет, что метод makeAllocator можно вызывать несколько раз
TEST(ALLOCATOR_TESTS, manyMakeAllocatorTest) {
  Allocator allocator;
  allocator.makeAllocator(10);
  char* mem1 = allocator.alloc(50);
  allocator.makeAllocator(50);
  char* mem2 = allocator.alloc(50);
  ASSERT_EQ(mem1,nullptr);
  ASSERT_NE(mem2,nullptr);
}
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
