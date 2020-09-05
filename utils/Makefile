all: hwrite

cc=gcc
cflags= -Wall -O2
emu=qemu-system-m68k
bin=

hwrite: src/hwrite.c
	$(cc) $(cflags) $^ -o $@

testbin: 
	$(emu) -kernel $(bin)

clean:
	rm hwrite


