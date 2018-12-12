/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:15:46 by jdiaz             #+#    #+#             */
/*   Updated: 2018/12/11 19:47:55 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

#include "op.h"
#include "libft.h"
#include <stdio.h>

typedef struct			s_op
{
	char				*mnemonic;
	int					num_args;
	int					arg_types[3];
	int					op_code;
	int					num_cycles;
	char				*description;
	int					encoding_byte;   //boolean
	int					carry;
}						t_op;

extern t_op		op_tab[17];

typedef struct			s_label
{
	char				*label;
	int					address;
	struct s_label		*next;
}						t_label;

typedef struct			s_param
{
	int					value;
	int					type;
	int					index;
	int					size;   //neccesary?
	struct	s_param		*next;
}						t_param;

typedef struct			s_ins
{
	int					op_code;
	int					arg_types[3];
	int					encoding_value;
	t_param				*params;
	struct s_ins		*next;
}						t_ins;	


typedef struct			s_vars
{
	int					output_fd;
	char				*player_name;
	char				*comment;
	t_label				*labels;
	int					bl_label;
	int					op_code;
	//t_inst				*ins_ls;
}						t_vars;

int		all_whitespace(char *line);

/*assembler*/
int		get_op(char *mnemonic);
int		free_split(char **inst);
/*lexer*/
int		check_name(t_vars *ob, char *line);
int		get_label(char *lbl, t_vars *ob);
t_label	*ft_create_elem(char *lbl);
int		lexer(t_vars *ob, int fd); //1st pass check lexical errors 
/*check_args*/
int		check_args(int num_args, int *arg_types, char **inst, t_vars *ob);
int		check_indirect(char *ind);
int		check_direct(char *direct);   //can be %:alphanumeric or %numeric
int		check_register(char *reg);
/*parser*/
int		count_params(int op_code, int num_args, char **inst, int bl);
int		get_label_address(t_vars *ob, int fd);
/*generator*/
int		print_name(t_vars *ob, char **inst, char *line);
int		print_encoding(t_vars *ob, int op_code, char **params, int num_params);
int		print_inst(t_vars *ob, char **inst, int counter);
int		generator(t_vars *ob, int fd);
int		power_of2(int exp);
int		check_index(int op_code);
int		print_direct(char *param, t_vars *ob, int begin_address);
int		print_indirect(char *param, t_vars *ob, int begin_address);

#endif
