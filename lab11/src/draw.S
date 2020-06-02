.section .text
.globl draw
.type draw, @function
draw:
addi sp,sp,-4
sw ra, 0(sp)
# li a0, 20
mv a1, a0
mv a2, a0
andi a2,a2,0x3f
mv a3, a0
mul a3,a3,a3
mul a3,a3,a3
call LCD_DrawCircle
lw ra, 0(sp)
addi sp, sp, 4
ret
