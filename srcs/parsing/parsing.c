#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "../../includes/cub.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			w++;
		i++;
	}
	return (w);
}

static char	*ft_strncpy_split(char const *src, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * n);
	if (!dest)
		return (NULL);
	while (i < n - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*free_tab(char **tab, int k)
{
	while (k >= 0)
	{
		free(tab[k]);
		tab[k] = NULL;
		k--;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

static char	**ft_split_body(char const *s, char c, char **split)
{
	int	j;
	int	k;
	int	i;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		while (s[i + j] && s[i + j] != c)
			j++;
		if (j != 0)
		{
			split[k] = ft_strncpy_split(s + i, j + 1);
			if (!split[k++])
				return (free_tab(split, k - 1));
			i += j - 1;
			j = 0;
		}
		i++;
	}
	split[k] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (s == NULL)
		return (NULL);
	split = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!split)
		return (NULL);
	return (ft_split_body(s, c, split));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1 && *s1)
	{
		str[i++] = *s1;
		s1++;
	}
	while (s2 && *s2)
	{
		str[i++] = *s2;
		s2++;
	}
	str[i] = 0;
	return (str);
}


char	*read_file(int fd)
{
	int		read_val;
	char	*str;
	char	*tmp;
	char	buff[1084];

	str = NULL;
	read_val = 1;
	while (read_val)
	{
		read_val = read(fd, buff, 1084);
		buff[read_val] = 0;
		tmp = str;
		str = ft_strjoin(tmp, buff);
	}
	return (str);
}

t_vector2D  get_pos(char **map, char c)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if (map[i][j] == c)
                return ((t_vector2D){j, i});
            j++;
        }
        i++;
    }
    return ((t_vector2D){-1, -1});
}

int	is_char_in_range(t_vector2D pos, char **map)
{
	t_vector2D	it;
	int			ok;

	it = pos;
	ok = 0;
	while (map[pos.y][pos.x] && map[pos.y][pos.x] != 'Z')
	{
		if (map[pos.y][pos.x] == '1')
		{
			ok++;
			break;
		}
		pos.x++;
	}
	pos = it;
	while (pos.x >= 0 && map[pos.y][pos.x] && map[pos.y][pos.x] != 'Z')
	{
		if (map[pos.y][pos.x] == '1')
		{
			ok++;
			break;
		}
		pos.x--;
	}
	pos = it;
	while (map[pos.y][pos.x] && map[pos.y][pos.x] != 'Z')
	{
		if (map[pos.y][pos.x] == '1')
		{
			ok++;
			break;
		}
		pos.y++;
	}
	pos = it;
	while (pos.y >= 0 && map[pos.y][pos.x] && map[pos.y][pos.x] != 'Z')
	{
		if (map[pos.y][pos.x] == '1')
		{
			ok++;
			break;
		}
		pos.y--;
	}
	if (ok == 4)
		return (1);
	return (0);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int check_map(char **map)
{
	t_vector2D	it;

	it = (t_vector2D){0, 0};
	while (map[it.y])
	{
		it.x = 0;
		while (map[it.y][it.x])
		{
			if (map[it.y][it.x] == '0' || is_player(map[it.y][it.x]))
			{
				if (!is_char_in_range(it, map))
				{
					printf("SCANDLAEUX CA MARCHE PAS\n");
						return (0);
				}
			}
			it.x++;
		}
		it.y++;
	}
	return (1);
}

int	get_longest_line(char **map)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > (size_t)max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

char	*copy_line_and_add(char *str, int size)
{
	int		i;
	char	*new;

	i = 0;
	new	= malloc(sizeof(char) * (size + 1));
	while (str[i])
	{
		if (str[i] == ' ')
			new[i] = 'Z';
		else
			new[i] = str[i];
		i++;
	}
	while (i < size)
		new[i++] = 'Z';
	new[i] = 0;
	return (new);
}

char	**resize_map(char **map)
{
	int		max;
	int		i;
	char	**new;

	max = get_longest_line(map);
	new = malloc(sizeof(char *) * 100);
	i = 0;
	while (map[i])
	{
		new[i] = copy_line_and_add(map[i], max);
		i++;
	}
	new[i] = NULL;
	return (new);
}
/*
int main(int argc, char **argv)
{
    int     fd;
    char    *str;
    char    **map;

    fd = open(argv[1], O_RDONLY);
    str = read_file(fd);
    map = ft_split(str, '\n');
    //for (int i = 0; map[i]; i++)
    //    printf("{%s}\n", map[i]);
	char **new = resize_map(map);
    //for (int i = 0; new[i]; i++)
    //    printf("{%s}\n", new[i]);
	printf("HEY-> %d\n", check_map(new));
}*/
