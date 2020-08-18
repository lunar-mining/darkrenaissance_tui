default: pages.o menu.o login.o main.o 
	g++ *.o -lpanel -lncurses

login.o: login.hpp login.cpp
	g++ -c login.cpp 

pages.o: pages.hpp pages.cpp
	g++ -c pages.cpp

main.o: main.cpp
	g++ -c main.cpp  

#gui.o: gui.hpp gui.cpp
	#g++ -c gui.cpp 

# $(shell pkg-config --cflags biji)

