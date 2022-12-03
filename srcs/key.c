/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:04:46 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 20:33:36 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	ft_get_key_next(int keycode)
{
	if (keycode == F)
		_var()->key[f] = 1;
	if (keycode == ESC)
		_var()->key[esc] = 1;
	if (keycode == E)
		_var()->key[e] = 1;
	if (keycode == ARR_UP)
		_var()->key[up] = 1;
	if (keycode == ARR_DOWN)
		_var()->key[down] = 1;
	if (keycode == ARR_LEFT)
		_var()->key[left] = 1;
	if (keycode == ARR_RIGHT)
		_var()->key[right] = 1;
	if (keycode == SPACE)
		_var()->key[space] = 1;
	if (keycode == MAJ)
		_var()->key[maj] = 1;
	if (keycode == R)
		_var()->key[r] = 1;
}

void	get_key(int keycode)
{
	if (keycode == CTRL)
		_var()->key[ctrl] = 1;
	if (keycode == A_)
		_var()->key[a] = 1;
	if (keycode == W)
		_var()->key[w] = 1;
	if (keycode == S_)
		_var()->key[s] = 1;
	if (keycode == D)
		_var()->key[d] = 1;
	if (keycode == ONE)
		_var()->key[one] = 1;
	if (keycode == TWO)
		_var()->key[two] = 1;
	if (keycode == THREE)
		_var()->key[three] = 1;
	ft_get_key_next(keycode);
}

static void	ft_release_next(int keycode)
{
	if (keycode == ESC)
		_var()->key[esc] = 0;
	if (keycode == ARR_UP)
		_var()->key[up] = 0;
	if (keycode == ARR_DOWN)
		_var()->key[down] = 0;
	if (keycode == ARR_LEFT)
		_var()->key[left] = 0;
	if (keycode == ARR_RIGHT)
		_var()->key[right] = 0;
	if (keycode == SPACE)
		_var()->key[space] = 0;
	if (keycode == MAJ)
		_var()->key[maj] = 0;
	if (keycode == R)
		_var()->key[r] = 0;
	if (keycode == ONE)
		_var()->key[one] = 0;
	if (keycode == TWO)
		_var()->key[two] = 0;
	if (keycode == THREE)
		_var()->key[three] = 0;
	if (keycode == F)
		_var()->key[f] = 0;
	if (keycode == E)
		_var()->key[e] = 0;
}

int	ft_release(int keycode)
{
	if (keycode == A_)
	{
		_var()->key[a] = 0;
		_player()->is_walking = 0;
	}
	if (keycode == CTRL)
		_var()->key[ctrl] = 0;
	if (keycode == W)
	{
		_var()->key[w] = 0;
		_player()->is_walking = 0;
	}
	if (keycode == S_)
	{
		_var()->key[s] = 0;
		_player()->is_walking = 0;
	}
	if (keycode == D)
	{
		_var()->key[d] = 0;
		_player()->is_walking = 0;
	}
	ft_release_next(keycode);
	return (0);
}
