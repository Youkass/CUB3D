/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 22:28:01 by dasereno          #+#    #+#             */
/*   Updated: 2022/11/20 22:32:16 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub.h"

void	parse_dir(char *str, int index, int *nb)
{
	int		i;
	int		j;
	char	*new;

	i = 2;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	new = malloc(sizeof(char) * ft_strlen(str));
	printf("=> %s\n", str + i);
	while (str[i] && (str[i] != ' ' || str[i] == '\t'))
		new[j++] = str[i++];
	new[j] = 0;
	printf("::%s, %d\n", new, index);
	_var()->dir[index] = generate_image(new);
	*nb += 1;
	if (!_var()->dir[index].img || *nb > 1)
	{
		// exit(1);
		printf("Error\n[%s]: does not valid\n", new);
	}
	return ;
}

void	jump_spaces(int *i, char *str, int k)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		*i += 1;
	if (str[*i] == ',')
		*i += 1;
	else if (k != 2)
	{
		printf("Error\n");
		exit(1);
	}
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		*i += 1;
}

void	parse_color(char *str, int index, int *nb)
{
	int			i;
	int			j;
	int			k;
	int			tmp;
	char		buf[5];

	i = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	k = 0;
	*nb += 1;
	while (str[i])
	{
		j = 0;
		buf[0] = 0;
		while (str[i] && str[i] >= '0' && str[i] <= '9' && j < 4)
			buf[j++] = str[i++];
		buf[j] = 0;
		tmp = atoi(buf);
		jump_spaces(&i, str, k);
		_var()->colors[index][k++] = tmp;
		if (tmp > 255 || tmp < 0)
		{
			printf("Error\n%d is not in color range (0-255)\n", tmp);
			exit(1);
		}
		else if ( k > 3 || j > 3)
		{
			printf("Error\nToo many instructions\n");
		}
	}
	if (*nb > 1)
	{
		printf("Error\n");
		exit(1);
	}
	_var()->colors[index][k] = 100;
}

int	is_nb_args(int	*tab)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (tab[i++] != 1)
			return (0);
	}
	return (1);
}
int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' || str[i] != '\n' || str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	is_map(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '1' && str[i] != '0'
			&& !is_player(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	parse_args(char **map)
{
	int	nb_types[6];
	int	index;
	int	i;

	i = 0;
	index = -1;
	memset(&nb_types, 0, sizeof(nb_types));
	while (map[i])
	{
		if (!strncmp(map[i], "NO", 2))
			parse_dir(map[i], 0, &nb_types[0]);
		else if (!strncmp(map[i], "SO", 2))
			parse_dir(map[i], 1, &nb_types[1]);
		else if (!strncmp(map[i], "WE", 2))
			parse_dir(map[i], 2, &nb_types[2]);
		else if (!strncmp(map[i], "EA", 2))
			parse_dir(map[i], 3, &nb_types[3]);
		else if (!strncmp(map[i], "F", 1))
			parse_color(map[i], 0, &nb_types[4]);
		else if (!strncmp(map[i], "C", 1))
			parse_color(map[i], 1, &nb_types[5]);
		else if (is_nb_args(nb_types) && index == -1)
			index = i;
		else if (!is_empty(map[i]) && !is_map(map[i]))
		{
			printf("Error\n%s Unrecognized argument\n", map[i]);
			exit(0);
		}
		++i;
	}
	if (!is_nb_args(nb_types))
	{
		printf("Error\nToo many arguments\n");
		exit(1);
	}
	while (is_empty(map[index]))
		index++;
	check_map(map, index);
}
