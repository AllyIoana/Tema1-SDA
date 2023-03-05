build: 
	gcc -o tema1 main.c cuvintehash.c printN.c functii-tabHash.c functiiLG.c
run:
	./tema1
clean:
	rm -rf tema1