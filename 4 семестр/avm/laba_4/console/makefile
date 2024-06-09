build:
	gcc main.c -o console.out -I../include -I../mySimpleComputer -I../myBigChars -I../myTerm -L../mySimpleComputer -lMySimpleComputer -L../myTerm -lMyTerm -L../myBigChars -lMyBigChars

run: build
	./console.out

clean: 
	rm -rf console.out