#include "php.h"
#include "php_uuid.h"
// #include "ext/standard/info.h" 

#include <stdint.h>         
#include <stdlib.h>         
#include <string.h>         
#include <time.h>           
#include <unistd.h>         
// #include <uuid/uuid.h> 
#include <sys/time.h>
#include <pthread.h>


#include <uuid.h>

zend_class_entry *uuid_ce;

// Method declaration
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

// Method entries
static const zend_function_entry uuid_class_methods[] = {
    PHP_ME(uuid, v1, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(uuid, v3, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(uuid, v4, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(uuid, v5, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(uuid, v6, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(uuid, v7, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(uuid, snowflake, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(uuid, ksuid, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(uuid, ulid, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(uuid, uuid128, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_FE_END
};



// MINIT: module initialization
PHP_MINIT_FUNCTION(uuid)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "uuid", uuid_class_methods);
    uuid_ce = zend_register_internal_class(&ce);
    return SUCCESS;
}

// Module entry
zend_module_entry uuid_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_UUID_EXTNAME,
    NULL, // no functions
    PHP_MINIT(uuid),
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_UUID_VERSION,
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(uuid)
