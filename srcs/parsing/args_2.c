/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:05:31 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/05 16:13:03 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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

void	arg_check(char *str, int nb_types[6], int *index, int i)
{
	if (!strncmp(str, "NO", 2))
		parse_dir(str, 0, &nb_types[0]);
	else if (!strncmp(str, "SO", 2))
		parse_dir(str, 2, &nb_types[2]);
	else if (!strncmp(str, "WE", 2))
		parse_dir(str, 1, &nb_types[1]);
	else if (!strncmp(str, "EA", 2))
		parse_dir(str, 3, &nb_types[3]);
	else if (!strncmp(str, "F", 1))
		parse_color(str, 0, &nb_types[4]);
	else if (!strncmp(str, "C", 1))
		parse_color(str, 1, &nb_types[5]);
	else if (is_nb_args(nb_types) && *index == -1)
		*index = i;
	else if (!is_empty(str) && !is_map(str))
	{
		printf("Error\n%s Unrecognized argument\n", str);
		ft_black_hole(0);
	}
}

void	parse_args(char **map)
{
	int	nb_types[6];
	int	index;
	int	i;

	i = 0;
	index = -1;
	memset(&_img()->map, 0, sizeof(_img()->map));
	memset(&nb_types, 0, sizeof(nb_types));
	while (map[i])
	{
		arg_check(map[i], nb_types, &index, i);
		++i;
	}
	if (!is_nb_args(nb_types))
	{
		printf("Error\nToo many arguments\n");
		ft_black_hole(1);
	}
	while (is_empty(map[index]))
		index++;
	check_map(map, index);
}
