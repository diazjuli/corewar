/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:59 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/05 19:40:42 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		check_name(char *line, t_vars *ob)
{
	
}

int		get_label(char **line)
{
	int		i;

	i = 0;
	if (line[])

}

//check_op(char **line, ob);

int        lexer(char *filename, t_vars *ob) //1st pass check lexical errors 
{
    int		fd;
	char	**line;	

    fd = open(str, O_RDONLY);
	while ((get_next_line(fd, line) > 0)) 
	{
		line = strplit(*line, '\0');
		if (line[0][0] == '#')
			continue ;
		else if (line[0][0] == '.')
		{
			if (line[0][1] == 'n')
				check_name(line, ob);    //check and get name into ob
			else if (line[0][1] == 'c')
				check_comment(line, ob); //check and get comment into ob
		}
		get_label(line, ob);  //get label name into labels ob
		check_op(line, ob);   //get the type of args, op_code, num_args into ob,
		check_args(line, ob); //unable check if %:label because haven't completed label list
	}
	close(fd);
	return (1);
}
