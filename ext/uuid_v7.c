#include "php.h"            // Core PHP functions/macros
#include "ext/standard/info.h" // For phpinfo and standard functions

#include <stdint.h>         // For uint8_t, uint64_t
#include <stdlib.h>         // For EXIT_SUCCESS
#include <string.h>         // For memcpy or string ops
#include <time.h>           // For timespec, timespec_get
#include <unistd.h>         // For getentropy (on some platforms)


PHP_METHOD(uuid, v7)
{
    uint8_t uuid_val[16];

    // Fill entire UUID with entropy
    if (getentropy(uuid_val, sizeof(uuid_val)) != 0) {
        php_error_docref(NULL, E_WARNING, "Failed to get entropy");
        RETURN_FALSE;
    }

    // Get timestamp in milliseconds
    struct timespec ts;
    if (timespec_get(&ts, TIME_UTC) == 0) {
        php_error_docref(NULL, E_WARNING, "Failed to get time");
        RETURN_FALSE;
    }

    uint64_t timestamp = (uint64_t)ts.tv_sec * 1000 + ts.tv_nsec / 1000000;

    // Set timestamp in big-endian (bytes 0-5)
    uuid_val[0] = (timestamp >> 40) & 0xFF;
    uuid_val[1] = (timestamp >> 32) & 0xFF;
    uuid_val[2] = (timestamp >> 24) & 0xFF;
    uuid_val[3] = (timestamp >> 16) & 0xFF;
    uuid_val[4] = (timestamp >> 8) & 0xFF;
    uuid_val[5] = timestamp & 0xFF;

    // Set version to 7 (UUIDv7: bits 48-51)
    uuid_val[6] = (uuid_val[6] & 0x0F) | 0x70;

    // Set variant to 10xxxxxx (RFC 4122)
    uuid_val[8] = (uuid_val[8] & 0x3F) | 0x80;

    // Format UUID string
    char uuid_str[37]; // 36 chars + null terminator
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
