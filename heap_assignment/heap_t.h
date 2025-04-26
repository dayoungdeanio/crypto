#include <stdbool.h>
#include <stdlib.h>

typedef struct heap_struct {
    size_t ele_size;
    size_t num_eles;
    size_t capacity;
    bool (*gt)(void *, void *);
    void *eles;
} heap_t;

heap_t heap(size_t ele_size, bool (*gt)(void *, void *));
void insert(heap_t *heap, void *ele_ptr);
void *maxpop(heap_t *heap);
