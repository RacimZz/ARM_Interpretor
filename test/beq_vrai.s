.data
.text
    mov r1,#10
    cmp r1,#10
    beq vrai
faux:
    mov r2,#1
    bal fin_si
vrai:
    mov r3,#99
    affrn r3

fin_si:


bal exit


