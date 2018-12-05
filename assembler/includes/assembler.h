/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:15:46 by jdiaz             #+#    #+#             */
/*   Updated: 2018/12/04 19:51:12 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

#include "op.h"
#include "libft.h"
#include <stdio.h>

typedef struct	s_op
{
	char	*mneumonic;
	int		num_args;
	int		arg_types[3];
	int		op_code;
	int		num_cycles;
	char	*description;
	int		encoding_byte;
	int		carry;
}				t_op;

#endif
