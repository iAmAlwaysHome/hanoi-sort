 
#include "../../incs/mylibc.h"

char	*mystrjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && s1[i])
		i++;
	j = 0;
	while (s2 && s2[j])
		j++;
	str = malloc(i + j + 1);
	i = 0;
	while (str && s1 && s1[i++])
		str[i - 1] = s1[i - 1];
	j = 0;
	while (str && s2 && s2[j++])
		str[i + j - 2] = s2[j - 1];
	if (str && (i || j))
		str[i + j - 1 - (i && j)] = '\0';
	if (str && !i && !j)
		str[0] = '\0';
	return (str);
}
