#include "cpair.h"

cpair* CPair(unsigned key_size, unsigned value_size){
    cpair* pair;
    __allocate((void**)&pair, 0, sizeof(cpair));

    pair->_key_size = key_size;
    __allocate(&pair->_key, 0, key_size);
    pair->_values = CVector(value_size, 1);

    return pair;
}

void make_pair(cpair* pair, const void* key, const cvector* values){
    memcpy(pair->_key, key, pair->_key_size);
    CV_copy(pair->_values, values);
}

void set_key(cpair* pair, const void* key){
    memcpy(pair->_key, key, pair->_key_size);
}

void set_value(cpair* pair, const void* value, unsigned index){
    if(index < pair->_values->_size){
        memcpy(pair->_values->_data+pair->_values->_block_size*index, value, pair->_values->_block_size);
    }
}

void add_value(cpair* pair, const void* value){
    // push_back()
}

unsigned size_of_values(const cpair* pair){
    return pair->_values->_size;
}

void delete_pair(cpair* pair){
    free((void*)pair->_key);
    pair->_key = NULL;

    CV_delete(pair->_values);
    pair->_values = NULL;

    free((void*)pair);
}