fifteen: fifteen.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o fifteen fifteen.c -lcs50 -lm

test: test.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o fifteen test.c -lcs50 -lm

clean:
	rm -f *.o a.out core fifteen log.txt
