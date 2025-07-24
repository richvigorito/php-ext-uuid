--TEST--
uuid::snowflake() returns a numeric string
--FILE--
<?php
$sf = uuid::snowflake();
echo $sf, "\n";
?>
--EXPECTF--
%r^\d+$%r

