CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I src -MP -MMD
CPPFLAGST = -I thirdparty -MP -MMD
CHESS = bin/chess
TEST_NAME = bin/chess-test

all: $(CHESS)

chess-start: $(CHESS) 
	./$(CHESS)

$(CHESS): obj/src/chess/chess.o obj/src/libchessviz/libchessviz.a
	g++ $(CFLAGS) -o $@ $^

obj/src/chess/chess.o: src/chess/chess.cpp
	g++ -c -I src $(CFLAGS) $(CPPFLAGS) -o $@ $<

obj/src/libchessviz/libchessviz.a: obj/src/libchessviz/chessviz.o
	ar rcs $@ $^

obj/src/libchessviz/chessviz.o: src/libchessviz/chessviz.cpp
	g++ -c -I src $(CFLAGS) $(CPPFLAGS) -o $@ $<

.PHONY: all clean test chess-start test-start

clean:
	rm obj/src/libchessviz/*.[oad] obj/src/chess/*.[od] $(CHESS) $(TEST_NAME) obj/test/*.[od]

test-start:
	./$(TEST_NAME)

test: $(TEST_NAME)

$(TEST_NAME): obj/test/main.o obj/test/test.o obj/src/libchessviz/libchessviz.a
	g++ $(CFLAGS) -o $@ $^

obj/test/test.o: test/test.cpp
	g++ -c $(CFLAGS) $(CPPFLAGS) $(CPPFLAGST) $< -o $@

obj/test/main.o: test/main.cpp
	g++ -c $(CFLAGS) $(CPPFLAGS) $(CPPFLAGST) $< -o $@

-include obj/src/chess/chess.d obj/src/libchessviz/chessviz.d obj/test/test.d obj/test/main.d

