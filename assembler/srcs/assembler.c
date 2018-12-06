/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:09:01 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/05 18:21:35 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		get_label(char **line)
{
	int		i;

	i = 0;
	if (line[])
}

int		check_register(char *r_arg)
{
	int		reg_num;

	reg_num = ft_atoi([i++]);
	if (reg_num > 16)
	{
		printf("incorrect register number\n");
		exit (0);
	}
}

int		check_args(char **line, t_vars *ob)
{
	int		i;

	i = 0;
	while (i < ob->num_args)
	{
		if (line[i][0] == 'r' && ob->)
		{
			check_register(line[i++]);
		}
		else if (line[i][0] == '%')
			check_direct(line[i++]);
		else if (line[i][0] >= '0' && 0line[i][0] <= '9')
			check_indirect(line[i++]);
	}
}


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
			check_name(line, ob);    //check and get name into ob
			check_comment(line, ob); //check and get comment into ob
		}
		get_label(line, ob);  //get label name into labels ob
		check_op(line, ob);   //get the type of args, op_code, num_args into ob,
		check_args(line, ob); //unable check if %:label because haven't completed label list
	}
	close(fd);
	return (1);
}

int		parser(char *filename, t_vars *ob)  //2nd pass, while counting get label addresses and check lex-labels
{
	int		fd;
	int		counter;
	char	**line;

	fd = open(filename, O_RDONLY);
	counter = 0;
	while ((get_next_line(fd, line) > 0))
	{
		get_label_addr(line, ob);
		check_label(line, ob);   //check the label is correct within the arg, get the label value inside the struct


	}
	return (1);
}

int		generator(int fd, t_vars *ob) //3rd pass generate the bits
{
	//How will we know the value corresponding to each param? we would need to do atoi again, bc we transform itob (not atob)
	linked_list
	elem =
	write(fd, buf, 1)
}

int        main(int argc, char **argv)
{
    t_vars	ob;
	int		fd;

    if (argc != 2)
        printf("incorrect number of arguments\n");
    else
    {
        if (lexer(argv[1], &ob) == -1)
            return(printf("lexical error in the input file\n"));
		if (parser(argv[1], &ob) == -1)
			return(printf("parser/label error in the input file\n"));
        fd = open("new_file", O_WRONLY);
        generator(fd, &ob);
        close(fd);
    }
    return (0);
}
