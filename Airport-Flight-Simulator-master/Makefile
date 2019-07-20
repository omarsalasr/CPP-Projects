proj6: Osalas3Proj6.o Airport.o MyList.o MyNode.o MyFileList.o MyFileNode.o
	g++ -g -o proj6 Osalas3Proj6.o Airport.o MyList.o MyNode.o MyFileList.o MyFileNode.o

Osalas3Proj6.o: Osalas3Proj6.cpp Proj6.h
	g++ -c Osalas3Proj6.cpp

Airport.o: Airport.cpp Proj6.h
	g++ -c Airport.cpp

MyList.o: MyList.cpp Proj6.h
	g++ -c MyList.cpp

MyNode.o: MyNode.cpp Proj6.h
	g++ -c MyNode.cpp

MyFileList.o: MyFileList.cpp Proj6.h
	g++ -c MyFileList.cpp

MyFileNode.o: MyFileNode.cpp Proj6.h
	g++ -c MyFileNode.cpp

clean:
	rm proj6 Osalas3Proj6.o Airport.o MyList.o MyNode.o MyFileList.o MyFileNode.o
