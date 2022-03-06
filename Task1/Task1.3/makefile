all:
	g++ -m64 -I"${MKLROOT}/include" -c -fpic audioAPI.cpp -L${MKLROOT}/lib/intel64 -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl
	g++ -m64 -I"${MKLROOT}/include" -shared -o libaudioAPI.so audioAPI.o -L${MKLROOT}/lib/intel64 -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl

run:
	g++ -m64 -I"${MKLROOT}/include" -Wall main.cpp -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_sequential.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm -ldl -g -pthread -L. -laudioAPI -o yourcode.out

clean:
	rm audioAPI.o
	rm libaudioAPI.so
	rm yourcode.out