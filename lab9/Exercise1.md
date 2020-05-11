# Exercise 1
1. `_mm_div_ps`
#### Synopsis
```c
	#include <xmmintrin.h>
	__m128 _mm_div_ps (__m128 a, __m128 b)
```
#### ISA
 `divps xmm, xmm`
 CPUID Flags: SSE
#### Description
Divide packed single-precision (32-bit) floating-point elements in a by packed elements in b, and store the results in dst.

2. `_mm_max_epi8`
#### Synopsis
```c
	__m128i _mm_max_epi8 (__m128i a, __m128i b)
	#include <smmintrin.h>
#### Instruction
 pmaxsb xmm, xmm
 CPUID Flags: SSE4.1
#### Description
Compare packed 8-bit integers in a and b, and store packed maximum values in dst.

3. `_mm_srai_epi16`
#### Synopsis
```c
	__m128i _mm_srai_epi16 (__m128i a, int imm8)
	#include <emmintrin.h>
```
#### Instruction
 psraw xmm, imm
 CPUID Flags: SSE2
#### Description
Shift packed 16-bit integers in a right by imm8 while shifting in sign bits, and store the results in dst.



4. `_mm_sra_epi16`
#### Synopsis
```c
#include <emmintrin.h>
__m128i _mm_sra_epi16 (__m128i a, __m128i count)
````
#### Instruction
 psraw xmm, xmm
 CPUID Flags: SSE2
#### Description
Shift packed 16-bit integers in a right by count while shifting in sign bits, and store the results in dst.
