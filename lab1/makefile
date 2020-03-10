all: size_32 size_64

size_32: size.c
	gcc -Wpedantic -Wall -Wextra -Werror -std=c89 size.c -m32 -o size_32

size_64: size.c
	gcc -Wpedantic -Wall -Wextra -Werror -std=c89 size.c -m64 -o size_64

run: all
	@echo "=== Running 32 bit version ==="
	./size_32
	@echo "=== Running 64 bit version ==="
	./size_64
	