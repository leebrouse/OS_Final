CXX=g++
TARGET=main
OBJ=main.o Disk.o

$(TARGET):$(OBJ)
	$(CXX) -g  -o  $(TARGET) $(OBJ)

main.o:main.cpp
	$(CXX) -g -c main.cpp

Disk.o:Disk.cpp
	$(CXX) -g -c Disk.cpp

clean:
	rm -f main main.o Disk.o 