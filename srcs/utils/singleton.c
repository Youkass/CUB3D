/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:45:56 by yobougre          #+#    #+#             */
/*   Updated: 2023/12/21 14:17:17 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
-Singleton for the image
*/
t_data	*_img(void)
{
	static t_data	*img = NULL;

	if (!img)
	{
		ft_memset(&img, 0, sizeof(img));
		img = ft_malloc(sizeof(t_data));
	}
	if (!img)
		return (NULL);
	return (img);
}

/*
-Singleton for the mlx datas
*/
t_mlx	*_mlx(void)
{
	static t_mlx	*mlx = NULL;

	if (!mlx)
	{
		ft_memset(&mlx, 0, sizeof(mlx));
		mlx = ft_malloc(sizeof(t_mlx));
	}
	if (!mlx)
		return (NULL);
	return (mlx);
}

/*
-Singleton for the enum tab 
*/
t_obj	*_player(void)
{
	static t_obj	*player = NULL;

	if (!player)
	{
		ft_memset(&player, 0, sizeof(player));
		player = ft_malloc(sizeof(t_obj));
	}
	if (!player)
		return (NULL);
	return (player);
}

/*
-Singleton for the raycasting data
*/
t_raycasting	*_ray(void)
{
	static t_raycasting	*ray = NULL;

	if (!ray)
	{
		ft_memset(&ray, 0, sizeof(ray));
		ray = ft_malloc(sizeof(t_raycasting));
	}
	if (!ray)
		return (NULL);
	return (ray);
}

/*
-Singleton for all var
*/
t_var	*_var(void)
{
	static t_var	var;
	static int		i = 0;

	if (!i)
	{
		++i;
		ft_memset(&var, 0, sizeof(var));
	}
	return (&var);
}
