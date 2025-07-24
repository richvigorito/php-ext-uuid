// uuid_ksuid.c
#include "php.h"
#include "uuid.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define KSUID_BYTES 20

// Simple base62 encoding table (digits + uppercase + lowercase)
static const char base62_chars[] = 
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

static void base62_encode(const uint8_t *src, size_t len, char *dst, size_t dst_len) {
    // Encode binary src to base62 string in dst
    // This is a simplified encoder assuming enough dst_len.
    // For real use, prefer a proper base62 implementation.
    uint64_t num = 0;
    for (size_t i = 0; i < len; i++) {
        num = (num << 8) + src[i];
    }

    // Fill dst backwards
    size_t pos = dst_len;
    dst[pos] = '\0';
    while (pos > 0) {
        dst[--pos] = base62_chars[num % 62];
        num /= 62;
    }
}

PHP_METHOD(uuid, ksuid)
{
    uint8_t ksuid[KSUID_BYTES];
    char ksuid_str[28]; // 27 chars + null terminator

    // Timestamp (4 bytes big endian)
    uint32_t timestamp = (uint32_t)time(NULL);
    ksuid[0] = (timestamp >> 24) & 0xFF;
    ksuid[1] = (timestamp >> 16) & 0xFF;
    ksuid[2] = (timestamp >> 8) & 0xFF;
    ksuid[3] = timestamp & 0xFF;

    // Random 16 bytes payload
    if (getentropy(ksuid + 4, 16) != 0) {
        php_error_docref(NULL, E_WARNING, "Failed to get entropy");
        RETURN_FALSE;
    }

    // Base62 encode to 27 chars (note: this is approximate for demonstration)
    base62_encode(ksuid, KSUID_BYTES, ksuid_str, 27);

    RETURN_STRING(ksuid_str);
}
