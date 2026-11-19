/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_attempt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoromin@student.42barcelona.com           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 17:50:42 by acoromin          #+#    #+#             */
/*   Updated: 2026/11/19 18:23:54 by acoromin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_read(int fd, t_node **head)
{
	int	status;
	
	status = read(fd, head->data, O_RONLY);
	return (status);
}

int	gnl_check(t_node *head)
{
	ssize_t	i;

	if (head->len <= 0)
		return (NULL);
	while (head)
	{
		i = 0;
		while (i < head->len)
		{
			if (head->data[i] == '\n')
				return (1);
			i++;
		}
		head = head->next;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	char			*line;
	int				status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!gnl_check(head))
	{
		status = gnl_read(fd, &head);
		if (status < 0)
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
