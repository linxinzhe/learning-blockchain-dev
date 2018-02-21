<?php

$block = get_head() . get_coinbase();
file_put_contents('1.block', $block);

function get_head()
{
    $current = hash('sha256', get_coinbase(), true);
    $nonce = pack('L', 0);
    $previous = str_repeat(chr(0), 32);
    $target = str_repeat(chr(0), 32);
    $time = pack('L', time());

    return $current . $nonce . $previous . $target . $time;
}

function get_coinbase()
{
    $x = get_input();
    $y = get_output();
    $total = pack('L', 4 + strlen($x) + strlen($y));
    return $total . $x . $y;
}

function get_input()
{
    $a = pack('L', 0);
    $b = pack('L', 0);
    $index = pack('L', 0);
    $transaction = str_repeat(chr(0), 32);

    $total = pack('L', 48);
    return $total . $index . $a . $b . $transaction;
}

function get_output()
{
    $address = substr(md5(file_get_contents("./public.txt")), 0, 8);
    $amount = chr(100) . chr(0) . chr(0) . chr(0) . chr(0) . chr(0) . chr(0) . chr(0);

    $a = chr(8) . chr(0) . chr(0) . chr(0);
    $total = chr(24) . chr(0) . chr(0) . chr(0);
    return $total . $a . $address . $amount;
}