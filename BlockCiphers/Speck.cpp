//
// Created by Alexander Lavysh on 29/11/15.
//

#include "Speck.h"
#include <inttypes.h>

static inline void speck_round(uint64_t& x, uint64_t& y, const uint64_t k)
{
    x = (x >> 8) | (x << (8 * sizeof(x) - 8)); // x = ROTR(x, 8)
    x += y;
    x ^= k;
    y = (y << 3) | (y >> (8 * sizeof(y) - 3)); // y = ROTL(y, 3)
    y ^= x;
}

void speck_encrypt( const uint64_t plaintext[2]
        , const uint64_t key[2]
        , uint64_t ciphertext[2]
)
{
    uint64_t b = key[0];
    uint64_t a = key[1];
    ciphertext[0] = plaintext[0];
    ciphertext[1] = plaintext[1];
    for (unsigned i = 0; i < 32; i++) {
        speck_round(ciphertext[1], ciphertext[0], b);
        speck_round(a, b, i);
    }
}