gcc -c vector.c -Wpedantic -Wall -Wextra -Werror -std=c89
ar crv libvector.a vector.c
gcc -o staticvector test.c -L./ -lvector -Wpedantic -Wall -Wextra -Werror -std=c89
