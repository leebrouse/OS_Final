CXX=g++
TARGET=main
OBJ=main.o Disk.o

$(TARGET):$(OBJ)
	$(CXX) -o $(TARGET) $(OBJ)

main.o:main.cpp
	$(CXX) -c main.cpp

Disk.o:Disk.cpp
	$(CXX) -c Disk.cpp

clean:
	rm -f main main.o Disk.o 