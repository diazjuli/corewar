/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:59 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/13 00:52:54 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

int		check_name(t_vars *ob, char *line, int fd)
{
	char	**inst;
	char	*jointline;
	char	*str;

	inst = ft_strsplit(line, "\"\"\"");
	str = ft_strtrim(inst[0]);
	if (inst[1])
		jointline = ft_strdup(inst[1]);
	else
		jointline = ft_strdup("Default");
	if (ft_strcmp(NAME_CMD_STRING, str) == 0 || ft_strcmp(COMMENT_CMD_STRING, str) == 0)
	{
		if (strlastchr(line, '\"') == -1 && inst[1])
			jointline = join_quotes(inst[1], fd, ob);
		if (ft_strcmp(NAME_CMD_STRING, str) == 0 && ft_strlen(jointline) <= PROG_NAME_LENGTH)	
		{
			ob->player_name = ft_strdup(jointline);
		}
		if (ft_strcmp(COMMENT_CMD_STRING, str) == 0 && ft_strlen(jointline) <= COMMENT_LENGTH)	
			ob->comment = ft_strdup(jointline);
		ob->begin_line = ob->counter;
		free_split(inst);
		free(str);
		free(jointline);
		return (1);
	}
	else
		return (-1);
}

int		strlastchr(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] == c)
		return (1);
	else
		return (-1);
}

char	*join_quotes(char *str, int fd, t_vars *ob)
{
	int		i;
	char	*line;
	char	*tmp;

	i = 0;
	while (!ft_strchr(str, '"'))
	{
		get_next_line(fd, &line);
		ob->counter++;
		tmp = ft_strjoin(str, line);
		free(line);
	}
	i = ft_strlen(str);
	i--;
	tmp[i] = '\0';
	free(str);
	return (tmp);
}
int		check_label(char *lbl)
{
	int		i;

	i = 0;
	if (strlastchr(lbl, LABEL_CHAR) == -1)
		return (-1);
	while (lbl[i] != LABEL_CHAR)
	{
		if (!ft_strchr(LABEL_CHARS, lbl[i]))
			return (-1);
		i++;
	}
	return (1);
}

int		get_label(char *lbl, t_vars *ob, char ** inst)
{
	t_label	*tmp;
	t_label	*elem;
	
	tmp = ob->labels;
	while (tmp && tmp->next)
	{
		if (ft_strcmp(lbl, tmp->label) == 0)
			return (-1);
		tmp = tmp->next;
	}
	if (check_label(lbl) == -1)
		return (-1);
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

int		empty(char *str)
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

int		check_dot(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			return (1);
		if (str[i] != ' ' && str[i] != '	')
			return (-1);
		i++;
	}
	return (-1);
}

int		lexer(t_vars *ob, int fd) //1st pass check lexical errors 
{
	char	*line;
	char	**inst;
	int		i;

	i = 0;
	while ((get_next_line(fd, &line) > 0)) 
	{
		printf("%s\n", line);
		ob->counter++;
		if (line[0] == COMMENT_CHAR || empty(line) == -1) 
		{
			free(line);
			continue;
		}
		else if (check_dot(line) == 1 && check_name(ob, line, fd) == -1)
			return (-1);
		else if (line[0] != COMMENT_CHAR && check_dot(line) != 1 && empty(line) == 1)
		{
			inst = ft_strsplit(line, " ,	");
			if (ft_strchr(inst[0], LABEL_CHAR) && get_label(inst[0], ob, inst) == -1)
				return (-1);
			if (inst[1] && !ft_strchr(inst[1], COMMENT_CHAR) && (get_op(inst[ob->bl_label], ob) == -1 ||
check_args(op_tab[ob->op_code].num_args, op_tab[ob->op_code].arg_types, inst, ob) == -1))
				return (-1);
			ob->bl_label = 0;
			free_split(inst);
		}
		free(line);
		i++;
		if (i == 19)
			while(1);
	}
	close(fd);
	return (1);
}