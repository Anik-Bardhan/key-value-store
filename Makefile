CFLAGS = -Wall -Wextra -g -fsanitize=address -fsanitize=leak -Isrc

kvstore: src/main.c src/hashtable.c src/hashtable.h
	gcc $(CFLAGS) src/main.c src/hashtable.c -o kvstore

clean:
	rm -f kvstore