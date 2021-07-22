TARGET	= program
SRC	= $(TARGET).cpp
CC	= g++
LFLAGS= -o $(TARGET) -ltsal -lportaudio -fopenmp

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CXXFLAGS) $(LFLAGS)

clean:
	rm -f $(TARGET) *.o
