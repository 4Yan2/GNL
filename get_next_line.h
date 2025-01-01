#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

// Prototype de la fonction principale
char	*get_next_line(int fd);

// Prototypes des fonctions utilitaires
size_t	gnl_strlen(const char *s);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strchr(const char *s, int c);
char	*extract_line(char *stash);
char	*clean_stash(char *stash);

#endif