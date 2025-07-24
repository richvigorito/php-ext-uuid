#include "php.h"          // PHP extension API
#include "uuid.h"         // Your shared extension header

#include <stdint.h>       // uint64_t, uint16_t, etc.
#include <stdlib.h>       // Standard library functions (malloc, etc.)
#include <string.h>       // String operations
#include <sys/time.h>     // gettimeofday() for timestamps
#include <unistd.h>       // usleep()
#include <pthread.h>      // pthread_mutex_t for locking


//#define EPOCH 1609459200000ULL  // Jan 1, 2021
#define EPOCH 1288834974657ULL // Twitter epoch Nov 4, 2010

#define MACHINE_ID_BITS 10
#define SEQUENCE_BITS 12

#define MAX_MACHINE_ID ((1 << MACHINE_ID_BITS) - 1)
#define MAX_SEQUENCE ((1 << SEQUENCE_BITS) - 1)

static const uint16_t MACHINE_ID = 1; // Change or allow config later

static pthread_mutex_t sf_lock = PTHREAD_MUTEX_INITIALIZER;
static uint64_t last_timestamp = 0;
static uint16_t sequence = 0;

static uint64_t current_millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}

static uint64_t wait_next_millis(uint64_t last_ts) {
    uint64_t ts = current_millis();
    while (ts <= last_ts) {
        usleep(1000);  // 1ms
        ts = current_millis();
    }
    return ts;
}

static uint64_t generate_snowflake_id() {
    pthread_mutex_lock(&sf_lock);

    uint64_t timestamp = current_millis();

    if (timestamp < last_timestamp) {
        pthread_mutex_unlock(&sf_lock);
        return 0; // Or handle clock skew differently
    }

    if (timestamp == last_timestamp) {
        sequence = (sequence + 1) & MAX_SEQUENCE;
        if (sequence == 0) {
            timestamp = wait_next_millis(last_timestamp);
        }
    } else {
        sequence = 0;
    }

    last_timestamp = timestamp;

    uint64_t id = ((timestamp - EPOCH) << (MACHINE_ID_BITS + SEQUENCE_BITS)) |
                  ((MACHINE_ID & MAX_MACHINE_ID) << SEQUENCE_BITS) |
                  sequence;

    pthread_mutex_unlock(&sf_lock);
    return id;
}

PHP_METHOD(uuid, snowflake)
{
    char buf[32];
    uint64_t id = generate_snowflake_id();
    
    int len = snprintf(buf, sizeof(buf), "%" PRIu64, id);
    
    RETURN_STRINGL(buf, len);
}


