/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:45:56 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/01 10:20:21 by yobougre         ###   ########.fr       */
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
		img = malloc(sizeof(t_data));
		memset(img, 0, sizeof(t_data));
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
		mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	return (mlx);
}

/*
-Singleton player
*/
t_obj	*_player(void)
{
	static t_obj	player;

	return (&player);
	//if (!player)
	//	player = malloc(sizeof(t_obj));
	//if (!player)
	//	return (NULL);
	//return (player);
}

/*
-Singleton for the raycasting data
*/
t_raycasting	**_ray(void)
{
	static t_raycasting	**ray = NULL;

	if (!ray)
	{
		ray = malloc(sizeof(t_raycasting *) * TH_RAY);
		for (int i = 0; i < TH_RAY; i++)
			ray[i] = malloc(sizeof(t_raycasting));
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
	
	return (&var);
}
