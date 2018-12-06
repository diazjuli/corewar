/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:52 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/05 18:31:21 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		check_register(char *r_arg)
{
	int		reg_num;

	reg_num = ft_atoi([i++]);
	if (reg_num > 16)
	{
		printf("incorrect register number\n");
		exit (0);
	}
}

int		check_args(char **line, t_vars *ob)
{
	int		i;

	i = 0;
	while (i < ob->num_args)
	{
		if (line[i][0] == 'r' && ob->)
		{
			check_register(line[i++]);
		}
		else if (line[i][0] == '%')
			check_direct(line[i++]);
		else if (line[i][0] >= '0' && 0line[i][0] <= '9')
			check_indirect(line[i++]);
	}
}
