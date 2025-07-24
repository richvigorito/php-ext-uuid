--TEST--
uuid::v6() returns a valid UUIDv6 string
--FILE--
<?php
$uuid = uuid::v6();
echo $uuid, "\n";
?>
--EXPECTF--
%r^[0-9a-f]{8}-[0-9a-f]{4}-6[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$%r

