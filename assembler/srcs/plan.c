//1)first pass parsing
//2)identify name and comment
//separate accordingly (the virtual machine will only consume the program starting
//from the first instruction

//1) #1 op_code byte #2 if encoding flag == 1 encoding byte #3 parameter byte(s)

#include <assembler.h>
/*
fd1 = open(argv[1], RD_ONLY);
char	*newfile(char *str)
fd2 = open(newfile(argv[1], RDWR);
get_next_line
/*1st pass LEXER*/
void	lexer(char *filename) 		  //Iterate through the whole file and check for lexical errors.
									   //(op mnemonics, indirect labels correspond, direct and indirect numbers are numbers
{

}
void	get_structure
int		get_labels                    //create a linked list with the labels and its addresses  ex: %:liv == 15, be counting bytes, -1 error
void	create_word_array?            //create a word array with


/*2nd pass get labels*/
int		check_optable(char *str)      	//check op_table
int		get_op_code(char *instruction) 	//iterate through the op_table and get instruction
void	write_op_byt(char **chararr)    //
int		check_par_typ(char *str)      	// check parameter type with op table
int		get_par_type(char *str)
void	get_encoding_byt(char *str)       //con bitwise operators irlos guardando en un byte
void	write_encoding_byt(int	rnum_dnum_inum)
void	write_bits(t_asm obj, int fd2)

/*3rd pass write bits*/

//convert to a decimal number text file??
open(argv[1])
