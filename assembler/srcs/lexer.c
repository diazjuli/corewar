/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:59 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/13 21:16:50 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

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
	if (lbl[i + 1] != '\0' || lbl[0] == LABEL_CHAR)
		return (-1);
	return (1);
}

int		get_label(char *lbl, t_vars *ob, char **inst)
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
		inst = ft_strsplit(line, " ,	");
		printf("%s\n", line);
		ob->counter++;
		ob->bl_label = 0;
		if (inst[0] && (ft_strcmp(inst[0], NAME_CMD_STRING) == 0 ||
				ft_strcmp(inst[0], COMMENT_CMD_STRING) == 0))
		{
			if (check_name(ob, line, fd) == -1)
				return (-1);
		}
		else if (all_whitespace(line) != 1 && inst[0][0] != COMMENT_CHAR)
		{
		
			if (ft_strchr(inst[0], LABEL_CHAR) && get_label(inst[0], ob, inst) == -1)
				return (-1);
			if (inst[ob->bl_label] && inst[ob->bl_label][0] != COMMENT_CHAR
					&& (get_op(inst[ob->bl_label], ob) == -1 ||
					 check_args(op_tab[ob->op_code].num_args,
						 op_tab[ob->op_code].arg_types, inst, ob) == -1))
				return (-1);	
		}
		free_split(inst);
		free(line);
	}
	return (1);
}
