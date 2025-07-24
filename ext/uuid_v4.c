#include "php.h"
#include "uuid.h"
#include <uuid/uuid.h>

PHP_METHOD(uuid, v4)
{
    uuid_t binuuid; 
    char uuid_str[37];

    uuid_generate_random(binuuid);

    uuid_unparse_lower(binuuid, uuid_str);

    RETURN_STRING(uuid_str);
}
