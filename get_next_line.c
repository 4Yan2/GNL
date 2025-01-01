#include "get_next_line.h"

char	*get_next_line(int fd)
{
    static char	*stash = NULL;
    char		buffer[BUFFER_SIZE + 1];
    ssize_t		bytes_read;  // Type corrigé
    char		*line;
    char		*temp;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    bytes_read = 1;
    while (!gnl_strchr(stash, '\n') && bytes_read != 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(stash);
            stash = NULL;
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        temp = gnl_strjoin(stash, buffer);
        if (stash != NULL)
            free(stash);
        stash = temp;
        if (!stash)
            return (NULL);
    }
    line = extract_line(stash);
    stash = clean_stash(stash);
    return (line);
}
