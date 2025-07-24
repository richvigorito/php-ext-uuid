// uuid_uuid128.c
#include "php.h"
#include "uuid.h"
#include <stdint.h>

PHP_METHOD(uuid, uuid128)
{
    uint8_t uuid_val[16];

    if (getentropy(uuid_val, sizeof(uuid_val)) != 0) {
        php_error_docref(NULL, E_WARNING, "Failed to get entropy");
        RETURN_FALSE;
    }

    RETURN_STRINGL((char *)uuid_val, 16);
}

