/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 22:28:01 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 20:27:45 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	is_map(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n' && is_wall(str[i]) && str[i] != '0'
			&& !is_player(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	mandatory_args(char *str, int nb_types[16])
{
	if (!strncmp(str, "NO", 2))
		parse_dir(str, 0, &nb_types[0]);
	else if (!strncmp(str, "SO", 2))
		parse_dir(str, 1, &nb_types[1]);
	else if (!strncmp(str, "WE", 2))
		parse_dir(str, 2, &nb_types[2]);
	else if (!strncmp(str, "EA", 2))
		parse_dir(str, 3, &nb_types[3]);
	else if (!strncmp(str, "F", 1))
		parse_color(str, 0, &nb_types[4]);
	else if (!strncmp(str, "C", 1))
		parse_color(str, 1, &nb_types[5]);
	else
		return (0);
	return (1);
}

int	specials_args(char *str, int nb_types[16])
{
	if (!strncmp(str, "2", 1))
		parse_new_textures(str, 0, &nb_types[6]);
	else if (!strncmp(str, "3", 1))
		parse_new_textures(str, 1, &nb_types[7]);
	else if (!strncmp(str, "4", 1))
		parse_new_textures(str, 2, &nb_types[8]);
	else if (!strncmp(str, "5", 1))
		parse_new_textures(str, 3, &nb_types[9]);
	else if (!strncmp(str, "6", 1))
		parse_new_textures(str, 4, &nb_types[10]);
	else if (!strncmp(str, "7", 1))
		parse_new_textures(str, 5, &nb_types[11]);
	else if (!strncmp(str, "8", 1))
		parse_new_textures(str, 6, &nb_types[12]);
	else if (!strncmp(str, "9", 1))
		parse_new_textures(str, 7, &nb_types[13]);
	else if (!strncmp(str, "A", 1))
		parse_new_textures(str, 8, &nb_types[14]);
	else if (!strncmp(str, "B", 1))
		parse_new_textures(str, 9, &nb_types[15]);
	else if (!strncmp(str, "D", 1))
		parse_new_textures(str, 10, &nb_types[16]);
	else
		return (0);
	return (1);
}

int	get_args(char **map, int i, int *index, int nb_types[16])
{
	if (!strncmp(map[i], ".", 1))
	{
		if (!is_nb_args(nb_types))
			ft_black_hole(13);
		*index = i + 1;
		return (0);
	}
	else if (!mandatory_args(map[i], nb_types))
	{
		if (!specials_args(map[i], nb_types))
		{
			if (is_nb_args(nb_types) && *index == -1)
				*index = i;
			else if (!is_empty(map[i]) && !is_map(map[i]))
				ft_black_hole(14);
		}
	}
	return (1);
}

void	parse_args(char **map)
{
	int	nb_types[17];
	int	index;
	int	i;

	i = 0;
	index = -1;
	memset(&nb_types, 0, sizeof(nb_types));
	while (map[i])
	{
		if (!get_args(map, i, &index, nb_types))
			break ;
		++i;
	}
	if (!is_nb_args(nb_types))
		ft_black_hole(15);
	while (is_empty(map[index]))
		index++;
	check_map(map, index);
	ft_find_wall_scale();
}
