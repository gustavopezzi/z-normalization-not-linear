build:
	gcc -std=c99 -Wall ./src/*.c -lm -o main

run:
	./main

clean:
	rm main