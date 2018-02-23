#!/usr/bin/env bash
rm -rf build
mkdir -p build
gcc -c src/program_ecc.c -o build/program_ecc.o

gcc build/program_ecc.o lib/libtomcrypt.a -o build/program_ecc.elf

cd ./build
./program_ecc.elf
cd ..

#openssl dgst -sha256 random.txt