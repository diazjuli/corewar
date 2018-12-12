/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:09:01 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/11 19:31:47 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

int		get_op(char *mnemonic)
{
	int i;

	i = 0;
	while (i < 17)
	{
		if (ft_strcmp(op_tab[i].mnemonic, mnemonic) == 0)
		{
			return (i);
			printf("op_code = %d\n", i);
		}
		i++;
	}
	return (-1);
}

int	free_split(char **inst)
{
	int	i;

	i = 0;
	if (inst)
	{
		while (inst[i])
		{
			free(inst[i]);
			i++;
		}
		free(inst);
	}
	return (0);
}	

int		main(int argc, char **argv)
{
	t_vars	ob;
	int		fd;

	if (argc != 2)
		printf("incorrect number of arguments\n");
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (lexer(&ob, fd) == -1 || fd == -1)
			return(printf("error in the input file\n"));
		printf("lexer is good\n");
		fd = open(argv[1], O_RDONLY);
		get_label_address(&ob,fd);
		close(fd);
		fd = open(argv[1], O_RDONLY);
		ob.output_fd = open("new_file", O_WRONLY);
		if (generator(&ob, fd) == -1)
			return (-1);
		close(fd);
		close(ob.output_fd);
	}
	return (0);
}
