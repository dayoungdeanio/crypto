#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint64_t modexp(uint64_t m, uint64_t e, uint64_t n) {
    uint64_t r = 1;
    m = m % n;
    while (e > 0) {
        if (e & 1) {
            r = (r * m) % n;
        }
        e = e >> 1;
        m = (m * m) % n;
    }
    return r;
}

int main(int argc, char *argv[]) {
    FILE *key, *fin, *fout;
    unsigned char *buf;
    uint64_t n, e, m, c;
    long len;
    size_t read_len;
    int i;

    if (argc != 4) {
        return 1;
    }

    if (strchr(argv[1], 'e')) {
        key = fopen("unsafe.pub", "r");
        if (!key) return 1;
        if (fscanf(key, "-----BEGIN UNSAFE PUBLIC KEY-----\n%lx\n%lx\n-----END UNSAFE PUBLIC KEY-----\n", &n, &e) != 2) return 1;
        fclose(key);
    } else if (strchr(argv[1], 'd')) {
        key = fopen("unsafe.bad", "r");
        if (!key) return 1;
        if (fscanf(key, "-----BEGIN UNSAFE PRIVATE KEY-----\n%lx\n%lx\n%lx\n-----END UNSAFE PRIVATE KEY-----\n", &n, &e, &e) != 3) return 1;
        fclose(key);
    } else {
        return 1;
    }

    fin = fopen(argv[2], "rb");
    if (!fin) return 1;
    fseek(fin, 0, SEEK_END);
    len = ftell(fin);
    rewind(fin);

    buf = malloc(len);
    if (!buf) return 1;
    read_len = fread(buf, 1, (size_t)len, fin);
    if (read_len != (size_t)len) return 1;
    fclose(fin);

    m = 0;
    for (i = 0; i < len; i++) {
        m |= ((uint64_t)buf[i]) << (8 * i);
    }

    c = modexp(m, e, n);

    fout = fopen(argv[3], "wb");
    if (!fout) return 1;
    fwrite(&c, sizeof(c), 1, fout);
    fclose(fout);

    free(buf);

    return 0;
}
