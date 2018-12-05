# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/15 19:22:08 by jdiaz             #+#    #+#              #
#    Updated: 2018/12/04 20:30:42 by jdiaz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

### PATH ###
SRCS_PATH = srcs/
OBJ_PATH  = obj/
LIBFT_PATH = ../libft/

FLAGS = -Wall -Werror -Wextra
INC = -I ./includes/ -I ./$(LIBFT_PATH)includes/

ASM_SRC = srcs/assembler.c srcs/op.c
		  
ASM_OBJ = assembler.o op.o

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

.PHONY: all, clean, fclean, re
