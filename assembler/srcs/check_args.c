/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:52 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/13 01:06:17 by jcruz-y-         ###   ########.fr       */
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
int		check_arglabel(char *lbl)
{
	int		i;

	i = 2;
	while (lbl[i])
	{
		if (!ft_strchr(LABEL_CHARS, lbl[i]))
			return (-1);
		i++;
	}
	return (1);
}

int		check_direct(char *direct)   //can be %:alphanumeric or %numeric
{
	int	i;

	i = 1;
	if (direct[1] == LABEL_CHAR) //must be a valid label, but we don hav no label list
	{
		if (check_arglabel(direct) == -1)
			return (-1);
		//check label?

		//continue?
	}
	else
	{
		while (direct[i]) 
		{
			if (((direct[i] >= '0' && direct[i] <= '9') || direct[1] == '-') ||
			 direct[ft_strlen(direct) - 1] == SEPARATOR_CHAR)
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
		if (ind[i] == LABEL_CHAR && check_arglabel(ind) == -1)
			return (-1);
		if (((ind[i] >= '0' && ind[i] <= '9') || ind[0] == '-') || ind[ft_strlen(ind) - 1] == SEPARATOR_CHAR)
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
	int		j;

	i = ob->bl_label + 1;
	j = 0;
	//printf("check args i = %d\n", i);
	while (i < (num_args + ob->bl_label + 1))
	{
		if (inst[i][0] == 'r' && ((T_REG & arg_types[j]) == T_REG))
		{
			printf("args inst[%d] = %s\n", i, inst[i]);
			check_register(inst[i]);
		}
		else if (inst[i][0] == DIRECT_CHAR && (((T_DIR & arg_types[j]) != T_DIR) || check_direct(inst[i]) == -1))
			return (-1);
		else if (inst[i][0] >= '0' && inst[i][0] <= '9' && (((T_IND & arg_types[j]) != T_IND) ||
		check_indirect(inst[i]) == -1))   //check for indirect label :likethis
			return (-1);
		i++;
		j++;
	}
	return (1);
}
