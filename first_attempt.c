#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_list
{
	char			*data;
	struct s_list	*link;
}					t_list;

t_list	*ft_lstlast(t_list *lst);

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		{
			write(fd, &str[i], 1);
			i++;
		}
}

int		check(t_list list)
{
	int	i;
	char	*content;

	content = list.data;
	i = 0;
	while (content[i])
	{
		if (content[i] != '\n')
			i++;
		else if (content[i] == '\n')
			return (1);
	}
	return (0);
}

t_list	*ft_lstnew(char	*content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->data = content;
	list->link = NULL;
	return (list);
}

t_list	*ft_lstast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->link)
		lst = lst->link;
	return (lst);
}

void	ft_listadd_back(t_list **lst, t_list new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = &new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->link = new;
}

void	read_bytes(int fd, char *buffer, size_t nbytes)
{
	ssize_t	bytes_read;
	t_list	*head;

	bytes_read = read(fd, buffer, nbytes);
	head = ft_lstnew(&buffer);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, nbytes);
		ft_listadd_back(&head, *ft_lstnew(buffer));
	}
}

int		main(void)
{
	char	buffer[5];
	int		fd = 0;
	size_t	nbytes;
	t_list	*list;

	fd = open("hola.txt", O_RDONLY);
	nbytes = sizeof(buffer);
	read_bytes(fd, buffer, nbytes);
	if (check(*list) > 0)
		ft_putstr_fd("Newline found", 1);
	ft_putstr_fd(list->data, 1);
}
