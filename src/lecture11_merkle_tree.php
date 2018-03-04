<?php

$a = hash('sha256', "a", true);
$b = hash('sha256', "b", true);
$c = hash('sha256', "c", true);
$d = hash('sha256', "d", true);
$e = hash('sha256', "e", true);
$f = hash('sha256', $a . $b, true);
$g = hash('sha256', $c . $d, true);
$h = hash('sha256', $e . $e, true);
$i = hash('sha256', $f . $g, true);
$j = hash('sha256', $h . $h, true);
$k = hash('sha256', $i . $j);

var_dump($k);