#include <stdint.h>
#include <string.h>

#define S 64

uint64_t bigadd(uint64_t *a, uint64_t *b, uint64_t *dest) {
    uint64_t carry = 0;
    for (int i = 0; i < S; i++) {
        uint64_t sum = a[i] + b[i] + carry;
        if (sum < a[i] || (carry && sum == a[i])) {
            carry = 1;
        } else {
            carry = 0;
        }
        dest[i] = sum;
    }
    return carry;
}

uint64_t bigsub(uint64_t *a, uint64_t *b, uint64_t *dest) {
    uint64_t borrow = 0;
    for (int i = 0; i < S; i++) {
        uint64_t diff = a[i] - b[i] - borrow;
        if (a[i] < b[i] + borrow) {
            borrow = 1;
        } else {
            borrow = 0;
        }
        dest[i] = diff;
    }
    return borrow;
}

uint64_t bigmul(uint64_t *a, uint64_t *b, uint64_t *dest) {
    uint64_t tmp[2 * S];
    memset(tmp, 0, sizeof(tmp));

    for (int i = 0; i < S; i++) {
        uint64_t carry = 0;
        for (int j = 0; j < S; j++) {
            __uint128_t product = (__uint128_t)a[i] * b[j] + tmp[i + j] + carry;
            tmp[i + j] = (uint64_t)product;
            carry = (uint64_t)(product >> 64);
        }
        tmp[i + S] += carry;
    }

    memcpy(dest, tmp, S * sizeof(uint64_t));
    return 0;
}

// --- New Code for Division ---

static int cmp(uint64_t *a, uint64_t *b) {
    for (int i = S - 1; i >= 0; i--) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;
}

static void lshift(uint64_t *a) {
    uint64_t carry = 0;
    for (int i = 0; i < S; i++) {
        uint64_t next_carry = a[i] >> 63;
        a[i] = (a[i] << 1) | carry;
        carry = next_carry;
    }
}

static void rshift(uint64_t *a) {
    uint64_t carry = 0;
    for (int i = S - 1; i >= 0; i--) {
        uint64_t next_carry = a[i] << 63;
        a[i] = (a[i] >> 1) | carry;
        carry = next_carry;
    }
}

uint64_t bigdiv(uint64_t *num, uint64_t *den, uint64_t *quo, uint64_t *rem) {
    memset(quo, 0, S * sizeof(uint64_t));
    memset(rem, 0, S * sizeof(uint64_t));

    for (int i = S - 1; i >= 0; i--) {
        rem[i] = num[i];
    }

    uint64_t denom[S];
    memcpy(denom, den, S * sizeof(uint64_t));

    int shift = 0;
    while (cmp(rem, denom) >= 0) {
        lshift(denom);
        shift++;
    }

    while (shift--) {
        rshift(denom);
        lshift(quo);
        if (cmp(rem, denom) >= 0) {
            bigsub(rem, denom, rem);
            quo[0] |= 1;
        }
    }

    return 0;
}

uint64_t bigquo(uint64_t *num, uint64_t *den, uint64_t *dest) {
    uint64_t rem[S];
    bigdiv(num, den, dest, rem);
    return 0;
}

uint64_t bigrem(uint64_t *num, uint64_t *den, uint64_t *dest) {
    uint64_t quo[S];
    bigdiv(num, den, quo, dest);
    return 0;
}

