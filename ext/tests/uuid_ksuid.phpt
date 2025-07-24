--TEST--
UUID::ksuid() returns a 27-character base62 string
--FILE--
<?php
$ksuid = uuid::ksuid();
var_dump(strlen($ksuid));
var_dump(preg_match('/^[0-9A-Za-z]{27}$/', $ksuid) === 1);
?>
--EXPECT--
int(27)
bool(true)
