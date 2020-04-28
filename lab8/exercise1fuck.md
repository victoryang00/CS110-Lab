# s1
hit rate :`0`

## Q1

Step Size * 4 % Cache Size = 0

## Q2

0

## Q3

 increase the stepsize to 128 and increase the repcount as many as possible

# s2
hit rate 0.75

## Q1

Array Size = Cache Size
r+w times = Array Size / 4 / Step Size = 32
r/w times = 64
compulsory misses = Number of blocks = 16
miss rate = compulsory misses / (r/w times) = 0.75

## Q2

-> 1

no compulsory misses.

## Q3

each time fully process a block of data of size Cache Size.
Cache blocking.

# s3
hit rate 0.75

## Q1

Array Size = Cache Size
r times = Array Size / 4 / Step Size = 8

access          set
00 00 0000      0
00 10 0000      2
01 00 0000      0
01 10 0000      2
10 00 0000      0
10 10 0000      2
11 00 0000      0
11 10 0000      2

min: each time is a miss, hit rate = 0/16 = 0
max: only compulsory = 8, lines in a set = 4, hit rate = 8/16 = 0.5

## Q2

Associativity = 1

0.5

each line only has compulsory miss.

1/2=0.5

## Q3

# Loop Ordering and Matrix Multiplication
## a
jki
## b
ikj kij
## c
the way we stride through the matrices
with respect to the innermost loop 
which visits at least 2 row by step size 1 outperform others.


# test of transpose

```bash
root@H4CK5T4T1ON:/mnt/c/Users/14682/Desktop/CS110/newlab/lab8# ./transpose 100 20
Testing naive transpose: 0.004 milliseconds
Testing transpose with blocking: 0.004 milliseconds
root@H4CK5T4T1ON:/mnt/c/Users/14682/Desktop/CS110/newlab/lab8# ./transpose 1000 20
Testing naive transpose: 0.944 milliseconds
Testing transpose with blocking: 0.632 milliseconds
root@H4CK5T4T1ON:/mnt/c/Users/14682/Desktop/CS110/newlab/lab8# ./transpose 2000 20
Testing naive transpose: 19.667 milliseconds
Testing transpose with blocking: 3.36 milliseconds
root@H4CK5T4T1ON:/mnt/c/Users/14682/Desktop/CS110/newlab/lab8# ./transpose 5000 20
Testing naive transpose: 180.88 milliseconds
Testing transpose with blocking: 22.551 milliseconds
root@H4CK5T4T1ON:/mnt/c/Users/14682/Desktop/CS110/newlab/lab8# ./transpose 10000 20
Testing naive transpose: 863.078 milliseconds
Testing transpose with blocking: 107.438 milliseconds
```

```bash
root@H4CK5T4T1ON:/mnt/c/Users/14682/Desktop/CS110/newlab/lab8# ./transpose 10000 50
Testing naive transpose: 868.028 milliseconds
Testing transpose with blocking: 97.576 milliseconds
root@H4CK5T4T1ON:/mnt/c/Users/14682/Desktop/CS110/newlab/lab8# ./transpose 10000 100
Testing naive transpose: 858.035 milliseconds
Testing transpose with blocking: 93.829 milliseconds
root@H4CK5T4T1ON:/mnt/c/Users/14682/Desktop/CS110/newlab/lab8# ./transpose 10000 500
Testing naive transpose: 855.374 milliseconds
Testing transpose with blocking: 104.434 milliseconds
root@H4CK5T4T1ON:/mnt/c/Users/14682/Desktop/CS110/newlab/lab8# ./transpose 10000 1000
Testing naive transpose: 870.747 milliseconds
Testing transpose with blocking: 151.308 milliseconds
root@H4CK5T4T1ON:/mnt/c/Users/14682/Desktop/CS110/newlab/lab8# ./transpose 10000 5000
Testing naive transpose: 866.62 milliseconds
Testing transpose with blocking: 860.822 milliseconds
```