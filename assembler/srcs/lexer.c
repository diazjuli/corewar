/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:59 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/10 15:30:41 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		check_name(char **inst, t_vars *ob, char *line)
{
	if (strcmp(NAME_CMD_STRING, inst[0]) == 0 && ft_strlen(line) <= PROG_NAME_LENGTH)
		ob->name = inst[1];
	if (strcmp(COMMENT_CMD_STRING, inst[0] == 0 && ft_strlen(line) <= COMMENT_LENGTH))
		ob->comment = inst[1];
	else
		return (-1);
}

int		get_label(char *lbl, t_vars *ob)
{
	t_label	*tmp;
	int		i;
	
	tmp = op->labels->label;
	i = 0;
	while (ob->labels->label)
	{
		if (strcmp(lbl, ob->labels->label) == 0)
			tmp = ob->labels->next;
		else
			return (-1);
	}
	while (lbl[i])
	{
		if (ft_strchr(LABEL_CHARS, lbl[i]))
			i++;
		else
			return (-1);
	}
	ob->labels->label = lbl;
	ob->bl_label = 1;
	return (0);
}

int	free_split(char **inst, int numwords)
{
	int	i;

	i = 0;
	while (i < numwords)
	{
		free(inst[i])
		i++;
	}
	free(inst);
	return (0);
}	

int		lexer(t_vars *ob, int fd) //1st pass check lexical errors 
{
	char	*line;
	char	**inst;

	while ((get_next_line(fd, &line) > 0)) 
	{
		if (line[0] == COMMENT_CHAR) 
			continue;
		inst = ft_strplit(line, ' ');
		if (line[0] == '.' && check_name(inst, ob, line) != -1)
			return (-1);
		else
		{
			if (ft_strchr(inst[0], LABEL_CHAR) && get_label(inst[0], ob) == -1)
				return (-1);
			ob->op_code = get_op(inst[ob->bl_label]);
			if (ob->op_code == -1 || check_args(op_tab[ob->op_code][1],
						op_tab[ob->op_code][2],inst ,ob) == -1)
				return (-1);
			ob->bl_label = 0;
		}
		free_split(inst, ft_num_words(line));
		free(line);
	}
	close(fd);
	return (1);
}
