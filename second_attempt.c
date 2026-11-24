/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_attempt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperez-h@student.42barcelona.com           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 12:35:15 by cperez-h          #+#    #+#             */
/*   Updated: 2026/11/24 13:14:54 by cperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

int	gnl_check(t_node *head)
{
	ssize_t	i;

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

void	gnl_tail(t_node **head,t_node **tail, t_node *new)
{
	if (!*head)
		*head = new;
	else
		(*tail)->next = new;
	*tail = new;
}

int	gnl_read(int fd, t_node **head)
{
	t_node	*new;
	t_node	*tail;
	ssize_t	bytes;

	tail = *head;
	while (tail && tail->next)
		tail = tail->next;
	while (1)
	{
		new = malloc(sizeof(t_node));
		if (!new)
			return (-1);
		new->data = malloc(sizeof(char) * BUFFER_SIZE);
		if (!new->data)
		{
			free(new);
			return (-1);
		}
		bytes = read(fd, new->data, BUFFER_SIZE);
		if (bytes <= 0)
		{
			free(new->data);
			free(new);
			if (bytes < 0)
				return (-1);
			return (0);
		}
		new->len = bytes;
		new->next = NULL;
		gnl_tail(head, &tail, new);
		if (gnl_check(new))
			return (0);
	}
}

size_t	gnl_linelen(t_node *head)
{	
	ssize_t	i;
	size_t	j;

	j = 0;
	while (head) 
	{
		i = 0;
		while (i < head->len) 
		{
			j++;
			if (head->data[i] == '\n')
				return (j); 
			i++;
		}
		head = head->next;
	}
	return (j);
}

char	*gnl_extract(t_node *head)
{
	ssize_t	i;
	size_t	j;
	char	*line;

	line = malloc(sizeof(char) * gnl_linelen(head) + 1);
	j = 0;
	while (head)
	{
		i = 0;
		while (i < head->len)
		{
			if (head->data[i] == '\n')
			{
				line[j] = head->data[i];
				break;
			}
			line = head->data[i];
			i++;
			j++;
		}
		head = head->next
	}
	line[j] = '\0'; 
	return (line);
}

void	gnl_cleanup(t_node **head)
{
	t_node	*tmp; 
	ssize_t	i;
	ssize_t	j;

	while (*head)
	{
		i = 0;
		while (i < (*head)->len)
		{
			if ((*head)->data[i] == '\n')
			{
				j = 0;
				i++;
				while (i < (*head)->len)
					(*head)->data[j++] = (*head)->data[i++];
				(*head)->len = j;
				if (j == 0)
				{
					tmp = head;
					*head = (*head)->next;
					free(tmp->data);
					free(tmp);
				}
				return ;
			}
			i++;
		}
		tmp = *head;
		*head = (*head)->next;
		free(tmp->data);
		free(tmp);
	}
}

void	gnl_clear(t_node **head)
{
	t_node	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->data);
		free(tmp);
	}
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	char			*line;
	int				status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!gnl_check(head)) // if return 0 entra en el loop
	{
		status = gnl_read(fd, &head); // aqui se lee e
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
