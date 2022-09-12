// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

//i=0
//j=0
//ptr=SCREEN
//val = 0
//LOOP:
//if KBD == 0 GOTO WHITE
//val=-1
//WHITE:
//	val=0
//LOOP2:
//		if i-32=0 GOTO CHANGECOL
//		A[ptr]=val
//		ptr=ptr+1
//		CHANGECOL:
//			if 256-j == 0 GOTO END		
//			j=j+1
//			GOTO LOOP2
//	END:
//	GOTO LOOP



@KBD
D=A
@press
M=D

@i
M=0
@j
M=1
@val
M=0

(LOOP)
	@SCREEN
	D=A
	@ptr
	M=D
	
	@press
	A=M
	D=M
	
	@WHITE
	D;JEQ
	
	@val			//for black
	M=-1
	@MAIN
	0;JMP

	(WHITE)
	@val
	M=0
	@MAIN
	0;JMP

	//drawing loop
	(MAIN)
	@i
	D=M
	@32
	D=A-D
	@CHGCOL
	D;JEQ
	@val
	D=M
	@ptr
	A=M
	M=D
	
	@ptr
	M=M+1			//ptr+1
	@i
	M=M+1
	@MAIN
	0;JMP

	(CHGCOL)
	@j
	D=M
	@256
	D=A-D
	@END
	D;JEQ
	@j
	M=M+1
	@i
	M=0
	@MAIN
	0;JMP

	(END)
	@i
	M=0
	@j
	M=1
	@LOOP	
	0;JMP
	
			
