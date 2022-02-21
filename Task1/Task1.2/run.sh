make gen
for ((i=0;i<100;i++))
do
make mkl
done
for ((i=0;i<100;i++))
do
make openblas
done
for ((i=0;i<100;i++))
do
make pthread
done

g++ make_data.cpp
./a.out
rm a.out