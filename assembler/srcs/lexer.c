/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:59 by jcruz-y-          #+#    #+#             */
/*   Updated: 2019/01/26 15:23:31 by tholzheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

int				check_label(char *lbl, t_vars *ob)
{
	int		i;

	i = 0;
	while (lbl[i] != LABEL_CHAR)
	{
		if (!ft_strchr(LABEL_CHARS, lbl[i])) // if there is a character that is not in the LABEL_CHARS ret -1
			return (error_message(4, ob->counter, 0));
		i++;
	}
	if (lbl[i + 1] != '\0' || lbl[0] == LABEL_CHAR) // if there is something after ":" or ":" is at the beginning ret -1
		return (error_message(5, ob->counter, 0));
	return (1);
}

int				get_label(char *lbl, t_vars *ob)
{
	t_label	*tmp;
	t_label	*elem;
	
	tmp = ob->labels; // tmp = head of the labels
	while (tmp && tmp->next) // why tmp->next also?
	{
		if (ft_strcmp(lbl, tmp->label) == 0) // if the new label was already saved before return -1
			return (error_message(3, ob->counter, 0));
		tmp = tmp->next;
	}
	if (tmp && ft_strcmp(lbl, tmp->label) == 0) // if the new label was already saved before return -1
		return (error_message(3, ob->counter, 0));
	if (check_label(lbl, ob) == -1) // checks that the label is correct
		return (-1);
	elem = ft_create_elem(lbl); // create a new label
	if (ob->labels == NULL)
		ob->labels = elem;
	if (tmp != NULL)
		tmp->next = elem;
	ob->bl_label = 1; // bl_label is set to one because there is a label in the current line
	return (0);
}

t_label			*ft_create_elem(char *lbl)
{
	t_label	*elem;

	elem = (t_label*)malloc(sizeof(t_label));
	elem->label = ft_strdup(lbl);
	elem->address = -1;
	elem->next = NULL;
	return (elem);
}

static int		arg_lexer(char **inst, t_vars *ob)
{
	if (ft_strchr(inst[0], LABEL_CHAR) && get_label(inst[0], ob) == -1) // save label. if error ret -1
		return (-1);
	if (inst[ob->bl_label] && inst[ob->bl_label][0] != COMMENT_CHAR // if there is an inst and it's not comment
			&& (get_op(inst[ob->bl_label], ob) == -1 || // check that mnemonic exists and save op_code in ob
			 check_args(op_tab[ob->op_code].num_args, // check that the amount of arguments and their type is
				 op_tab[ob->op_code].arg_types, inst, ob) == -1)) // correct
		return (-1);
	return (1);
}

int				lexer(t_vars *ob, int fd) //1st pass check lexical errors 
{
	char	*line;
	char	**inst;

	while ((get_next_line(fd, &line) > 0)) 
	{
		inst = ft_strsplit(line, " ,\t"); // change here
		ob->counter++;
		ob->bl_label = 0; // 0 if there is NO label on the line, 1 otherwise
		if (inst[0] && (ft_strcmp(inst[0], NAME_CMD_STRING) == 0 || // if the first element of the inst array is 
				ft_strcmp(inst[0], COMMENT_CMD_STRING) == 0))		// ".name" or ".comment"
		{
			if (check_name(ob, line) == -1) //checks that the name and comment are written correctly and saves them
				return (-1);					// in t_vars op
		}
		else if (all_whitespace(line) == 0 && inst[0][0] != COMMENT_CHAR) // if the line is not empty and not a comment
			if (arg_lexer(inst, ob) == -1)
				return (-1);
		free_split(inst);
		free(line);
	}
	return (1);
}
