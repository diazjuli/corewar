/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:59 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/10 19:52:26 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		check_name(char **inst, t_vars *ob, char *line)
{
	if (strcmp(NAME_CMD_STRING, inst[0]) == 0 && ft_strlen(line) <= PROG_NAME_LENGTH)
	{
		ob->player_name = inst[1];
		return (0);
	}
	if (strcmp(COMMENT_CMD_STRING, inst[0]) == 0 && ft_strlen(line) <= COMMENT_LENGTH)
	{
		ob->comment = inst[1];
		return (0);
	}
	else
		return (-1);
}

int		get_label(char *lbl, t_vars *ob)
{
	t_label	*tmp;
	int		i;
	
	tmp = ob->labels;
	i = 0;
	while (tmp && tmp->next)
	{
		if (ft_strcmp(lbl, ob->labels->label) == 0)
			return (-1);
		tmp = ob->labels->next;
	}
	while (lbl[i])
	{
		if (ft_strchr(LABEL_CHARS, lbl[i]))
			i++;
		else
			return (-1);
	}
	tmp->next = ft_create_elem(lbl)
	ob->bl_label = 1;
	return (0);
}

t_label		*ft_create_elem(char *lbl)
{
	t_label	*elem;

	elem = (t_label*)malloc(sizeof(t_label));
	elem->label = lbl;
	elem->address = NULL;
	return (elem);
}

int		lexer(t_vars *ob, int fd) //1st pass check lexical errors 
{
	char	*line;
	char	**inst;

	while ((get_next_line(fd, &line) > 0)) 
	{
		if (line[0] == COMMENT_CHAR) 
			continue;
		inst = ft_strsplit(line, ' ');
		if (line[0] == '.' && check_name(inst, ob, line) != -1)
			return (-1);
		else
		{
			if (ft_strchr(inst[0], LABEL_CHAR) && get_label(inst[0], ob) == -1)
				return (-1);
			ob->op_code = get_op(inst[ob->bl_label]);
			if (ob->op_code == -1 || check_args(op_tab[ob->op_code].num_args,
					   	op_tab[ob->op_code].arg_types, inst, ob) == -1)
				return (-1);
			ob->bl_label = 0;
		}
		free_split(inst, ft_num_words(line));
		free(line);
	}
	close(fd);
	return (1);
}
