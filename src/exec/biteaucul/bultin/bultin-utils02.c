# include "minishell.h"

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    char *d;
    const char *s;

    d = dest;
    s = src;
    while (n--)
        *d++ = *s++;
    return dest;
}

char *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    if ((char)c == '\0')
        return (char *)s;
    return NULL;
}
char *ft_strndup(const char *s, size_t n)
{
    char *dup;
    size_t len;

    len = 0;
    while (s[len] && len < n)
        len++;
    dup = (char *)malloc(len + 1);
    if (!dup)
        return NULL;
    ft_memcpy(dup, s, len);
    dup[len] = '\0';
    return dup;
}

char *ft_strdup(const char *s)
{
    char *dup;
    size_t len;

    len = ft_strlen(s);
    dup = (char *)malloc(len + 1);
    if (!dup)
        return NULL;
    ft_memcpy(dup, s, len + 1);
    return dup;
}