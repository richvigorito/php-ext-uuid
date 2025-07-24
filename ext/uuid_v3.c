#include "php.h"
#include "uuid.h"
#include <uuid/uuid.h>

PHP_METHOD(uuid, v3)
{
    uuid_t binuuid;
    char uuid_str[37];
    char namespace_uuid_str[] = "6ba7b810-9dad-11d1-80b4-00c04fd430c8"; // Example DNS namespace UUID

    uuid_t namespace_uuid;
    uuid_parse(namespace_uuid_str, namespace_uuid);

    const char *name = "example";  // For demo; you might want to accept param in future

    uuid_generate_md5(binuuid, namespace_uuid, (const unsigned char *)name, strlen(name));

    uuid_unparse_lower(binuuid, uuid_str);

    RETURN_STRING(uuid_str);
}

