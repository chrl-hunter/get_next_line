#include "get_next_line.h"

void	ft_lstnew(t_list **head, int fd)
{
	
}

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	char			*line;
	size_t			nbytes;

	line = NULL;
	nbytes = 0;
	if (read(fd, &line, 0) < 0) // si el primer read de 0 bytes da fallo de lectura aborta
	{
		ft_lstdel(&head);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0) // si no hay buffer_size y el fd es negativo(error code) aborta
		return (NULL);
	ft_lstnew(&head, fd);
	if (head == NULL) // si fallo al crear el stash aborta
		return (NULL);
	line = ft_newline(&head, line, nbytes); // sobreescribe el BUFFER
	ft_lstclear(&head);
	return (line);
}
