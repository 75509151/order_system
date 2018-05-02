ELF=main
SRC=$(shell find ./ -name "*.cpp")
OBJ=$(SRC:.cpp=.o)
LIB= -lncurses -lsqlite3
CC=g++ $(LIB) -g
CXX=g++ -g $(LIB)
$(ELF):$(OBJ)
	$(CC) -o $(ELF) $(OBJ) $(LIB)
$(OBJ):
clean:
	rm $(ELF) $(OBJ)
  

