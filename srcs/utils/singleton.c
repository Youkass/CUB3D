/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:45:56 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/01 18:22:52 by dasereno         ###   ########.fr       */
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
		img = ft_malloc(sizeof(t_data));
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
		mlx = ft_malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	return (mlx);
}

t_media	*_media(void)
{
	static t_media	*media = NULL;

	if (!media)
		media = ft_malloc(sizeof(t_media));
	if (!media)
		return (NULL);
	return (media);
}

/*
-Singleton player
*/
t_obj	*_player(void)
{
	static t_obj	player;

	return (&player);
}

/*
-Singleton for the raycasting data
*/
t_raycasting	**_ray(void)
{
	static t_raycasting	**ray = NULL;
	int					i;

	if (!ray)
	{
		ray = ft_malloc(sizeof(t_raycasting *) * TH_RAY);
		i = 0;
		while (i < TH_RAY)
			ray[i++] = ft_malloc(sizeof(t_raycasting));
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
	static t_var	*var = NULL;

	if (var == NULL)
	{
		var = ft_malloc(sizeof(t_var));
		if (!var)
			printf("le ft_malloc pet\n");
	}
	return (var);
}

t_log	*_log(void)
{
	static t_log	*log = NULL;

	if (log == NULL)
	{
		log = ft_malloc(sizeof(t_log));
		if (!log)
			ft_black_hole(137);
	}
	return (log);
}
