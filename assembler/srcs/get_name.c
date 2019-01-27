/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:45:01 by jdiaz             #+#    #+#             */
/*   Updated: 2019/01/26 15:04:06 by tholzheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler.h>

static int		check_max_sizes(t_vars *ob)
{
	if (ob->player_name && ft_strlen(ob->player_name) > 128)
	{
		printf("Champion Name too long (Max length 128)\n");
		return (-1);
	}
	if (ob->comment && ft_strlen(ob->comment) > 2048)
	{
		printf("Comment too long (Max length 2048)\n");
		return (-1);
	}
	return (1);
}

static void		save_name_comment(t_vars *ob, char i, char *new)
{
	if (i == 'n')
		ob->player_name = new;
	else
		ob->comment = new;
	ob->begin_line = ob->counter;
}

int				check_name(t_vars *ob, char *line)
{
	char	i;
	char	*new;

	line = ft_strchr(line, '.'); // if there is tab or space before it moves it to the .
	i = *(++line); //this would be a "n" or a "c"
	while (*line && *line != ' ' && *line != '\t') // skiping the letters
		line++;
	while (*line && (*line == ' ' || *line == '\t')) // skiping the spaces
		line++;
	if (*line != '"') // if there is no double quotes after the spaces return -1
		return (error_message(2, i, 0));
	line++; // we are inside the name/comment after the first double quotes
	if (!ft_strchr(line, '"') || ft_strchr(line, '"') != ft_strrchr(line, '"'))
		return (error_message(2, i, 0));
	new = ft_strdup(line);
	line = ft_strchr(new, '"');
	*line = '\0'; // added in order to save only what's inside the double quotes
	while (*(++line))
		if (*line != ' ' && *line != '\t') // if there is something after the double quotes that isn't spaces
			return (error_message(2, i, 0));
	save_name_comment(ob, i, new);
	return (check_max_sizes(ob));
}
