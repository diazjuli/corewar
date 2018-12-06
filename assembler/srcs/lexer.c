/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:59 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/05 21:04:54 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		check_name(char *line, t_vars *ob)
{
	if (line[1] == 'n')
		check_name(line, ob);    //check and get name into ob
	else if (line[1] == 'c')
		check_comment(line, ob) //check and get comment into ob
}

int		get_label(char *label, t_vars *ob)
{
	int		i;

	i = 0;
	if (line[])

}


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

int		check_args(int num_args, int *arg_types, char **inst, t_vars *ob)
{
	int		i;

	i = 0;
	while (i < num_args)
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
	return (1);
}

int		lexer(t_vars *ob, int fd) //1st pass check lexical errors 
{
	char	*line;
	char	**inst;

	while ((get_next_line(fd, &line) > 0)) 
	{
		if (line[0] == '#')
			continue;
		if (line[0] == '.' && check_name(line, ob) != -1)
			return (-1);
		else
		{
			inst = ft_strplit(line, ' ');
			if (ft_strchr(inst[0], ":") && get_label(inst[0], ob) == -1)
				return (-1);
			ob->op_code = get_op(inst[ob->label]);
			if (ob->op_code == -1 || check_args(op_tab[ob->op_code][1],
						op_tab[ob->op_code][2],inst ,ob) == -1)
				return (-1);
		}
		free(line);
		free_split(inst);
	}
	close(fd);
	return (1);
}
