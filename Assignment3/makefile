libuserthread.so: myThread.o queue.o
	gcc -o libuserthread.so myThread.o queue.o -shared
myThread.o:
	gcc -Wall -fpic -c src/myThread.c
queue.o:
	gcc -Wall -fpic -c src/queue.c
	
test1: myThread.o queue.o
	gcc -c src/single_thread.c
	gcc single_thread.o myThread.o queue.o -o xyz
	./xyz
	
test2: myThread.o queue.o
	gcc -c src/multi_thread.c
	gcc multi_thread.o myThread.o queue.o -o xyz
	./xyz

test3: myThread.o queue.o
	gcc -c src/multi_thread_yield.c
	gcc multi_thread_yield.o myThread.o queue.o -o xyz
	./xyz

test4: myThread.o queue.o
	gcc -c src/multi_lock.c
	gcc multi_lock.o myThread.o queue.o -o xyz
	./xyz

test5: myThread.o queue.o
	gcc -c src/multi_lock_yield.c
	gcc multi_lock_yield.o myThread.o queue.o -o xyz
	./xyz	


clean:
	rm -rf *.o
	rm -rf *.so
	rm -rf src/*.o
