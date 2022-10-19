all: hash mac encr decr

hash: build/hash.o build/permutation.o build/sponge.o build/crypto.o build/iohelpers.o
	gcc build/hash.o build/permutation.o build/sponge.o build/crypto.o build/iohelpers.o -o hash -g

mac: build/mac.o build/permutation.o build/sponge.o build/crypto.o build/iohelpers.o
	gcc build/mac.o build/permutation.o build/sponge.o build/crypto.o build/iohelpers.o -o mac -g

encr: build/encr.o build/permutation.o build/sponge.o build/crypto.o build/iohelpers.o
	gcc build/encr.o build/permutation.o build/sponge.o build/crypto.o build/iohelpers.o -o encr -g

decr: build/decr.o build/permutation.o build/sponge.o build/crypto.o build/iohelpers.o
	gcc build/decr.o build/permutation.o build/sponge.o build/crypto.o build/iohelpers.o -o decr -g

build/hash.o: src/hash.c include/crypto.h include/iohelpers.h
	gcc -Iinclude -Wall -g -c src/hash.c -o build/hash.o

build/mac.o: src/mac.c include/crypto.h include/iohelpers.h
	gcc -Iinclude -Wall -g -c src/mac.c -o build/mac.o

build/encr.o: src/encr.c include/crypto.h include/iohelpers.h
	gcc -Iinclude -Wall -g -c src/encr.c -o build/encr.o

build/decr.o: src/decr.c include/crypto.h include/iohelpers.h
	gcc -Iinclude -Wall -g -c src/decr.c -o build/decr.o

build/permutation.o: include/permutation.h src/permutation.c
	gcc -Iinclude -Wall -g -c src/permutation.c -o build/permutation.o

build/sponge.o: include/sponge.h src/sponge.c include/permutation.h
	gcc -Iinclude -Wall -g -c src/sponge.c -o build/sponge.o

build/crypto.o: include/crypto.h src/crypto.c include/sponge.h
	gcc -Iinclude -Wall -g -c src/crypto.c -o build/crypto.o

build/iohelpers.o: include/iohelpers.h src/iohelpers.c
	gcc -Iinclude -Wall -g -c src/iohelpers.c -o build/iohelpers.o

clean:
	rm -rf build/* hash mac encr decr
