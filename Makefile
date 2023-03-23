CC = gcc
CFLAGS = -Wall -Wextra

SRC = BinCalc.c
EXEC = BinCalc

.PHONY: all clean try

all: $(EXEC)

try: 
	./BinCalc 3.40e38 '*' 3.40e38; \
	./BinCalc 1.23456 / 2.3456; \
	./BinCalc 1e-45 / 2; \
	./BinCalc 1 / 0; \
	./BinCalc 0 / 0; \
	

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ -lm

clean:
	rm -f $(EXEC)
