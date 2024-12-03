
all:
	export MallocNanoZone=0
	g++ ./main.cpp -o main -g -fsanitize=address -fno-omit-frame-pointer -std=c++14
run:
	./main
clean:
	rm ./main
	rm -rf ./main.dSYM