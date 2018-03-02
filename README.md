# Context-Free-Grammar-and-Parsing
CSC173
Project2
Jianyuan Zhong

Collaborator
	Jianyuan Zhong<jzhong9@u.rochester.edu>
	

How to build:
	-go the the directory containing this project
	-type “bash run.sh”


How to test:
	-Run the program
	-Follow the prompt from the program
	-Enter a Random input(up to 64 character)
	The program will:
	 	-First, execute the RDP.c, print out the the resulting Parse tree from Recursive Descent Parsing and evaluate the result if input is an arithmetic expression.
		-Second, execute the TDP.c, print out the the resulting Parse tree from Table Driven Parsing and evaluate the result if input is an arithmetic expression.


Basic Idea
	Follow the Unambiguous Gramma:
		<E >  →  <T > <TT >
		
		<TT > → +- <T > <TT > | e
		
		<T >  →  <F > <FT >
		
		<FT > → */ <F > <FT > | e
		
		<F >  → <N > | ( <E > )
		
		<N >  → <D> <NT >
		
		<NT > → <N > | e
		
		<D>   → 0 | 1 | · · · | 9

	For table Drive, Created a table:

	//    {0 , 1,  2, 3, 4, 5, 6, 7, 8, 9, +, -, *, /, (, ), e}
        /*E*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*T*/
              {4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4},
        /*TT*/
              {1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  3,  1,  1,  1,  1},
        /*F*/
              {8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  -1, -1, -1, -1, 9,  -1},
        /*FT*/
              {5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  6,  7,  5,  5},
        /*N*/
              {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, -1, -1, -1, -1, -1, -1},
        /*NT*/
              {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11, 11, 11, 11, 11, 11},
        /*D*/
              {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, -1, -1, -1, -1, -1, -1},
