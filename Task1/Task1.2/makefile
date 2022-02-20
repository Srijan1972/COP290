all:
	echo "Choose which way to run by running make mkl, make openblas or make pthread. Run make clean to delete the executables."

mkl:
	g++ -m64  -I"${MKLROOT}/include" matrix_mkl.cpp  -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_sequential.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm -ldl -g -pthread -o mkl.out
	./mkl.out fullyconnected input.txt weight.txt bias.txt output.txt mkl
	rm *.out

openblas:
	g++ matrix_openblas.cpp -lopenblas -lpthread -lm -ldl -o openblas.out
	./openblas.out fullyconnected input.txt weight.txt bias.txt output.txt openblas
	rm *.out

pthread:
	g++ -pthread matrix_pthread.cpp -o pthread.out
	./pthread.out fullyconnected input.txt weight.txt bias.txt output.txt pthread
	rm *.out

clean:
	rm *.out
	clear

gen:
	g++ matrix_gen.cpp
	./a.out
	rm a.out