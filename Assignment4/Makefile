build:
	gcc -fPIC -c src/classifier.c
	gcc -fPIC -c src/regression.c
	gcc -fPIC -c src/backpropogation.c
	gcc -fPIC -c src/trainer.c
	gcc -fPIC -c src/read_csv.c
	gcc -fPIC -c src/helper.c
	gcc -c src/main.c
	gcc -shared -o toynn.so classifier.o regression.o backpropogation.o trainer.o read_csv.o helper.o
	
	
start: build
	gcc -o obj/prediction main.o toynn.so -lm
	
run: start
	./obj/prediction $(LAYER) $(L_RATE) $(N_FEATURES) $(TRAINING_ROWS) $(EPOCHS) $(BATCH_SIZE) $(ALGO) $(COST) $(AF) $(N_HIDDEN)
	
plot_classifier:
	gnuplot --persist -e "set xlabel 'Epochs' ; set ylabel 'ERROR' ;plot 'error_c.txt' w l"
	
plot_regresser:
	gnuplot --persist -e "set xlabel 'Epochs' ; set ylabel 'ERROR' ;plot 'error_R.txt' w l"
	
p:
	python3 src/classifier.py
	python3 src/regresser.py
	
clean:
	rm -rf *.txt
	rm -rf src/*.o
	rm -rf src/*.txt
	rm -rf *.so
	rm -rf *.o
	 
	
