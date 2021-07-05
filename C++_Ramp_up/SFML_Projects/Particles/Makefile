
copy :
	scp -r ../Particles pi@192.168.100.30:/home/pi/work	

all :
	g++ ./src/main.cpp ./src/CircleElement.cpp ./src/GenerateRandomNumbers.cpp  ./src/Constants.cpp ./src/Game.cpp ./src/Window.cpp ./src/Inputs.cpp -o particles -lsfml-graphics -lsfml-window -lsfml-system -lpthread -I ./include -Wall --std=c++17
