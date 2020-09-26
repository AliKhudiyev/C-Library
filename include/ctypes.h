
#ifndef _TYPES_
#define _TYPES_

#include <stdarg.h>

#define False 0
#define True 1

typedef unsigned char bool_t;

// char* CType_convert2(const void* data, size_t size){
//     char* _data;

//     __allocate(&_data, 0, size);
//     for(size_t i=0; i<size; ++i){
//         memcpy(_data+i, data+i, sizeof(char));
//     }

//     return _data;
// }

// void* CType_convert(size_t size, unsigned int count, ...){
//     void* _data;
//     va_list args;

//     __allocate(&_data, 0, size);
//     va_start(args, count);
//     for(unsigned i=0; i<count; ++i){
//         void* _tmp = va_arg(args, )
//         memcpy(_data+i, )
//     }
//     va_end(args);

//     return _data;
// }

// #define MCType_convert(size, count, ...)

#endif
