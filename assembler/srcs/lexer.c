/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:59 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/12 19:06:07 by jcruz-y-         ###   ########.fr       */
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
	jointline = inst[1];
	if (ft_strcmp(NAME_CMD_STRING, str) == 0 || ft_strcmp(COMMENT_CMD_STRING, str) == 0)
	{
		if (strlastchr(line, '\"') == -1)
			jointline = join_quotes(inst[1], fd);
		if (ft_strcmp(NAME_CMD_STRING, str) == 0 && ft_strlen(jointline) <= PROG_NAME_LENGTH)	
			ob->player_name = jointline;
		if (ft_strcmp(COMMENT_CMD_STRING, str) == 0 && ft_strlen(jointline) <= COMMENT_LENGTH)	
			ob->comment = jointline;
		free_split(inst);
		free(str);
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

char	*join_quotes(char *str, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (!ft_strchr(str, '"'))
	{
		get_next_line(fd, &line);
		str = ft_strjoin(str, line);
	}
	i = ft_strlen(str);
	i--;
	str[i] = '\0';
	return (str);
}
int		check_label(char *lbl)
{
	int		i;

	i = 0;
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

	while ((get_next_line(fd, &line) > 0)) 
	{
		printf("%s\n", line);
		if (line[0] == COMMENT_CHAR || empty(line) == -1) 
			continue;
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
	}
	close(fd);
	return (1);
}