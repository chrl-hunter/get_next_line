/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperez-h@student.42barcelona.com           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 15:45:58 by cperez-h          #+#    #+#             */
/*   Updated: 2026/11/24 15:54:03 by cperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_check(t_node *head)
{
	size_t	i;

	while (head)
	{
		i = head->offset;
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

void	gnl_tail(t_node **head, t_node **tail, t_node *new)
{
	if (!*head)
		*head = new;
	else
		(*tail)->next = new;
	*tail = new;
}

size_t	gnl_linelen(t_node *head)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (head)
	{
		i = head->offset;
		while (i < head->len)
		{
			len++;
			if (head->data[i] == '\n')
				return (len);
			i++;
		}
		head = head->next;
	}
	return (len);
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
