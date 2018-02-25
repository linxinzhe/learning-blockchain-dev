#!/usr/bin/env bash
rm -rf build
mkdir -p build
gcc -c src/lecture7_ecc_private_public_base64.c -Iinclude -o build/lecture7_ecc_private_public_base64.o

gcc build/lecture7_ecc_private_public_base64.o lib/libtomcrypt.a lib/libtfm.a lib/libtommath.a -o build/lecture7_ecc_private_public_base64.elf

cd ./build
./lecture7_ecc_private_public_base64.elf
cd ..
#openssl dgst -sha256 random.txt