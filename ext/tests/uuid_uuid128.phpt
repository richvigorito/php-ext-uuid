--TEST--
UUID::uuid128() returns 16 raw bytes
--FILE--
<?php
$uuid_bin = uuid::uuid128();
var_dump(strlen($uuid_bin));
?>
--EXPECT--
int(16)
