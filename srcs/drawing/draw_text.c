/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:20:26 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/21 21:46:34 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	is_allow_alpha(char c)
{
	if ((c < '0' || c > '9') && (c < 'A' && c > 'Z') && c != '_')
		return (0);
	return (1);
}

char	char_up(char c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

void	draw_text(char *text, t_vector2D pos, t_data *img)
{
	t_vector2D	tmp;
	int			i;
	int			len;

	tmp = pos;
	i = 0;
	len = ft_strlen(text);
	while (i < len)
	{
		if (!is_allow_alpha(text[i]))
			ft_put_image_to_image(*img, _var()->alpha['_'], tmp);
		else
			ft_put_image_to_image(*img, _var()->alpha[(int)char_up(text[i])], tmp);
		tmp.x += 42;
		if (tmp.x + 42 >= WIN_W)
		{
			tmp.x = pos.x;
			tmp.y += 42;
		}
		if (tmp.y + 42 > WIN_H)
			return ;
		i++;
	}
}