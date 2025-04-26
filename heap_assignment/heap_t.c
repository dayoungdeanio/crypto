#include "heap_t.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

heap_t heap(size_t ele_size, bool (*gt)(void *, void *)) {
    heap_t h;
    h.ele_size = ele_size;
    h.num_eles = 0;
    h.capacity = 4;
    h.gt = gt;
    h.eles = malloc(h.capacity * ele_size);
    return h;
}

void insert(heap_t *heap, void *ele_ptr) {
    if (heap->num_eles == heap->capacity) {
        heap->capacity *= 2;
        heap->eles = realloc(heap->eles, heap->capacity * heap->ele_size);
    }

    void *dest = (char *)heap->eles + (heap->num_eles * heap->ele_size);
    memcpy(dest, ele_ptr, heap->ele_size);

    size_t i = heap->num_eles;
    heap->num_eles++;

    while (i > 0) {
        size_t parent = (i - 1) / 2;
        void *parent_ptr = (char *)heap->eles + (parent * heap->ele_size);
        void *curr_ptr = (char *)heap->eles + (i * heap->ele_size);

        if (heap->gt(curr_ptr, parent_ptr)) {
            uint8_t temp[heap->ele_size];
            memcpy(temp, curr_ptr, heap->ele_size);
            memcpy(curr_ptr, parent_ptr, heap->ele_size);
            memcpy(parent_ptr, temp, heap->ele_size);
            i = parent;
        } else {
            break;
        }
    }
}

void *maxpop(heap_t *heap) {
    if (heap->num_eles == 0) return NULL;

    void *ret = malloc(heap->ele_size);
    void *root = heap->eles;
    memcpy(ret, root, heap->ele_size);

    heap->num_eles--;

    if (heap->num_eles == 0) {
        return ret;
    }

    void *last = (char *)heap->eles + (heap->num_eles * heap->ele_size);
    memcpy(root, last, heap->ele_size);

    size_t i = 0;
    while (1) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t largest = i;

        if (left < heap->num_eles) {
            void *left_ptr = (char *)heap->eles + (left * heap->ele_size);
            void *largest_ptr = (char *)heap->eles + (largest * heap->ele_size);
            if (heap->gt(left_ptr, largest_ptr)) {
                largest = left;
            }
        }

        if (right < heap->num_eles) {
            void *right_ptr = (char *)heap->eles + (right * heap->ele_size);
            void *largest_ptr = (char *)heap->eles + (largest * heap->ele_size);
            if (heap->gt(right_ptr, largest_ptr)) {
                largest = right;
            }
        }

        if (largest != i) {
            void *curr_ptr = (char *)heap->eles + (i * heap->ele_size);
            void *largest_ptr = (char *)heap->eles + (largest * heap->ele_size);

            uint8_t temp[heap->ele_size];
            memcpy(temp, curr_ptr, heap->ele_size);
            memcpy(curr_ptr, largest_ptr, heap->ele_size);
            memcpy(largest_ptr, temp, heap->ele_size);

            i = largest;
        } else {
            break;
        }
    }

    return ret;
}
