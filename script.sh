#!/usr/bin/env bash
rm -rf build
mkdir -p build
gcc -c src/tfm_desc.c -Iinclude -o build/tfm_desc.o
gcc -c src/lecture5_tx_input.c -Iinclude -o build/lecture5_tx_input.o

gcc build/lecture5_tx_input.o build/tfm_desc.o lib/libtomcrypt.a lib/libtfm.a lib/libtommath.a -o build/lecture5_tx_input.elf

cd ./build
./lecture5_tx_input.elf > ../tx.txt
cd ..
xxd tx.txt
#openssl dgst -sha256 random.txt