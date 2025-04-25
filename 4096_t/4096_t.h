#ifndef BIG4096_T_H
#define BIG4096_T_H

#include <stdint.h>

#define S 64

void bigadd(uint64_t *a, uint64_t *b, uint64_t *res);
void bigsub(uint64_t *a, uint64_t *b, uint64_t *res);
void bigmul(uint64_t *a, uint64_t *b, uint64_t *res);
uint64_t bigdiv(uint64_t *num, uint64_t *den, uint64_t *quo, uint64_t *rem);
uint64_t bigquo(uint64_t *num, uint64_t *den, uint64_t *quo);
uint64_t bigrem(uint64_t *num, uint64_t *den, uint64_t *rem);

#endif
