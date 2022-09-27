/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:55:05 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/27 12:32:01 by yobougre         ###   ########.fr       */
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
		if (_enum_key()[i].id == keycode)
			return (_enum_key()[i].ft_hook_key());
		++i;
	}
	return (0);
}

int	ft_forward(void)
{
	printf("i'm moving forward\n");
	return (0);
}

int	ft_back(void)
{
	printf("i'm moving backward\n");
	return (0);
}

int	ft_left(void)
{
	printf("i'm moving left\n");
	return (0);
}

int	ft_right(void)
{
	printf("i'm moving right\n");
	return (0);
}

int	ft_escape(void)
{
	exit(1);
}
