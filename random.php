<?php

$random = file_get_contents("./random.txt");
$random = base64_decode($random);
var_dump(strlen($random));

srand(intval($random));
var_dump(rand());
var_dump(rand());
var_dump(rand());