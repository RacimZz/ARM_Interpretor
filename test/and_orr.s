.data
.text

mov r0,#10 @1010
mov r1,#9 @1001

and r2,r0,r1 @ = 1000 = 8

mov r3,#14 @1110
mov r4,#9 @1001

orr r5,r3,r4 @ = 1111 = 15

bal exit


