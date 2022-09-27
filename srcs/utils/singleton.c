/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:45:56 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/27 16:05:43 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
-Singleton for the image
*/
t_data	*_img(void)
{
	static t_data	img;

	return (&img);
}

/*
-Singleton for the mlx datas
*/
t_mlx	*_mlx(void)
{
	static t_mlx	mlx;

	return (&mlx);
}

/*
-Singleton for the enum tab 
*/
t_enum_key *_enum_key(void)
{
	static t_enum_key tab;

	return (&tab);
}

t_player	*_player(void)
{
	static t_player	player;

	return (&player);
}
