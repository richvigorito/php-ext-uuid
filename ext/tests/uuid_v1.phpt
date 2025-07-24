--TEST--
uuid::v1() returns a valid UUIDv1 string
--FILE--
<?php
$uuid = uuid::v1();
echo $uuid, "\n";
?>
--EXPECTF--
%r^[0-9a-f]{8}-[0-9a-f]{4}-1[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$%r

