all: chess

chess: chess.c
	gcc -Wall -Werror -o chess chess.c

run: chess
	./chess

remove: chess	
	rm chess
