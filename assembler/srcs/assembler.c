/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:09:01 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/06 20:15:40 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		get_op(char *mnemonic)
{
	int i;

	i = 0;
	while (i < 17)
	{
		if (ft_strcmp(op_tab[i], mnemonic) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		main(int argc, char **argv)
{
	t_asm	ob;
	int		fd;

	if (argc != 2)
		printf("incorrect number of arguments\n");
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1 || lexer(&ob, fd) == -1)
			return(printf("error in the input file\n"));
		fd = open(argv[1], O_RDONLY);
		get_label_address(&ob,fd);
		close(fd);
		fd = open(argv[1], O_RDONLY);
		ob.output_fd = open("new_file", O_WRONLY);
		if (file_generator(&ob, fd) == -1)
			return (-1);
		close(fd);
		close(ob.output_fd);
	}
	return (0);
}
