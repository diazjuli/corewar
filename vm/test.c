#include <stdio.h>
int		main(void)
{
	char *str;
	int	i;

	str = malloc(6);
	i = 0;
	while (i < 6)
	{
		str[i] = "J";
		i++;
	}
	str[i] = '\0';
	str = "HELLO";
	printf("%s\n", str);
	return (0);
}
