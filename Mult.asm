// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// pseudo code
// x = R0
// y = R1
// if x-y > 0: sml = y ;num = x else sml=x; num=y
// i = 0
// sum = 0

//LOOP:
//	if sml-i == 0 GOTO STOP
// 	sum = sum+num
//	i++
// STOP:
//	R2 = sum
//	
//END:
//	GOTO END
//start

@R0
D=M
@x
M=D				
@R2
M=0

@R1
D=M
@y
M=D				


@x
D=D-M				
@YSMALLER
D;JLE

@x				
D=M
@sml
M=D
@y
D=M
@num
M=D

(YSMALLER)			
@y
D=M
@sml
M=D
@x
D=M
@num
M=D

@i
M=0
@sum
M=0


(LOOP)
@sml
D=M
@i
D=D-M			
@STOP
D;JEQ

@num
D=M
@sum
M=D+M				

@i			
M=M+1
@LOOP
0;JMP

(STOP)
@sum
D=M
@R2
M=D			

(END)
@END
0;JMP
