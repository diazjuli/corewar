/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:52 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/13 17:10:51 by jdiaz            ###   ########.fr       */
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
		if ((reg[i] >= '0' && reg[i] <= '9'))
			i++;
		else
		{
			printf("error in register lex index %d\n", i);  
			return (-1);
		}
	}
	reg_num = ft_atoi(reg + 1);
	if (reg_num > REG_NUMBER || reg_num <= 0)
	{
		printf("register number out of range\n");
		return (-1);
	}
	return (0);
}
int		check_arglabel(char *lbl)
{
	int		i;

	i = 1;
	if (lbl[i] == '\0')
		return (-1);
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
	if (direct[1] == LABEL_CHAR)
	{
		if (check_arglabel(direct + 1) == -1)
			return (-1);
	}
	else
	{
		if (direct[i] == '-')
				i++;
		if (direct[i] == '\0')
			return (-1);
		while (direct[i]) 
		{
			if (direct[i] < '0' || direct[i] > '9')
			{
				printf("error in direct lex index %d\n", i);  
				return (-1);
			}
			i++;
		}
	}
	return (0);
}


int	check_indirect(char *ind)
{
	int	i;

	i = 0;
	if (ind[i] == LABEL_CHAR)
		return (check_arglabel(ind));
	if (ind[i] == '-')
		i++;
	while (ind[i])
	{
		if (ind[i] >= '0' && ind[i] <= '9')
			i++;
		else
		{
			printf("error in indirect lex index %d\n", i);
			return (-1);
		}
	}
	return (0);
}

int check_args(int num_args, int *arg_types, char **inst, t_vars *ob)
{
	int i;
	int j;

	i = ob->bl_label + 1;
	j = 0;
	while (inst[i] && i < num_args + ob->bl_label + 1)
	{
		if (inst[i][0] == 'r')
		{
			if ((T_REG & arg_types[j]) != T_REG || check_register(inst[i]) == -1)
				return (-1);
		}
		else if (inst[i][0] == DIRECT_CHAR)
		{
			if ((T_DIR & arg_types[j]) != T_DIR || check_direct(inst[i]) == -1)
				return (-1);
		}
		else
		{
			if ((T_IND & arg_types[j]) != T_IND || check_indirect(inst[i]) == -1)
				return (-1);
		}
		i++;
		j++;
	}
	if (i != num_args + ob->bl_label + 1 || (inst[i] != NULL && inst[i][0]
				!= COMMENT_CHAR))
		return (-1);
	return (1);
}
