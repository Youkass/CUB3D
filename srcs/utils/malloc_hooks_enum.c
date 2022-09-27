/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_hooks_enum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:19:44 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/27 12:34:00 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	ft_malloc_enum_key()
{
	_enum_key() = malloc(sizeof(t_enum_key) * MAX_KEYS);
	if (!_enum())
		return (1);
}

void	ft_init_enum_key(void)
{
	_enum_key()[0].id = 119;
	_enum_key()[0].ft_hook_key = &ft_forward;
	_enum_key()[1].id = 115;
	_enum_key()[1].ft_hook_key = &ft_back;
	_enum_key()[2].id = 97;
	_enum_key()[2].ft_hook_key = &ft_left;
	_enum_key()[3].id = 100;
	_enum_key()[3].ft_hook_key = &ft_right;
	_enum_key()[4].id = 65307;
	_enum_key()[4].ft_hook_key = &ft_escape;
}
