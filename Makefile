build:
	g++ src/*.cpp -Isrc -std=c++17 -o ./bin/game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
run:
	./bin/game