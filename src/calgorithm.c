#include "calgorithm.h"

size_t CAlgo_find(const void* data, size_t size, size_t block_size, 
                  const void* token, size_t beg, size_t end, 
                  int (*equals)(const void* data, const void* token)){
    if(beg >= size || end > size) return -1;

    for(size_t i=0; i<end-beg; ++i){
        if(equals){
            if(equals(data + (beg + i) * block_size, token)){
                return i;
            }
        }
        else if(!memcmp(data + (beg + i) * block_size, 
                        token, 
                        block_size)) return i;
    }
    return -1;
}