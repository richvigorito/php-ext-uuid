#include "php.h"
#include "uuid.h"
#include <uuid/uuid.h>

PHP_METHOD(uuid, v1)
{
    uuid_t binuuid;
    char uuid_str[37];

    uuid_generate_time(binuuid);
    uuid_unparse_lower(binuuid, uuid_str);

    RETURN_STRING(uuid_str);
}
