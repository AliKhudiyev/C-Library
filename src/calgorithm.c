#include "calgorithm.h"

size_t CAlgo_find(const void* data, size_t size, size_t block_size, 
                  const void* token, size_t beg, size_t end, 
                  int (*equals)(const void* data, const void* token)){
    size_t sz = strlen(token);
    if(beg >= size || end > size || beg + sz > size) return -1;

    for(size_t i=0; i<end-sz-beg; ++i){
        if(equals){
            if(equals(data + (beg + i) * block_size, token)){
                return i;
            }
        }
        else if(!memcmp(data + (beg + i) * block_size, 
                        token, 
                        strlen(token))) return i;
    }
    return -1;
}

size_t CAlgo_rfind(const void* data, size_t size, size_t block_size, 
                   const void* token, size_t beg, size_t end, 
                   int (*equals)(const void* data, const void* token)){
    size_t sz = strlen(token);
    if(beg >= size || end > size || beg + sz > size) return -1;

    for(size_t i=end-sz-beg-1, j=sz-1; i>=0 && i!=-1; --i, ++j){
        if(equals){
            if(equals(data + (beg + i) * block_size, token)){
                return j;
            }
        }
        else if(!memcmp(data + (beg + i) * block_size, 
                        token, 
                        strlen(token))) return j;
    }
    return -1;
}

size_t CAlgo_find_first_of(const void* data, size_t size, size_t block_size, 
                           const void* token, size_t beg, size_t end, 
                           int (*equals)(const void* data, const void* token)){
    return -1;
}

size_t CAlgo_find_last_of(const void* data, size_t size, size_t block_size, 
                          const void* token, size_t beg, size_t end, 
                          int (*equals)(const void* data, const void* token)){
    return -1;
}

size_t CAlgo_find_first_not_of(const void* data, size_t size, size_t block_size, 
                               const void* token, size_t beg, size_t end, 
                               int (*equals)(const void* data, const void* token)){
    return -1;
}

size_t CAlgo_find_last_not_of(const void* data, size_t size, size_t block_size, 
                              const void* token, size_t beg, size_t end, 
                              int (*equals)(const void* data, const void* token)){
    return -1;
}