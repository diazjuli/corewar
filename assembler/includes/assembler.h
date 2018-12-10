/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:15:46 by jdiaz             #+#    #+#             */
/*   Updated: 2018/12/10 15:48:31 by jdiaz            ###   ########.fr       */
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

#endif
