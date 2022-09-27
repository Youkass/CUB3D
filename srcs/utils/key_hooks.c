/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:55:05 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/27 18:25:35 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	ft_hook(int keycode, t_mlx *mlx)
{
	int	i;

	i = 0;
	(void)mlx;
	while (i < MAX_KEYS)
	{
		printf("id : %d\n",_enum_key()[i].id);
		if (_enum_key()[i].id == keycode)
		{
			return (_enum_key()[i].ft_hook_key());
		}
		++i;
	}
	return (0);
}

int	ft_forward(void)
{
	printf("i'm moving forward\n");
	_player()->y += 5;
	return (0);
}

int	ft_back(void)
{
	printf("i'm moving backward\n");
	_player()->y -= 5;
	return (0);
}

int	ft_left(void)
{
	printf("i'm moving left\n");
	_player()->x -= 5;
	return (0);
}

int	ft_right(void)
{
	printf("i'm moving right\n");
	_player()->x += 5;
	return (0);
}

int	ft_escape(void)
{
	exit(1);
}
