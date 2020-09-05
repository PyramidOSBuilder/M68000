m68=m68
all: $(m68)

cc=gcc
cflags= -Wall -O2
inc= -Iinclude
libs=
obj= src/list.o src/file.o src/token.o src/main.o

.c.o:
	$(cc) $(cflags) $(inc) -c $< -o $@

$(m68): $(obj)
	$(cc) $(cflags) $(libs) $(inc) $(obj) -o $@

clean: 
	rm $(m68) $(obj)
test0: 
	./$(m68) tests/test.txt


