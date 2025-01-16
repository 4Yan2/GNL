#include "get_next_line.h"
void *free_list(t_list **lst);
/*
 * Polish linked list for next call
*/
int	polish_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1); // Erreur d'allocation mémoire
	clean_node = malloc(sizeof(t_list));
	if (NULL == clean_node)
	{
		free(buf);
		return (-1); // Erreur d'allocation mémoire
	}
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf); // Remet la liste à jour
	return (0); // Succès
}

/*
 * Get my (line\n] 
*/
char	*get_ln(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (NULL == list)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

/*
 * append one node
 * to the end of list
*/
int	append(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (NULL == new_node)
	{
		free(buf);
		return (-1); // Erreur d'allocation mémoire
	}
	new_node->str_buf = buf;
	new_node->next = NULL;
	if (NULL == last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	return (0); // Succès
}

int	create_list(t_list **list, int fd)
{
	int		char_read;	
	char	*buf;

	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (NULL == buf)
			return (-1); // Erreur d'allocation mémoire
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read < 0)
		{
			free(buf);
			free_list(list);
			return (-1); // Erreur de lecture
		}
		if (char_read == 0) // Fin de fichier atteinte
		{
			free(buf);
			return (0);
		}
		buf[char_read] = '\0';
		if (append(list, buf) == -1)
		{
			free(buf);
			free_list(list); // Libère tous les nœuds alloués
			return (-1); // Échec lors de l'ajout à la liste
		}
	}
	return (0); // Succès
}

/*
 * Mother function
 * 	~Took a fildes
 * 	~Gives back the next_string 
*/
char *get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
	{	
		if (list != NULL)
		{
			// printf("on rentre ici (2)\n");
			free(list->str_buf);
			list->str_buf = NULL;
			free(list);
			list = NULL;
		}
		return (NULL);
	}
	
	if (create_list(&list, fd) == -1)
	{
		free_list(&list);
		return (NULL);
	}
	
	next_line = get_ln(list);
	if (next_line == NULL) //count > 2)
	{
		free_list(&list);
		next_line = NULL;
		return (NULL);
	}
	
	if (polish_list(&list) == -1)
	{
		free_list(&list);
		return (NULL);
	}
	return (next_line);
}

void *free_list(t_list **lst)
{
	t_list *tmp1;
	t_list *tmp2;

	if (lst == NULL)
		return (NULL);
	tmp1 = *lst;
	while (tmp1 != NULL)
	{
		// printf("on rentre ici BIIIIIIIIISS\n");
		tmp2 = tmp1->next;
		free(tmp1->str_buf);
		free(tmp1);
		tmp1 = tmp2;
	}
	*lst = NULL;
	return (NULL);
}