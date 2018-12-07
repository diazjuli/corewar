/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:52 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/05 21:04:24 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		check_register(char *reg)
{
	int		reg_num;
	int		i;

	i = 1;
	while (reg[i])
	{
		if (reg[i] >= '0' && reg[i] <= '9' || reg[i] == ',')
			i++;
		else
		{
			printf("error in register lex index %d", i);  
			return (-1);
		}
	}
	reg_num = ft_atoi(reg+1);
	if (reg_num > 16)
	{
		printf("register number too high\n");
		exit (0);
	}
	return (0);
}

int		check_direct(char *direct)   //can be %:alphanumeric or %numeric
{
	int	i;

	i = 1;
	if (direct[1] == ':') //must be a valid label, but we don hav no label list
	{
		//check label?
	}
	else
	{
		while (reg[i]) //not managing comma in between the word
		{
			if (reg[i] >= '0' && reg[i] <= '9' || reg[i] == ',')
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


int	check_indirect(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (reg[i] >= '0' && reg[i] <= '9' || reg[i] == ',')
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

	i = ob->bl_label + 2;
	while (i < num_args)
	{
		if (inst[i][0] == 'r' && (T_REG | arg_types[i] == T_REG))
		{
			check_register(inst[i]);
		}
		else if (inst[i][0] == '%' && (T_DIR | arg_types[i] == T_DIR)
			check_direct(inst[i]);
		else if (inst[i][0] >= '0' && inst[i][0] <= '9' && (T_IND | arg_types[i] == T_IND)
			check_indirect(inst[i]);
		i++;
	}
	return (1);
}
