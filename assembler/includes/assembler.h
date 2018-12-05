/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:15:46 by jdiaz             #+#    #+#             */
/*   Updated: 2018/12/04 21:57:00 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

#include "op.h"
#include "libft.h"
#include <stdio.h>

typedef struct			s_label
{
	char			*label;
	int				address;
	struct s_label	*next;
}						t_label;

typedef struct			s_op
{
	char	*mneumonic;
	int		num_args;
	int		arg_types[3];
	int		op_code;
	int		num_cycles;
	char	*description;
	int		encoding_byte;
	int		carry;
}						t_op;

typedef struct	s_asm
{
	int		output_fd;
	int		input_fd;
	t_label	*labels;

}				t_asm;

#endif
