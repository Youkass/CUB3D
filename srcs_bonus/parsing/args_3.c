/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:00:21 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

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
	_image()->dir[index] = generate_image(new);
	*nb += 1;
	if (!_image()->dir[index].img || *nb > 1)
		ft_black_hole(20);
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
	new = ft_malloc(sizeof(char) * ft_strlen(str));
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
}
