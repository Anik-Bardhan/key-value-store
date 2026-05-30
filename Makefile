CFLAGS = -Wall -Wextra -g -fsanitize=address -fsanitize=leak -Isrc

kvstore: src/main.c src/hashtable.c src/hashtable.h
	gcc $(CFLAGS) src/main.c src/hashtable.c -o kvstore

clean:
	rm -f kvstore
	rm -f run_tests

run: kvstore
	ASAN_OPTIONS=detect_leaks=0 ./kvstore

test: tests/test_hashtable.c src/hashtable.c
	gcc $(CFLAGS) tests/test_hashtable.c src/hashtable.c -o run_tests
	ASAN_OPTIONS=detect_leaks=0 ./run_tests