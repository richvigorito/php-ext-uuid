--TEST--
uuid::v5() returns a valid UUIDv5 string
--FILE--
<?php
$uuid = uuid::v5();
echo $uuid, "\n";
?>
--EXPECTF--
%r^[0-9a-f]{8}-[0-9a-f]{4}-5[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$%r
