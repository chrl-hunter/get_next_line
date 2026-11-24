/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperez-h@student.42barcelona.com           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 14:40:33 by cperez-h          #+#    #+#             */
/*   Updated: 2026/11/24 17:07:46 by cperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <fcntl.h>

typedef struct s_node
{
	char			*data;
	size_t			len;
	size_t			offset;
	struct s_node	*next;
}	t_node;

int		gnl_check(t_node *head);
void	gnl_tail(t_node **head, t_node *tail, t_node *new);
size_t	gnl_linelen(t_node *head);
void	gnl_clear(t_node *head);
t_node	gnl_newnode(void);
int		gnl_read(int fd, t_node **head);
void	gnl_cleanup(t_node **head);
char	get_next_line(int fd);
#endif
