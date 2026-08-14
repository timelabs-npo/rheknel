#ifndef RHEKNEL_SHA256_H
#define RHEKNEL_SHA256_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint32_t state[8];
    uint64_t bit_count;
    uint8_t block[64];
    size_t block_size;
} RheaSha256;

void rhea_sha256_init(RheaSha256 *context);
void rhea_sha256_update(RheaSha256 *context, const uint8_t *data, size_t size);
void rhea_sha256_final(RheaSha256 *context, uint8_t digest[32]);

#endif
