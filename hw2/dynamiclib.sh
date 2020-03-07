gcc -shared -fPIC -o libvector.so vector.c
gcc -o dynamicvector test.c ./libvector.so
