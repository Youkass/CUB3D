/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:45:56 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/28 11:09:46 by yobougre         ###   ########.fr       */
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
		img = malloc(sizeof(t_data));
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
-Singleton for the enum tab 
*/

t_player	*_player(void)
{
	static t_player	*player = NULL;
	if (!player)
		player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);

	return (player);
}

/*
-Singleton for all var
*/
t_var	*_var(void)
{
	static	t_var	var;

	return (&var);
}