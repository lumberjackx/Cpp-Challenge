labyrinth: gsoc_labyrinth.o
	g++ gsoc_labyrinth.o -o labyrinth

gsoc_labyrinth.o: gsoc_labyrinth.cpp
	g++ -c gsoc_labyrinth.cpp

clean:
	del *.o labyrinth.exe