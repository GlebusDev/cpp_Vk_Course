#include "Allocator.h"

void Allocator::makeAllocator(size_t maxSize) {
    if (memoryPtr != nullptr)
        delete[] memoryPtr;
    memoryPtr = new char[maxSize];
    offset = 0;
    memSize = maxSize;
}

char* Allocator::alloc(size_t size) {
    if (offset + size > memSize)
        return nullptr;
    char* ptr = memoryPtr + offset;
    offset += size;
    return ptr;
}

void Allocator::reset() {
    offset = 0;
}

Allocator::~Allocator() {
    delete[] memoryPtr;
}
