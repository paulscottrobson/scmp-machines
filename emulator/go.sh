rm scmpmc
make
asl -L test.asm
p2bin test.p test.bin
./scmpmc test.bin
