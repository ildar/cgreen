#include <stdlib.h>
#include <cgreen/internal/circular_buffer.h>

CircularBuffer* create_circular_buffer(int len) {
    CircularBuffer* result;
    
    result = malloc(sizeof(CircularBuffer));
    if(!result)
        return NULL;
    result->length = len;
    result->buffer = malloc(len*sizeof(CB_TYPE));
    if(!result) {
        free(result);
        return NULL;
    }
    return result;
}

/* vim: set ts=4 sw=4 et cindent: */
