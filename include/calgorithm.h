
#ifndef _ALGORITHM_
#define _ALGORITHM_

#include <stdlib.h>
#include <unistd.h>
#include <memory.h>

size_t CAlgo_find(const void* data, size_t size, size_t block_size, const void* token, size_t beg, size_t end);

#endif
