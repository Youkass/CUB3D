/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 22:28:01 by dasereno          #+#    #+#             */
/*   Updated: 2022/11/20 23:41:57 by dasereno         ###   ########.fr       */
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
	while (str[i] && (str[i] != ' ' || str[i] == '\t'))
		new[j++] = str[i++];
	new[j] = 0;
	_image()->dir[index] = generate_image(new);
	*nb += 1;
	if (!_image()->dir[index].img || *nb > 1)
	{
		// exit(1);
		printf("Error\n[%s]: does not valid\n", new);
	}
	return ;
}

void	parse_new_textures(char *str, int index, int *nb)
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
	_image()->textures[index] = generate_image(new);
	*nb += 1;
	if (!_image()->textures[index].img || *nb > 1)
	{
		printf("Error\n[%s]: does not valid\n", new);
		exit(1);
	}
	return ;
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
		// ft_black_hole(1);
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
		if (tmp > 255 || tmp < 0 || k > 3 || j > 3)
		{
			printf("Error\n");
			// ft_black_hole(1);
		}
	}
	if (*nb > 1)
	{
		printf("Error\n");
		// ft_black_hole(1);
	}
	_var()->colors[index][k] = 100;
}

int	is_nb_args(int	*tab)
{
	int	i;

	i = 0;
	while (i < 16)
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

void	parse_args(char **map)
{
	int	nb_types[16];
	int	index;
	int	i;

	i = 0;
	index = -1;
	memset(&nb_types, 0, sizeof(nb_types));
	printf("la\n");
	while (map[i])
	{
		if (!strncmp(map[i], ".", 1))
		{
			if (!is_nb_args(nb_types))
			{
				printf("Error\n");
				// ft_black_hole(1);
			}
			index = i + 1;
			break ;
		}
		else if (!strncmp(map[i], "NO", 2))
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
		else if (!strncmp(map[i], "2", 1))
			parse_new_textures(map[i], 0, &nb_types[6]);
		else if (!strncmp(map[i], "3", 1))
			parse_new_textures(map[i], 1, &nb_types[7]);
		else if (!strncmp(map[i], "4", 1))
			parse_new_textures(map[i], 2, &nb_types[8]);
		else if (!strncmp(map[i], "5", 1))
			parse_new_textures(map[i], 3, &nb_types[9]);
		else if (!strncmp(map[i], "6", 1))
			parse_new_textures(map[i], 4, &nb_types[10]);
		else if (!strncmp(map[i], "7", 1))
			parse_new_textures(map[i], 5, &nb_types[11]);
		else if (!strncmp(map[i], "8", 1))
			parse_new_textures(map[i], 6, &nb_types[12]);
		else if (!strncmp(map[i], "9", 1))
			parse_new_textures(map[i], 7, &nb_types[13]);
		else if (!strncmp(map[i], "A", 1))
			parse_new_textures(map[i], 8, &nb_types[14]);
		else if (!strncmp(map[i], "B", 1))
			parse_new_textures(map[i], 9, &nb_types[15]);
		else if (is_nb_args(nb_types) && index == -1)
			index = i;
		++i;
	}
	if (!is_nb_args(nb_types))
	{
		printf("Error\n");
		// ft_black_hole(1);
	}
	printf(">>> %s\n", map[index]);
	while (is_empty(map[index]))
		index++;
	check_map(map, index);
	ft_find_wall_scale();
}
