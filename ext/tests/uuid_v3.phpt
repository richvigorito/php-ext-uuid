--TEST--
uuid::v3() returns a valid UUIDv3 string
--FILE--
<?php
$uuid = uuid::v3();
echo $uuid, "\n";
?>
--EXPECTF--
%r^[0-9a-f]{8}-[0-9a-f]{4}-3[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$%r

