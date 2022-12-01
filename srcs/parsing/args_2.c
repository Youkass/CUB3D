/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:59:52 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/01 16:00:47 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	jump_spaces(int *i, char *str, int k)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		*i += 1;
	if (str[*i] == ',')
		*i += 1;
	else if (k != 2)
		ft_black_hole(21);
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		*i += 1;
}

void	is_error(int tmp, int k, int j)
{
	if (tmp > 255 || tmp < 0)
		ft_black_hole(16);
	else if (k > 3 || j > 3)
		ft_black_hole(17);
}

void	parse_color(char *str, int index, int *nb)
{
	t_vector3D	it;
	int			tmp;
	char		buf[5];

	it.x = 1;
	while (str[it.x] && (str[it.x] == ' ' || str[it.x] == '\t'))
		it.x++;
	it.z = 0;
	*nb += 1;
	while (str[it.x])
	{
		it.y = 0;
		buf[0] = 0;
		while (str[it.x] && str[it.x] >= '0' && str[it.x] <= '9' && it.y < 4)
			buf[it.y++] = str[it.x++];
		buf[it.y] = 0;
		tmp = atoi(buf);
		jump_spaces(&it.x, str, it.z);
		_var()->colors[index][it.z++] = tmp;
		is_error(tmp, it.z, it.y);
	}
	if (*nb > 1)
		ft_black_hole(17);
	_var()->colors[index][it.z] = 100;
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
