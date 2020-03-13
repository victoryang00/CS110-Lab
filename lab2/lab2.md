# Ex1
1.  `.data` global data section.

    `.word` store 32-bit comma separated words
    
    `.text` code section
2.  34

    9th fib num
3.  `0x10000010`
4.  `t3 -> 0xD` after `lw t3, 0(t3)` runs 
# Ex2
1.  `t0`
2.  arrays: `t1`,`t2`

    elements: `t4`,`t6`
3.  ```
    loop:
        slli t3, t0, 2
        add t4, t1, t3
        lw t5, 0(t4)
        beq t5, x0, exit
        add t6, t2, t3
        sw t5, 0(t6)
        addi t0, t0, 1
        jal x0, loop
    exit:```
4.  `t3=t0*4, t4=t1+t3`

    `offset=k*4, addr=start+offset`
5.  ```
    .text                           .text
    main:                           main:
        addi t0, x0, 0                  addi t0, x0, 0
        la t1, source                   la t1, source
        la t2, dest                     la t2, dest
    loop:                           loop:
        slli t3, t0, 2                  slli t3, t0, 2
        add t4, t1, t3                  add t4, t1, t3
        lw t5, 0(t4)                    lw t5, 0(t4)
                               =>       add t5, t5, t5
        beq t5, x0, exit                beq t5, x0, exit
        add t6, t2, t3                  add t6, t2, t3
        sw t5, 0(t6)                    sw t5, 0(t6)
        addi t0, t0, 1         =>       addi t0, t0, 2
        jal x0, loop                    jal x0, loop
    exit:                           exit:
        jal ra, print_lists             jal ra, print_lists
        addi a0, x0, 10                 addi a0, x0, 10
        add a1, x0, x0                  add a1, x0, x0
        ecall # Terminate ecall         ecall # Terminate ecall
    ```

                      
                      
                                   
                                  
                                
                      
                                   
                                   
                                 
                                     
                                   
                                 
                                   
                                 
                      
                                        
                                    
                                   
                                            