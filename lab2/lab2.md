


```bash
 yiweiyang  (e) base  ~  Downloads  lab2  1  sudo gdb hello
GNU gdb (GDB) 8.3
Copyright (C) 2019 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-apple-darwin19.0.0".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from hello...
Reading symbols from /Users/yiweiyang/Downloads/lab2/hello.dSYM/Contents/Resources/DWARF/hello...
(gdb) si
The program is not being run.
(gdb) r
Starting program: /Users/yiweiyang/Downloads/lab2/hello 
[New Thread 0xc03 of process 5761]
[New Thread 0xf03 of process 5761]
warning: unhandled dyld version (16)
Thanks for waddling through this program. Have a nice day.[Inferior 1 (process 5761) exited normally]
(gdb) b main
Breakpoint 1 at 0x100000f05: file hello.c, line 5.
(gdb) r
Starting program: /Users/yiweiyang/Downloads/lab2/hello 
[New Thread 0xc0b of process 5765]
[New Thread 0x1503 of process 5765]
warning: unhandled dyld version (16)

Thread 2 hit Breakpoint 1, main (argc=1, argv=0x7ffeefbff9b8) at hello.c:5
5	  int i, *p, count = 0;
(gdb) b *p
Breakpoint 2 at 0x7ffeefbff9a8
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x0000000100000f05 in main at hello.c:5
	breakpoint already hit 1 time
2       breakpoint     keep y   0x00007ffeefbff9a8 
(gdb) watch *p
Hardware watchpoint 3: *p
(gdb) si
6	  p = &count;
(gdb) info p
Ambiguous info command "p": pretty-printer, probes, proc, program.
(gdb) info *p
Undefined info command: "*p".  Try "help info".
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x0000000100000f05 in main at hello.c:5
	breakpoint already hit 1 time
2       breakpoint     keep y   0x00007ffeefbff9a8 
3       hw watchpoint  keep y                      *p
(gdb) si
0x0000000100000f10	6	  p = &count;
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x0000000100000f05 in main at hello.c:5
	breakpoint already hit 1 time
2       breakpoint     keep y   0x00007ffeefbff9a8 
3       hw watchpoint  keep y                      *p
(gdb) bf
Undefined command: "bf".  Try "help".
(gdb) bt
#0  0x0000000100000f10 in main (argc=1, argv=0x7ffeefbff9b8) at hello.c:6
(gdb) info eax
Undefined info command: "eax".  Try "help info".
(gdb) info registers eax
eax            0xefbff97c          -272631428
(gdb) info registers ebx
ebx            0x0                 0
(gdb) info registers ecx
ecx            0xefbffa78          -272631176
(gdb) info main
Undefined info command: "main".  Try "help info".
(gdb) info line
Line 6 of "hello.c" starts at address 0x100000f0c <main+22>
   and ends at 0x100000f14 <main+30>.
(gdb) info function
All defined functions:

File hello.c:
3:	int main(int, char **);

Non-debugging symbols:
0x0000000100000000  _mh_execute_header
(gdb) si
8	  for (i = 0; i < 10; i++) {
(gdb) info function
All defined functions:

File hello.c:
3:	int main(int, char **);

Non-debugging symbols:
0x0000000100000000  _mh_execute_header
(gdb) info register eax
eax            0xefbff97c          -272631428
(gdb) info register ebx
ebx            0x0                 0
(gdb) info register ax
ax             0xf97c              -1668
(gdb) info register rbx
rbx            0x0                 0
(gdb) info register rax
rax            0x7ffeefbff97c      140732920756604
(gdb) info f
Stack level 0, frame at 0x7ffeefbff9a0:
 rip = 0x100000f14 in main (hello.c:8); saved rip = 0x7fff7107e7fd
 source language c.
 Arglist at 0x7ffeefbff990, args: argc=1, argv=0x7ffeefbff9b8
 Locals at 0x7ffeefbff990, Previous frame's sp is 0x7ffeefbff9a0
 Saved registers:
  rbp at 0x7ffeefbff990, rip at 0x7ffeefbff998
(gdb) info locals
i = 1
p = 0x7ffeefbff97c
count = 0
(gdb) info args
argc = 1
argv = 0x7ffeefbff9b8
(gdb) si
8	  for (i = 0; i < 10; i++) {
(gdb) si
8	  for (i = 0; i < 10; i++) {
(gdb) si
0x0000000100000f34	8	  for (i = 0; i < 10; i++) {
(gdb) info args
argc = 1
argv = 0x7ffeefbff9b8
(gdb) info locals
i = 0
p = 0x7ffeefbff97c
count = 0
(gdb) si
9	  	(*p)++;	//Do you understand this line of code and all the other permutations of the operators? ;)
(gdb) info locals
i = 0
p = 0x7ffeefbff97c
count = 0
(gdb) si
0x0000000100000f21	9	  	(*p)++;	//Do you understand this line of code and all the other permutations of the operators? ;)
(gdb) si
9	  	(*p)++;	//Do you understand this line of code and all the other permutations of the operators? ;)
(gdb) si
0x0000000100000f26	9	  	(*p)++;	//Do you understand this line of code and all the other permutations of the operators? ;)
(gdb) si
0x0000000100000f2a	9	  	(*p)++;	//Do you understand this line of code and all the other permutations of the operators? ;)
(gdb) si

Thread 2 hit Hardware watchpoint 3: *p

Old value = 0
New value = 1
main (argc=1, argv=0x7ffeefbff9b8) at hello.c:8
8	  for (i = 0; i < 10; i++) {
(gdb) si
8	  for (i = 0; i < 10; i++) {
(gdb) si
0x0000000100000f34	8	  for (i = 0; i < 10; i++) {
(gdb) si
9	  	(*p)++;	//Do you understand this line of code and all the other permutations of the operators? ;)
(gdb) si
0x0000000100000f21	9	  	(*p)++;	//Do you understand this line of code and all the other permutations of the operators? ;)
(gdb) si
9	  	(*p)++;	//Do you understand this line of code and all the other permutations of the operators? ;)
(gdb) si
0x0000000100000f26	9	  	(*p)++;	//Do you understand this line of code and all the other permutations of the operators? ;)
(gdb) si
0x0000000100000f2a	9	  	(*p)++;	//Do you understand this line of code and all the other permutations of the operators? ;)
(gdb) si

Thread 2 hit Hardware watchpoint 3: *p

Old value = 1
New value = 2
main (argc=1, argv=0x7ffeefbff9b8) at hello.c:8
8	  for (i = 0; i < 10; i++) {
(gdb) si
8	  for (i = 0; i < 10; i++) {
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) n
Program not restarted.
(gdb) c
Continuing.

Thread 2 hit Hardware watchpoint 3: *p

Old value = 2
New value = 3
main (argc=1, argv=0x7ffeefbff9b8) at hello.c:8
8	  for (i = 0; i < 10; i++) {
(gdb) c
Continuing.

Thread 2 hit Hardware watchpoint 3: *p

Old value = 3
New value = 4
main (argc=1, argv=0x7ffeefbff9b8) at hello.c:8
8	  for (i = 0; i < 10; i++) {
(gdb) c
Continuing.

Thread 2 hit Hardware watchpoint 3: *p

Old value = 4
New value = 5
main (argc=1, argv=0x7ffeefbff9b8) at hello.c:8
8	  for (i = 0; i < 10; i++) {
(gdb) c
Continuing.

Thread 2 hit Hardware watchpoint 3: *p

Old value = 5
New value = 6
main (argc=1, argv=0x7ffeefbff9b8) at hello.c:8
8	  for (i = 0; i < 10; i++) {
(gdb) c
Continuing.

Thread 2 hit Hardware watchpoint 3: *p

Old value = 6
New value = 7
main (argc=1, argv=0x7ffeefbff9b8) at hello.c:8
8	  for (i = 0; i < 10; i++) {
(gdb) c
Continuing.

Thread 2 hit Hardware watchpoint 3: *p

Old value = 7
New value = 8
main (argc=1, argv=0x7ffeefbff9b8) at hello.c:8
8	  for (i = 0; i < 10; i++) {
(gdb) c
Continuing.

Thread 2 hit Hardware watchpoint 3: *p

Old value = 8
New value = 9
main (argc=1, argv=0x7ffeefbff9b8) at hello.c:8
8	  for (i = 0; i < 10; i++) {
(gdb) c
Continuing.

Thread 2 hit Hardware watchpoint 3: *p

Old value = 9
New value = 10
main (argc=1, argv=0x7ffeefbff9b8) at hello.c:8
8	  for (i = 0; i < 10; i++) {
(gdb) c
Continuing.

Watchpoint 3 deleted because the program has left the block in
which its expression is valid.
0x00007fff7107e7fd in ?? ()
(gdb) c
Continuing.
Thanks for waddling through this program. Have a nice day.[Inferior 1 (process 5765) exited normally]
(gdb) c
The program is not being run.
(gdb) r
Starting program: /Users/yiweiyang/Downloads/lab2/hello 
[New Thread 0x1087 of process 5774]
[New Thread 0x1703 of process 5774]
warning: unhandled dyld version (16)
[2]  + 5709 suspended (tty output)  sudo gdb hello
```