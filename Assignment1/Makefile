all:
	gcc -o obj/alpha src/matrixMulB.c 

run: all
	obj/./alpha 2048 1 1024
	paste b.txt a.txt >merge.txt
	gnuplot --persist -e "plot 'merge.txt' w l title 'block vs non block',5*x"

clean:
	rm -rf *.out
	rm -rf *.txt 
