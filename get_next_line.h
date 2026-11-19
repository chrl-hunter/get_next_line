/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoromin@student.42barcelona.com           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 17:50:51 by acoromin          #+#    #+#             */
/*   Updated: 2026/11/19 17:50:53 by acoromin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE = 1024
#endif

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_node
{
	char			*data;
	ssize_t			len;
	struct s_node	*next;
}					t_node;
// DEFINICION DE NODOS
//	+ string (acotada por el len) dentro del buffer
//	+ cantidad de bytes (sin tener que hacer un sizeof)
//	+ link al siguiente nodo

char	*get_next_line(int fd);
// FUNCION PRINCIPAL
// Recibe un file descriptor del archivo
// Devuelve la cadena de la linea a imprimir 
// - la cadena debe estar almacenada en memoria
// - la cadena sera liberada en main

int		gnl_read(int fd, t_node **head);
// Recibe fd y el nodo principal head/stash
// Modifica dentro del nodo la cantidad de bytes del buffer y el contenido del buffer
// Tiene acceso completo al nodo; es decir sabe su data, len, y next
//		-> es una pista para saber a lo que llama esta funcion
//		-> deberia devolver un ssize_t siendo este la cantidad de bytes leidos (-1 significa error de lectura)
// 
int		gnl_check(t_node *head);
// Evalua el string del nodo y lo recorre para verificar si hay "/n"
//		-> si solo recibe *head, puede acceder a len?
//		-> lo logico es que si ya que los strings dentro no terminan en "/0"
//		-> el contador debe llegar a el len de la string
size_t	gnl_linelen(t_node *head);
// Ojo con esta funcion, porque no es el len del string del nodo
// Es el len de la linea total hasta encontrar "/n", incluyendo "/n"
//		-> podria simplemente sumar todos los len de los nodos (evitar caso -1) para el len total
//		-> no los puedo sumar tan facilmente, tengo que primero correr gnl_check para saber donde esta
//		-> aqui tendria que usar el offset??
//			+ si, por eso gnl_check devuelve int
char	*gnl_extract(t_node *head);
// Parece ser una version de ft_strcpy
// Aparentemente debe extraer la data de cada nodo
// Debe regresar toda la linea como una cadena y terminarla en "/0"
// Para que esto pueda funcionar esta debe llamar a gnl_linelen y luego hacer el malloc
void	gnl_cleanup(t_node **head);
// NO CONFUNDIR CON gnl_clear
// Libera los nodos consumidos
//		-> intuyo que esta se usara despues de pasarlo todo a una linea
// Conserva el ultimo nodo donde se encuentra "/n"
//		-> deberia desplazar el offset uno despues de la propia newline (???)
//		-> si conserva el ultimo nodo tal cual como esta va a fallar en el gnl_check
//		-> que pasa si agrego como un valor intrinseco del nodo el propio offset de la newline?
//			+ de modo que NULL es que no hay, pero cualquier int menor a len quiere decir que esta la newline
void	gnl_clear(t_node **head);
// Libera la lista cuando ya no se necesita
// O si hay un error
//		-> esta podria ser llamada por gnl_cleanup para liberar espacio

// intuyo que tendre que hacer un putstr/putchar?

// FLUJO
// 1) get_next_line -> gnl_read, gnl_extract, gnl_cleanup
// 2) gnl_read
// 3) gnl_extract -> gnl_linelen -> gnl_check
// 4) gnl_cleanup
// 5) gnl_clear


