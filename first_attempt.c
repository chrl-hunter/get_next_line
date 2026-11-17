#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_list
{
	char			*data;
	struct s_list	*link;
}					t_list;


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

char	*ft_strdup(char  *src, size_t nbytes)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = malloc(sizeof(char) * nbytes);
	if (!dest)
		return (NULL);
	while (i < nbytes)
	{
		dest[i] = src[i];
		i++;
	}
	return dest;
}

t_list	*ft_lstnew(char *content, size_t nbytes)
{
	t_list	*list;
	
	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->data = ft_strdup(content, nbytes);
	if (!list->data)
	{
		free(list->data);
		return (NULL);
	}
	list->link = NULL;
	return (list);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->link)
		lst = lst->link;
	return (lst);
}

void	ft_listadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->link = new;
}

void	get_next_line(int fd, size_t nbytes)
{
	ssize_t	bytes_read;
	t_list	*stash;
	t_list	*tail;
	char	buffer[nbytes];

	bytes_read = read(fd, buffer, nbytes);
	stash = ft_lstnew(buffer, nbytes);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, nbytes);
		tail = ft_lstnew(buffer, nbytes);
		ft_listadd_back(&stash, tail);
		ft_putstr_fd(stash->data, 1); //only for debbuging
	}
}

int		main(void)
{
	size_t	nbytes;
	int		fd = 0;

	nbytes = 5;
	fd = open("hola.txt", O_RDONLY);
	get_next_line(fd, nbytes);
//	if (check(*list) > 0)
//		ft_putstr_fd("Newline found", 1);
}
