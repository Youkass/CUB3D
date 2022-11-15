/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuro4ka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 01:57:27 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/11/15 23:38:44 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_open_intro_sprites(void)
{
	_image()->intro_sprite[0] = generate_image("./img/intro/darian_1.xpm");
	_image()->intro_sprite[1] = generate_image("./img/intro/darian_2.xpm");
	_image()->intro_sprite[2] = generate_image("./img/intro/darian_3.xpm");
	_image()->intro_sprite[3] = generate_image("./img/intro/youri_1.xpm");
	_image()->intro_sprite[4] = generate_image("./img/intro/youri_2.xpm");
	_image()->intro_sprite[5] = generate_image("./img/intro/youri_3.xpm");
	_image()->intro_sprite[6] = generate_image("./img/intro/us_1.xpm");
	_image()->intro_sprite[7] = generate_image("./img/intro/us_2.xpm");
}

void	ft_intro(void)
{
	int	clock;

	ft_open_intro_sprites();
}
