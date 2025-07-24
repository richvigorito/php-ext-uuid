--TEST--
uuid::v4() returns a valid UUIDv4 string
--FILE--
<?php
$uuid = uuid::v4();
echo $uuid, "\n";
?>
--EXPECTF--
%r^[0-9a-f]{8}-[0-9a-f]{4}-4[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$%r

