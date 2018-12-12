/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:59 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/12 14:41:52 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

int		check_name(t_vars *ob, char *line)
{
	char	**inst;
	char	*str;

	inst = ft_strsplit(line, "\"\"\"");
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

int		get_label(char *lbl, t_vars *ob, char ** inst)
{
	t_label	*tmp;
	int		i;
	t_label	*elem;
	
	tmp = ob->labels;
	i = 0;
	printf("get label\n");
	while (tmp && tmp->next)
	{
		printf("loop label\n");
		if (ft_strcmp(lbl, tmp->label) == 0)
			return (-1);
		tmp = tmp->next;
	}
	while (lbl[i] != ':')
	{
		if (ft_strchr(LABEL_CHARS, lbl[i]))
			i++;
		else
			return (-1);
	}
	elem = ft_create_elem(lbl);
	if (ob->labels == NULL)
		ob->labels = elem;
	if (tmp != NULL)
		tmp->next = elem;
	if (inst[1])
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

int		empty_line(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == COMMENT_CHAR)
			return (-1);
		if (str[i] != ' ' && str[i] != '	' )
			return (1);
		i++;
	}
	return (-1);
}



int		lexer(t_vars *ob, int fd) //1st pass check lexical errors 
{
	char	*line;
	char	**inst;

	while ((get_next_line(fd, &line) > 0)) 
	{
		if (line[0] == COMMENT_CHAR || empty_line(line) == -1 ) 
			continue;
		else if (line[0] == '.' && check_name(ob, line) == -1)
			return (-1);
		else if (line[0] != COMMENT_CHAR && line[0] != '.' && empty_line(line) == 1)
		{
			inst = ft_strsplit(line, " ,	");
			if (ft_strchr(inst[0], LABEL_CHAR) && get_label(inst[0], ob, inst) == -1)
				return (-1);
			if (inst[1] && (get_op(inst[ob->bl_label], ob) == -1 || check_args(op_tab[ob->op_code].num_args,
						   	op_tab[ob->op_code].arg_types, inst, ob) == -1))
				return (-1);
			ob->bl_label = 0;
			free_split(inst);
		}
		free(line);
	}
	close(fd);
	return (1);
}