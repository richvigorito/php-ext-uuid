--TEST--
UUID::ulid() returns a 26-character Crockford base32 string
--FILE--
<?php
$ulid = uuid::ulid();
var_dump(strlen($ulid));
var_dump(preg_match('/^[0-9A-HJ-KM-NP-TV-Z]{26}$/', $ulid) === 1);
?>
--EXPECT--
int(26)
bool(true)
