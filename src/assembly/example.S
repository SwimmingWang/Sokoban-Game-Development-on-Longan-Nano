.section .text
.globl draw
.type draw, @function
draw:
    addi sp,sp,-4
    sw a0,0(sp)

    li a0,0
    addi sp,sp,-4
    sw ra,0(sp)
    jal LCD_Clear
    lw ra,0(sp)
    addi sp,sp,4

    li a0,20
    li a1,60
    li a2,77 //M
    li a3,0
    li a4,65535
    addi sp,sp,-4
    sw ra,0(sp)
    jal LCD_ShowChar
    lw ra,0(sp)
    addi sp,sp,4

    li a0,30
    li a1,60
    li a2,65 //A
    li a3,0
    li a4,65535
    addi sp,sp,-4
    sw ra,0(sp)
    jal LCD_ShowChar
    lw ra,0(sp)
    addi sp,sp,4

    li a0,40
    li a1,60
    li a2,68 //D
    li a3,0
    li a4,65535
    addi sp,sp,-4
    sw ra,0(sp)
    jal LCD_ShowChar
    lw ra,0(sp)
    addi sp,sp,4

    li a0,50
    li a1,60
    li a2,69 //E 
    li a3,0
    li a4,65535
    addi sp,sp,-4
    sw ra,0(sp)
    jal LCD_ShowChar
    lw ra,0(sp)
    addi sp,sp,4

    li a0,500
    addi sp,sp,-4
    sw ra,0(sp)
    jal delay_1ms
    lw ra,0(sp)
    addi sp,sp,4

    li a0,30
    li a1,80
    li a2,66 //B 
    li a3,0
    li a4,65535
    addi sp,sp,-4
    sw ra,0(sp)
    jal LCD_ShowChar
    lw ra,0(sp)
    addi sp,sp,4

    li a0,40
    li a1,80
    li a2,89 //Y 
    li a3,0
    li a4,65535
    addi sp,sp,-4
    sw ra,0(sp)
    jal LCD_ShowChar
    lw ra,0(sp)
    addi sp,sp,4

    li a0,500
    addi sp,sp,-4
    sw ra,0(sp)
    jal delay_1ms
    lw ra,0(sp)
    addi sp,sp,4
    
    li a0,26
    li a1,100
    li a2,87 //W 
    li a3,0
    li a4,65535
    addi sp,sp,-4
    sw ra,0(sp)
    jal LCD_ShowChar
    lw ra,0(sp)
    addi sp,sp,4

    li a0,36
    li a1,100
    li a2,83 //S 
    li a3,0
    li a4,65535
    addi sp,sp,-4
    sw ra,0(sp)
    jal LCD_ShowChar
    lw ra,0(sp)
    addi sp,sp,4

    li a0,46
    li a1,100
    li a2,89 //Y 
    li a3,0
    li a4,65535
    addi sp,sp,-4
    sw ra,0(sp)
    jal LCD_ShowChar
    lw ra,0(sp)
    addi sp,sp,4

    li a0,500
    addi sp,sp,-4
    sw ra,0(sp)
    jal delay_1ms
    lw ra,0(sp)
    addi sp,sp,4

    li a0,20
    li a1,130
    li a2,60
    li a3,150
    li a4,65535
    addi sp,sp,-4
    sw ra,0(sp)
    jal LCD_DrawRectangle
    lw ra,0(sp)
    addi sp,sp,4

    li a0,500
    addi sp,sp,-4
    sw ra,0(sp)
    jal delay_1ms
    lw ra,0(sp)
    addi sp,sp,4
     
    li a0,20
    li a1,130
    li a2,35
    li a3,150
    li a4,65535
    addi sp,sp,-4
    sw ra,0(sp)
    jal LCD_Fill
    lw ra,0(sp)
    addi sp,sp,4

    li a0,500
    addi sp,sp,-4
    sw ra,0(sp)
    jal delay_1ms
    lw ra,0(sp)
    addi sp,sp,4

    li a0,35
    li a1,130
    li a2,50
    li a3,150
    li a4,65535
    addi sp,sp,-4
    sw ra,0(sp)
    jal LCD_Fill
    lw ra,0(sp)
    addi sp,sp,4

    li a0,500
    addi sp,sp,-4
    sw ra,0(sp)
    jal delay_1ms
    lw ra,0(sp)
    addi sp,sp,4

    li a0,40
    li a1,130
    li a2,60
    li a3,150
    li a4,65535
    addi sp,sp,-4
    sw ra,0(sp)
    jal LCD_Fill
    lw ra,0(sp)
    addi sp,sp,4

    lw a0,0(sp)
    addi a0,a0,1
    addi sp,sp,4
	ret
