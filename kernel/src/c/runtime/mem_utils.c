#include <inttypes.h>

void * memset(void *ptr, int value, uint64_t num) {
    uint8_t fill = value;
    void* end = ptr + num;
    for(uint8_t *tptr = ptr; tptr != end; tptr++) {
        *tptr = value;
    }
    return ptr;
}

void * memcpy (void * destination, const void * source, uint64_t num) {
    for(uint64_t i = 0; i < num; i++) {
        ((uint8_t*)destination)[i] = ((uint8_t*)source)[i];
    }
}
