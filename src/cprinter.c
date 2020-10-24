#include "cvector.h"
#include <stdio.h>
static char* _cprinter_buffer = NULL;

char* CPrinter_get_buffer(){
    return _cprinter_buffer;
}

void CPrinter_set_buffer(const char* buffer, size_t size){
    if(size == -1){ size = strlen(buffer);
    printf("> strlen: %zu\n", size);
    }
    
    size_t old_size = _cprinter_buffer? strlen(_cprinter_buffer) : 0;
    __allocate((void**)&_cprinter_buffer, old_size, size);
    strncpy(_cprinter_buffer, buffer, size);
}

void CPrinter_delete(){
    free(_cprinter_buffer);
    _cprinter_buffer = NULL;
}