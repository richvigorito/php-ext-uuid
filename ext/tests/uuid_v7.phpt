--TEST--
uuid::v7() returns a valid UUIDv7 string
--FILE--
<?php
$uuid = uuid::v7();
echo $uuid, "\n";
?>
--EXPECTF--
%r^[0-9a-f]{8}-[0-9a-f]{4}-7[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$%r
