/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:59 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/11 19:33:54 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

int		check_name(t_vars *ob, char *line)
{
	char	**inst;
	char	*str;

	inst = ft_strsplit(line, "\"\"");
	str = ft_strtrim(inst[0]);
	if (ft_strcmp(NAME_CMD_STRING, str) == 0 && ft_strlen(line) <= PROG_NAME_LENGTH)
	{
		ob->player_name = inst[1];
		printf("name = %s\n", ob->player_name);
		free_split(inst);
		free(str);
		return (0);
	}
	if (ft_strcmp(COMMENT_CMD_STRING, str) == 0 && ft_strlen(line) <= COMMENT_LENGTH)
	{
		ob->comment = inst[1];
		printf("comment = %s\n", ob->comment);
		free_split(inst);
		free(str);
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
		printf("loop label\n");
		if (ft_strcmp(lbl, ob->labels->label) == 0)
			return (-1);
		tmp = ob->labels->next;
	}
	while (lbl[i] != ':')
	{
		if (ft_strchr(LABEL_CHARS, lbl[i]))
			i++;
		else
			return (-1);
	}
	if (tmp != NULL)
		tmp->next = ft_create_elem(lbl);
	ob->bl_label = 1;
	return (0);
}

t_label		*ft_create_elem(char *lbl)
{
	t_label	*elem;

	elem = (t_label*)malloc(sizeof(t_label));
	elem->label = ft_strdup(lbl);
	elem->address = -1;
	elem->next = NULL;
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
		else if (line[0] == '.' && check_name(ob, line) == -1)
		{
			printf("line checked failed\n");
			return (-1);
		}
		else if (line[0] != COMMENT_CHAR && line[0] != '.')
		{
			printf("%s\n", line);
			inst = ft_strsplit(line, " ,");
			printf("split worked\n");
			if (ft_strchr(inst[0], LABEL_CHAR) && get_label(inst[0], ob) == -1)
				return (-1);
			printf("get_op\n");
			ob->op_code = get_op(inst[ob->bl_label]);
			if (ob->op_code == -1 || check_args(op_tab[ob->op_code].num_args,
					   	op_tab[ob->op_code].arg_types, inst, ob) == -1)
				return (-1);
			ob->bl_label = 0;
			free_split(inst);
		}
		printf("line => %s\n", line);
		free(line);
	}
	printf("lexer finished\n");
	close(fd);
	return (1);
}
