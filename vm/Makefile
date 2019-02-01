# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/15 19:22:08 by jdiaz             #+#    #+#              #
#    Updated: 2019/01/31 15:08:16 by jcruz-y-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

### PATH ###
SRCS_PATH = srcs/
OBJ_PATH  = obj/
LIBFT_PATH = ../libft/

FLAGS = -Wall -Werror -Wextra
INC = -I ./includes/ -I ./$(LIBFT_PATH)

VM_SRC = srcs/errorh.c srcs/flags.c srcs/init_objs.c \
srcs/players_utils.c srcs/players.c srcs/vm.c srcs/arena.c
		  
VM_OBJ =  vm.o errorh.o flags.o init_objs.o players_utils.o players.o arena.o

all: $(NAME)

$(NAME):
	@make -C $(LIBFT_PATH)
	@gcc $(FLAGS) $(INC) -c $(VM_SRC)
	@gcc -o $(NAME) $(VM_OBJ) $(LIBFT_PATH)libft.a
	@echo "Compiled corewar"

clean:
	@make -C $(LIBFT_PATH)/ clean
	@/bin/rm -rf $(VM_OBJ)
	@echo "Cleaned $(VM_OBJ)"

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@/bin/rm -rf $(NAME)
	@echo "Cleaned $(NAME)"

re: fclean all

de: fclean 
	make -C $(LIBFT_PATH)
	gcc -g -o $(NAME) $(FLAGS) $(INC) $(VM_SRC) $(LIBFT_PATH)libft.a
	echo "Compiled corewar"
	
se: fclean 
	make -C $(LIBFT_PATH)
	gcc -g -o $(NAME) -fsanitize=address $(FLAGS) $(INC) $(VM_SRC) $(LIBFT_PATH)libft.a
	echo "Compiled corewar"

test: fclean
	make -C $(LIBFT_PATH)
	gcc -g  -o test $(FLAGS) $(INC) srcs/test.c $(LIBFT_PATH)libft.a
	echo "Compiled test"

FILE = _

.PHONY: all, clean, fclean, re, de
