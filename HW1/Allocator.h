#pragma once
#include <stdio.h>
class Allocator {
 public:
  void makeAllocator(size_t maxSize);
  char* alloc(size_t size);
  void reset();
  ~Allocator();

 private:
  // указатель на всю память
  char* memoryPtr = nullptr;
  // количество байт выделенной памяти
  size_t memSize = 0;
  // количество байт занятой памяти
  size_t offset = 0;
};
