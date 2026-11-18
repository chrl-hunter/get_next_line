#ifndef BUFFER_SIZE
# define BUFFER_SIZE = 1024
#endif

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_list
{
	char			*data;
	struct s_list	*link;
}					t_list;
