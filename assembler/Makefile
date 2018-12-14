# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/15 19:22:08 by jdiaz             #+#    #+#              #
#    Updated: 2018/12/13 22:37:44 by jdiaz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

### PATH ###
SRCS_PATH = srcs/
OBJ_PATH  = obj/
LIBFT_PATH = ../libft/

FLAGS = -Wall -Werror -Wextra
INC = -I ./includes/ -I ./$(LIBFT_PATH)includes/

ASM_SRC = srcs/generator.c srcs/parser.c srcs/check_args.c srcs/lexer.c \
		  srcs/assembler.c srcs/op.c srcs/tools.c srcs/get_name.c
		  
ASM_OBJ = generator.o parser.o check_args.o assembler.o op.o lexer.o tools.o \
		  get_name.o

all: $(NAME)

$(NAME):
	@make -C $(LIBFT_PATH)
	@gcc $(FLAGS) $(INC) -c $(ASM_SRC)
	@gcc -o $(NAME) $(ASM_OBJ) $(LIBFT_PATH)libft.a
	@echo "Compiled asm"

clean:
	@make -C $(LIBFT_PATH)/ clean
	@/bin/rm -rf $(ASM_OBJ)
	@echo "Cleaned $(ASM_OBJ)"

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@/bin/rm -rf $(NAME)
	@echo "Cleaned $(NAME)"

re: fclean all

de: fclean 
	make -C $(LIBFT_PATH)
	gcc -g -o $(NAME) $(FLAGS) $(INC) $(ASM_SRC) $(LIBFT_PATH)libft.a
	echo "Compiled asm"
	
se: fclean 
	make -C $(LIBFT_PATH)
	gcc -g -o $(NAME) -fsanitize=address $(FLAGS) $(INC) $(ASM_SRC) $(LIBFT_PATH)libft.a
	echo "Compiled asm"

test: fclean
	make -C $(LIBFT_PATH)
	gcc -g  -o test $(FLAGS) $(INC) srcs/test.c $(LIBFT_PATH)libft.a
	echo "Compiled test"

te:
	rm new_file.cor
	./asm ex.s
	./sm42 ex.s
	hexdump new_file.cor
	hexdump ex.cor

.PHONY: all, clean, fclean, re, de
