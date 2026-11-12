#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

struct	node {
	char	*data;
	struct node	*link;
};

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		{
			ft_putchar_fd(str[i], fd);
			i++;
		}
}

int	main(void)
{
	char	buffer[5];
	int		fd;
	size_t	nbytes;
	ssize_t	bytes_read;

	fd = open("hola", O_RDONLY);
	nbytes = sizeof(buffer);
	bytes_read = read(fd, buffer, nbytes);
	ft_putstr_fd(buffer, 1);
}
