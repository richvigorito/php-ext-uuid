#ifndef PHP_UUID_H
#define PHP_UUID_H

#include "php.h"

PHP_METHOD(uuid, v1);
PHP_METHOD(uuid, v3);
PHP_METHOD(uuid, v4);
PHP_METHOD(uuid, v5);
PHP_METHOD(uuid, v6);
PHP_METHOD(uuid, v7);
PHP_METHOD(uuid, snowflake);
PHP_METHOD(uuid, ksuid);
PHP_METHOD(uuid, ulid);
PHP_METHOD(uuid, uuid128);

#endif

