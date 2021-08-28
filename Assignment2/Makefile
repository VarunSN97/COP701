build:
	gcc -o obj/wm src/wallis_method.c -lpthread -lm
	gcc -o obj/fm src/fourier_method.c -lpthread -lm
	gcc -o obj/fp src/fourier_parallel.c -lpthread -lm
	gcc -o obj/wp src/wallis_parallel.c -lpthread -lm
		 
run: build
	obj/./wm 10 1000000
	obj/./fm 10 1000000
	obj/./wp 1000000
	obj/./fp 1000000
	
plota:
	gnuplot --persist -e "plot 'thread_vs_performance_(wallis).txt' w l"
	
plotb:
	gnuplot --persist -e "plot 'thread_vs_performance_(fourier).txt' w l"
	
clean:
	rm -rf obj/*
	rm -rf *.txt
	

