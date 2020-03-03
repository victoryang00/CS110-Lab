gcc -c vector.c
ar crv libvector.a vector.c
gcc -o staticvector test.c -L./ -lvector
