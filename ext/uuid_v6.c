#include "php.h"
#include "uuid.h"
#include <uuid/uuid.h>
#include <time.h>
#include <string.h>

// Helper to get current timestamp in 100-nanosecond intervals since UUID epoch
static uint64_t get_uuid_timestamp() {
    // UUID epoch is October 15, 1582
    const uint64_t UUID_EPOCH_START = 0x01B21DD213814000ULL;

    struct timeval tv;
    gettimeofday(&tv, NULL);

    uint64_t timestamp = ((uint64_t)tv.tv_sec * 10000000) + ((uint64_t)tv.tv_usec * 10);
    return timestamp + UUID_EPOCH_START;
}

PHP_METHOD(uuid, v6)
{
    uint8_t uuid_val[16];
    uint64_t timestamp = get_uuid_timestamp();

    // Rearrange timestamp for UUIDv6 (48 bits timestamp high + 12 bits timestamp low)
    uuid_val[0] = (timestamp >> 40) & 0xFF;
    uuid_val[1] = (timestamp >> 32) & 0xFF;
    uuid_val[2] = (timestamp >> 24) & 0xFF;
    uuid_val[3] = (timestamp >> 16) & 0xFF;
    uuid_val[4] = (timestamp >> 8) & 0xFF;
    uuid_val[5] = timestamp & 0xFF;

    // Set version (6) in the correct nibble (bits 12-15 of time_hi_and_version)
    uuid_val[6] = (uuid_val[6] & 0x0F) | 0x60;

    // Get clock_seq (random or from MAC)
    // Using libuuid for randomness here for simplicity
    uuid_t random_bytes;
    uuid_generate_random(random_bytes);

    uuid_val[7] = random_bytes[0];

    // Variant (bits 6 and 7 of clock_seq_hi_and_reserved)
    uuid_val[8] = (random_bytes[1] & 0x3F) | 0x80;

    // Node (last 6 bytes)
    memcpy(&uuid_val[9], &random_bytes[2], 6);

    char uuid_str[37];
    snprintf(uuid_str, sizeof(uuid_str),
        "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
        uuid_val[0], uuid_val[1], uuid_val[2], uuid_val[3],
        uuid_val[4], uuid_val[5],
        uuid_val[6], uuid_val[7],
        uuid_val[8], uuid_val[9],
        uuid_val[10], uuid_val[11], uuid_val[12], uuid_val[13], uuid_val[14], uuid_val[15]
    );

    RETURN_STRING(uuid_str);
}

