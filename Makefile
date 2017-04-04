# poker.c Makefile
# Created by: Sean Quinn squin037@fiu.edu

# Macros

CC =	gcc
FILES =	main.c poker.h poker.c 
OUT_EXE =	poker	

# Targets

build:	$(FILES)
	$(CC) -o $(OUT_EXE) $(FILES) 

clean:
	rm -f *.o core

rebuild: clean build

debug:	$(FILES)	
	$(CC) -g $(FILES) -o $(OUT_EXE)
