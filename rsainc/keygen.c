#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

uint64_t modinv(uint64_t a, uint64_t m) {
    int64_t m0 = m, t, q;
    int64_t x0 = 0, x1 = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;
    return (uint64_t)x1;
}

int is_prime(uint64_t n) {
    uint64_t i;
    if (n < 2)
        return 0;
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

uint64_t randprime() {
    uint64_t p;
    do {
        p = ((uint64_t)rand() << 32) | rand();
        p |= 1;
    } while (!is_prime(p));
    return p;
}

int main() {
    uint64_t p, q, n, e, d, phi;
    FILE *pub, *bad;

    srand(time(NULL));

    p = randprime();
    q = randprime();
    n = p * q;
    e = 0x10001;
    phi = (p - 1) * (q - 1);
    d = modinv(e, phi);

    pub = fopen("unsafe.pub", "w");
    fprintf(pub, "-----BEGIN UNSAFE PUBLIC KEY-----\n%lx\n%lx\n-----END UNSAFE PUBLIC KEY-----\n", n, e);
    fclose(pub);

    bad = fopen("unsafe.bad", "w");
    fprintf(bad, "-----BEGIN UNSAFE PRIVATE KEY-----\n%lx\n%lx\n%lx\n-----END UNSAFE PRIVATE KEY-----\n", n, e, d);
    fclose(bad);

    return 0;
}
