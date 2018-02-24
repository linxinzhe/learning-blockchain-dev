<?php
// GET PRIVATE PUBLIC KEY
function get_private()
{
    $config = array(
        'private_key_bits' => 2048,
    );
    openssl_pkey_export($_b4b7 = openssl_pkey_new($config), $_eeb0);// The default value is OPENSSL_KEYTYPE_RSA.
    return array($_b4b7, $_eeb0);
}

function get_public($_b065)
{
    $_cb64 = openssl_pkey_get_details($_b065);
    return $_cb64['key'];
}

//$private = get_private();
//var_dump($private);
//var_dump(get_public($private[0]));
//var_dump(substr(md5(get_public($private[0])), 0, 8));  //生成md5摘要的地址，截取为8位地址

$private = get_private();
$public = get_public($private[0]);
echo $public;
