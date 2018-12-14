/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:45:01 by jdiaz             #+#    #+#             */
/*   Updated: 2018/12/13 19:55:16 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler.h>

int		add_lines(t_vars *ob, char *line, int fd, int i)
{
	char *new;
	char *temp;

	new = ft_strdup(line);
	while (get_next_line(fd, &line) > 0 && ft_strchr(line, '"') == NULL)
	{
		ob->counter++;
		temp = new;
		new = ft_strjoin(temp, line);
		free(temp);
		free(line);
	}
	if (line == NULL || ft_strchr(line, '"') != ft_strrchr(line, '"'))
		return (-1);
	temp = new;
	new = ft_strjoin(temp, line);
	free(temp);
	free(line);
	line = ft_strchr(new, '"');
	while (*(++line))
		if (*line != ' ' && *line != '\t')
			return (-1);
	new[ft_strlen(new) - 1] = '\0';
	if (i == 'n')
		ob->player_name = new;
	else
		ob->comment = new;
	ob->begin_line = ob->counter + 1;
	return (1);
}

int		check_name(t_vars *ob, char *line, int fd)
{
	char	i;
	char	*new;

	line = ft_strchr(line, '.');
	i = *(++line);
	while (*line && *line != ' ' && *line != '\t')
		line++;
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (*line != '"')
		return (-1);
	line++;
	if (ft_strchr(line, '"') == NULL)
		return (add_lines(ob, line, fd, i));
	if (ft_strchr(line, '"') != ft_strrchr(line, '"'))
		return (-1);
	new = ft_strdup(line);
	line = ft_strchr(new, '"');
	while (*(++line))
		if (*line != ' ' && *line != '\t')
			return (-1);
	new[ft_strlen(new) - 1] = '\0';
	if (i == 'n')
		ob->player_name = new;
	else
		ob->comment = new;
	ob->begin_line = ob->counter + 1;
	return (1);
}

