/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 22:28:01 by dasereno          #+#    #+#             */
/*   Updated: 2022/11/30 15:14:35 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	parse_dir(char *str, int index, int *nb)
{
	int		i;
	int		j;
	char	*new;

	i = 2;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	new = ft_malloc(sizeof(char) * ft_strlen(str));
	while (str[i] && (str[i] != ' ' || str[i] == '\t'))
		new[j++] = str[i++];
	new[j] = 0;
	_var()->dir[index] = generate_image(new);
	*nb += 1;
	error_dir(new, index, nb, str);
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
		ft_black_hole(1);
	}
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		*i += 1;
}

void	is_error(int tmp, int k, int j)
{
	if (tmp > 255 || tmp < 0)
	{
		printf("Error\n%d is not in color range (0-255)\n", tmp);
		ft_black_hole(1);
	}
	else if (k > 3 || j > 3)
	{
		printf("Error\nToo many instructions\n");
		ft_black_hole(1);
	}
}

void	body_color(t_vector3D *it, char *str, int index)
{
	int		tmp;
	char	buf[5];

	it->y = 0;
	buf[0] = 0;
	while (str[it->x] && str[it->x] >= '0' && str[it->x] <= '9' && it->y < 4)
		buf[it->y++] = str[it->x++];
	buf[it->y] = 0;
	tmp = atoi(buf);
	jump_spaces(&it->x, str, it->z);
	_var()->colors[index][it->z++] = tmp;
	is_error(tmp, it->z, it->y);
}

void	parse_color(char *str, int index, int *nb)
{
	t_vector3D	it;

	it.x = 1;
	while (str[it.x] && (str[it.x] == ' ' || str[it.x] == '\t'))
		it.x++;
	it.z = 0;
	*nb += 1;
	while (str[it.x])
		body_color(&it, str, index);
	if (*nb > 1)
	{
		printf("Error\n[%c]: Already defined\n", str[0]);
		ft_black_hole(1);
	}
	_var()->colors[index][it.z] = 100;
}
