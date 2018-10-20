all:
	gcc shortestDistance.c -o submission

clean:
	rm -rf submission shortestDistance.o
