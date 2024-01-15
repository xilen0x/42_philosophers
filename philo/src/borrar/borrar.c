#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	i = 0;

	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i = 0;

	while (s[i])
	{
		if (s[i] == c)
		{
			return (&s[i]);
		}
		i++;
	}
	return (NULL);
}

#include <stdio.h>
int main()
{
	char	*mystring = "holamundo\n";
	char		c = 'm';
	printf("%s\n", ft_strchr(mystring, c));
}
