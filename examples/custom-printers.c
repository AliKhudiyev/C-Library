#include "cpplib.h"
#include <stdio.h>

// Custom struct
typedef struct{
    float x, y;
}Vertex;

// Custom printer function for Vertex object
const char* Vertex_printer(void* data){
    Vertex* vertex = (Vertex*)data;
    char buffer[100];

    sprintf(buffer, "(%f, %f)", vertex->x, vertex->y);
    // Better to use library printer buffer
    CPrinter_set_buffer(buffer, 100);

    return CPrinter_get_buffer();
}

int main(){

    // 1. Constructor (stack)
    MCV_init(vec, Vertex, 1);

    // 2. Adding a new Vertex element
    MCV_emplace_back(&vec, Vertex, 2.25, -3);
    
    // 3. Setting the custom printer
    CV_set_printer(&vec, Vertex_printer);

    // 4. Printing the Vertex object
    printf("%s\n", MCV_str(&vec, 0));

    // . Destructor
    CV_destruct(&vec);

    return 0;
}