/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:14:37 by jdiaz             #+#    #+#             */
/*   Updated: 2018/12/04 21:57:02 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler.h>

int		lexer(char *str)
{
	int fd;

	fd = open(str, O_RDONLY);
}

int		main(int argc, char **argv)
{
	t_asm	ob;
	int		fd;

	if (argc != 2)
		printf("incorrect number of arguments\n");
	else
	{
		if (lexer(argv[1]) == -1)
			return(printf("error in the input file\n"));
		ob.labels = get_labels(&ob);
		fd = open("new_file", O_WRONLY);
		write_bits(&ob, fd);
		close(fd);
	}
	return (0);
}
