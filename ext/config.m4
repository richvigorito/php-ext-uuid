PHP_ARG_ENABLE(uuid, whether to enable uuid support,
[  --enable-uuid           Enable uuid support])

if test "$PHP_UUID" != "no"; then
    AC_CHECK_HEADER(uuid/uuid.h, [], [
        AC_MSG_ERROR([Cannot find uuid/uuid.h. Please install the libuuid development package.])
    ])

    PHP_ADD_LIBRARY(uuid, 1, UUID_SHARED_LIBADD)
    PHP_NEW_EXTENSION(uuid, uuid.c uuid_v1.c uuid_v3.c uuid_v4.c uuid_v5.c uuid_v6.c uuid_v7.c uuid_snowflake.c uuid_ksuid.c uuid_ulid.c uuid_uuid128.c, $ext_shared, , $UUID_SHARED_LIBADD)

fi
