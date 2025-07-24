// uuid_ulid.c
#include "php.h"
#include "uuid.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define ULID_LEN 26

// Crockford base32 alphabet
static const char crockford_base32[] = "0123456789ABCDEFGHJKMNPQRSTVWXYZ";

static void base32_encode(const uint8_t *src, size_t src_len, char *dst, size_t dst_len) {
    // Simple Crockford base32 encode for 16 bytes input to 26 chars output
    // Assumes dst_len >= 26
    uint64_t buffer = 0;
    int bits_left = 0;
    size_t dst_pos = 0;

    for (size_t i = 0; i < src_len; i++) {
        buffer = (buffer << 8) | src[i];
        bits_left += 8;
        while (bits_left >= 5) {
            bits_left -= 5;
            uint8_t index = (buffer >> bits_left) & 0x1F;
            dst[dst_pos++] = crockford_base32[index];
            if (dst_pos == dst_len) return;
        }
    }
    if (bits_left > 0 && dst_pos < dst_len) {
        uint8_t index = (buffer << (5 - bits_left)) & 0x1F;
        dst[dst_pos++] = crockford_base32[index];
    }
    if (dst_pos < dst_len) {
        dst[dst_pos] = '\0';
    }
}

PHP_METHOD(uuid, ulid)
{
    uint8_t ulid[16];
    char ulid_str[ULID_LEN + 1];

    // Timestamp (48 bits = 6 bytes)
    struct timespec ts;
    if (timespec_get(&ts, TIME_UTC) == 0) {
        php_error_docref(NULL, E_WARNING, "Failed to get time");
        RETURN_FALSE;
    }
    uint64_t timestamp = (uint64_t)ts.tv_sec * 1000 + ts.tv_nsec / 1000000;

    // Store timestamp 6 bytes big endian
    ulid[0] = (timestamp >> 40) & 0xFF;
    ulid[1] = (timestamp >> 32) & 0xFF;
    ulid[2] = (timestamp >> 24) & 0xFF;
    ulid[3] = (timestamp >> 16) & 0xFF;
    ulid[4] = (timestamp >> 8) & 0xFF;
    ulid[5] = timestamp & 0xFF;

    // Random 10 bytes
    if (getentropy(ulid + 6, 10) != 0) {
        php_error_docref(NULL, E_WARNING, "Failed to get entropy");
        RETURN_FALSE;
    }

    base32_encode(ulid, 16, ulid_str, ULID_LEN);
    ulid_str[ULID_LEN] = '\0';

    RETURN_STRING(ulid_str);
}

