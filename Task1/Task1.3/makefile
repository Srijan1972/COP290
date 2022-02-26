all:
	g++ -m64  -I"${MKLROOT}/include" dnn.cpp  -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_sequential.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm -ldl -g -pthread -o yourcode.out

clean:
	rm yourcode.out