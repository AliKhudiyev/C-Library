
#ifndef _ALGORITHM_
#define _ALGORITHM_

#include <stdlib.h>
#include <unistd.h>
#include <memory.h>

size_t CAlgo_find(const void* data, size_t size, size_t block_size, 
                  const void* token, size_t beg, size_t end, 
                  int (*equals)(const void* data, const void* token));
size_t CAlgo_rfind(const void* data, size_t size, size_t block_size, 
                   const void* token, size_t beg, size_t end, 
                   int (*equals)(const void* data, const void* token));
size_t CAlgo_find_first_of(const void* data, size_t size, size_t block_size, 
                           const void* token, size_t beg, size_t end, 
                           int (*equals)(const void* data, const void* token));
size_t CAlgo_find_last_of(const void* data, size_t size, size_t block_size, 
                          const void* token, size_t beg, size_t end, 
                          int (*equals)(const void* data, const void* token));
size_t CAlgo_find_first_not_of(const void* data, size_t size, size_t block_size, 
                               const void* token, size_t beg, size_t end, 
                               int (*equals)(const void* data, const void* token));
size_t CAlgo_find_last_not_of(const void* data, size_t size, size_t block_size, 
                              const void* token, size_t beg, size_t end, 
                              int (*equals)(const void* data, const void* token));

#endif
