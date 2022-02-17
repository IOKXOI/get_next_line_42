#include <stddef.h>

char	*ft_memmove(char *dest, char *src, size_t size)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	if (src == dest)
	{
		while (dest[i])
			dest[i++] = '\0';
	}
	else if (src > dest)
	{
		while (src[i] && size--)
		{
			dest[i] = src[i];
			i++;
		}
	}
	while (i <= 7)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int main()
{
	char str[7] = "Bomjour";
	ft_memmove(str, &str[6], 7);
	return 0;
}
