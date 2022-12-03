/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:41:58 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 17:43:57 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
This functions simplify the way to generate image. That verify if the images
couldn't be generated.
*/
t_data	generate_image(char *path)
{
	t_data	sprite;
	t_list	*tmp;

	memset(&sprite, 0, sizeof(t_data));
	tmp = _lstimg();
	if (!path)
		return (sprite);
	sprite.img = mlx_xpm_file_to_image(_mlx()->mlx, path,
			&sprite.w, &sprite.h);
	ft_lstadd_back(&tmp, ft_new_node(sprite.img));
	if (!sprite.img)
		return (sprite);
	sprite.addr = mlx_get_data_addr(sprite.img, &sprite.bits_per_pixel,
			&sprite.line_length, &sprite.endian);
	return (sprite);
}

void	gen_bar(void)
{
	_menu()->bar = ft_malloc(sizeof(t_data *) * 2);
	_menu()->bar[0] = ft_malloc(sizeof(t_data) * 3);
	_menu()->bar[0][0] = generate_image("./img/menu/bar/left_empty.xpm");
	_menu()->bar[0][1] = generate_image("./img/menu/bar/mid_empty.xpm");
	_menu()->bar[0][2] = generate_image("./img/menu/bar/right_empty.xpm");
	_menu()->bar[1] = ft_malloc(sizeof(t_data) * 3);
	_menu()->bar[1][0] = generate_image("./img/menu/bar/left_fill.xpm");
	_menu()->bar[1][1] = generate_image("./img/menu/bar/mid_fill.xpm");
	_menu()->bar[1][2] = generate_image("./img/menu/bar/right_fill.xpm");
}
