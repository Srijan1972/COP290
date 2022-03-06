all:
	g++ -m64 -I"${MKL_BLAS_PATH}/include" -c -fpic audioAPI.cpp -L${MKL_BLAS_PATH}/lib/intel64 -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl
	g++ -m64 -I"${MKL_BLAS_PATH}/include" -shared -o libaudioAPI.so audioAPI.o -L${MKL_BLAS_PATH}/lib/intel64 -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl
	g++ main.cpp -L. -laudioAPI -o yourcode.out

clean:
	rm audioAPI.o
	rm libaudioAPI.so
	rm yourcode.out