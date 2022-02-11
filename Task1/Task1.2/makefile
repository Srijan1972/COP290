all:
	g++ -m64  -I"${MKLROOT}/include" main.cpp  -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_sequential.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm -ldl -o yourcode.out
	./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt output.txt mkl