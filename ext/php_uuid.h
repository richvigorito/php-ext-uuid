#ifndef PHP_UUID_H
#define PHP_UUID_H 1

#define PHP_UUID_VERSION "1.0"
#define PHP_UUID_EXTNAME "uuid"

extern zend_module_entry uuid_module_entry;
#define phpext_uuid_ptr &uuid_module_entry

PHP_MINIT_FUNCTION(uuid);
PHP_METHOD(uuid, v7);

#endif
