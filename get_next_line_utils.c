#include "get_next_line.h"

size_t	gnl_strlen(const char *str)
{
    size_t	i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
    size_t	len1;
    size_t	len2;
    size_t	i;
    size_t	j;
    char	*dest;

    len1 = 0;
    len2 = 0;
    i = 0;
    j = 0;
    if (!s1 && !s2)
        return (NULL);
    if (s1)
        len1 = gnl_strlen(s1);
    if (s2)
        len2 = gnl_strlen(s2);
    dest = malloc(sizeof(char) * (len1 + len2 + 1));
    if (!dest)
        return (NULL);
    if (s1)
    {
        while (s1[i])
        {
            dest[i] = s1[i];
            i++;
        }
    }
    if (s2)
    {
        while (s2[j])
        {
            dest[i] = s2[j];
            i++;
            j++;
        }
    }
    dest[i] = '\0';
    return (dest);
}

char	*gnl_strchr(const char *s, int c)
{
    size_t	i;

    i = 0;
    if (!s)
        return (NULL);
    while (s[i])
    {
        if (s[i] == (char)c)
            return ((char *)(s + i));
        i++;
    }
    if (s[i] == (char)c)
        return ((char *)(s + i));
    return (NULL);
}

char	*extract_line(char *stash)
{
    size_t	i;
    char	*line;

    i = 0;
    if (!stash[i])
        return (NULL);
    while (stash[i] && stash[i] != '\n')
        i++;
    if (stash[i] == '\n')
        i++;
    line = malloc(sizeof(char) * (i + 1));
    if (!line)
        return (NULL);
    i = 0;
    while (stash[i] && stash[i] != '\n')
    {
        line[i] = stash[i];
        i++;
    }
    if (stash[i] == '\n')
    {
        line[i] = stash[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}

char	*clean_stash(char *stash)
{
    size_t	i;
    size_t	j;
    char	*new_stash;

    i = 0;
    while (stash[i] && stash[i] != '\n')
        i++;
    if (stash[i] == '\n')
        i++;
    if (!stash[i])
    {
        free(stash);
        return (NULL);
    }
    new_stash = malloc(sizeof(char) * (gnl_strlen(stash + i) + 1));
    if (!new_stash)
    {
        free(stash);
        return (NULL);
    }
    j = 0;
    while (stash[i])
    {
        new_stash[j] = stash[i];
        i++;
        j++;
    }
    new_stash[j] = '\0';
    free(stash);
    return (new_stash);
}
