CC = gcc
TARGET = solver.exe
SRC = main.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re