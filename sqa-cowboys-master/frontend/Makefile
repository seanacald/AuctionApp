output: fileIO.o item.o main.o mainWindow.o user.o
	g++ fileIO.o item.o main.o mainWindow.o user.o -o auction

fileIO.o: fileIO.cpp
	g++ -c fileIO.cpp

item.o: item.cpp
	g++ -c item.cpp

main.o: main.cpp
	g++ -c main.cpp

mainWindow.o: mainWindow.cpp
	g++ -c mainWindow.cpp

user.o: user.cpp
	g++ -c user.cpp

clean:
	rm *.o