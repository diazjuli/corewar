/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:52 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/11 19:28:50 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

int		check_register(char *reg)
{
	int		reg_num;
	int		i;

	i = 1;
	while (reg[i])
	{
		if ((reg[i] >= '0' && reg[i] <= '9') || reg[ft_strlen(reg) - 1] == SEPARATOR_CHAR)
			i++;
		else
		{
			printf("error in register lex index %d", i);  
			return (-1);
		}
	}
	reg_num = ft_atoi(reg+1);
	if (reg_num > REG_NUMBER)
	{
		printf("register number too high\n");
		exit (0);
	}
	printf("register number = %d\n", reg_num);
	return (0);
}

int		check_direct(char *direct)   //can be %:alphanumeric or %numeric
{
	int	i;

	i = 1;
	if (direct[1] == LABEL_CHAR) //must be a valid label, but we don hav no label list
	{
		//check label?
		//continue?
	}
	else
	{
		while (direct[i]) 
		{
			if ((direct[i] >= '0' && direct[i] <= '9') || direct[ft_strlen(direct) - 1] == SEPARATOR_CHAR)
				i++;
			else
			{
				printf("error in direct lex index %d", i);  
				return (-1);
			}
		}
	}
	return (0);
}


int	check_indirect(char *ind)
{
	int	i;

	i = 0;
	while (ind[i])
	{
		if ((ind[i] >= '0' && ind[i] <= '9') || ind[ft_strlen(ind) - 1] == SEPARATOR_CHAR)
			i++;
		else
		{
			printf("error in indirect lex index %d", i);
			return (-1);
		}
	}
	return (0);
}
	

int		check_args(int num_args, int *arg_types, char **inst, t_vars *ob)
{
	int		i;

	i = ob->bl_label + 1;
	printf("check args i = %d\n", i);
	while (i < num_args)
	{
		if (inst[i][0] == 'r' && ((T_REG & arg_types[i]) == T_REG))
		{
			printf("args inst[%d] = %s\n", i, inst[i]);
			check_register(inst[i]);
		}
		else if (inst[i][0] == DIRECT_CHAR && ((T_DIR & arg_types[i]) == T_DIR))
			check_direct(inst[i]);
		else if (inst[i][0] >= '0' && inst[i][0] <= '9' && ((T_IND & arg_types[i]) == T_IND))
			check_indirect(inst[i]);
		i++;
	}
	return (1);
}
