gcc -c vector.c
ar rcs libvector.a vector.o
gcc -o staticvector test.c -L./ -l:libvector.a
