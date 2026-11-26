/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperez-h@student.42barcelona.com           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 15:05:52 by cperez-h          #+#    #+#             */
/*   Updated: 2026/11/26 17:13:22 by cperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static t_node	gnl_newnode(void)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->data = malloc(BUFFER_SIZE);
	if (!new->data)
	{
		free(new);
		return (NULL);
	}
	new->len = 0;
	new->offset = 0;
	new->next = NULL;
	return (new);
}

static int	gnl_read(int fd, t_node **head)
{
	t_node	*new;
	t_node	*tail;
	ssize_t	bytes;

	tail = *head;
	while (tail && tail->next)
		tail = tail->next;
	while (1)
	{
		new = gnl_newnode();
		if (!new)
			return (-1);
		bytes = read(fd, new->data, BUFFER_SIZE);
		if (bytes <= 0)
		{
			gnl_clear(&new);
			return (bytes);
		}
		new->len = (size_t)bytes;
		gnl_tail(head, &tail, new);
		if (gnl_check(new))
			return (0);
	}
}

static char	*gnl_extract(t_node *head)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*line;

	len = gnl_linelen(head);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (head && j < len)
	{
		i = head->offset;
		while (i < head->len && j < len)
			line[j++] = head->data[i++];
		head = head->next;
	}
	line[j] = '\0';
	return (line);
}

static void	gnl_cleanup(t_node **head)
{
	t_node	*tmp;
	int		found;

	found = 0;
	while (*head && !found)
	{
		while ((*head)->offset < (*head)->len && !found)
		{
			if ((*head)->data[(*head)->offset] == '\n')
				found = 1;
			(*head)->offset++;
		}
		if ((*head)->offset == (*head)->len)
		{
			tmp = *head;
			*head = tmp->next;
			free(tmp->data);
			free(tmp);
		}
	} // que pasa si dentro del nodo se encuentran 2 newline?
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!gnl_check(head))
	{
		if (gnl_read(fd, &head) < 0)
		{
			gnl_clear(&head);
			return (NULL);
		}
	}
	if (!head)
		return (NULL);
	line = gnl_extract(head);
	if (!line)
	{
		gnl_clear(&head);
		return (NULL);
	}
	gnl_cleanup(&head);
	return (line);
}
