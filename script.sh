mkdir -p build
tcc -c src/program.c -o build/program.o

tcc build/program.o lib/libtomcrypt.a -o build/program.elf

./build/program.elf