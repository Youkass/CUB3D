/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:50:49 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/05 14:14:05 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	ft_recv_players(t_send_server *o_player, int size)
{
	int	ret;
	int	i;
	
	i = 1;
	ret = 0;
	while (i)
	{
		i = recv(_var()->socket, o_player + ret, size, MSG_WAITALL);
		ret += i;
		if (ret == size)
			return (0);
		if (ret < 0 || i < 0)
			return (1);
	}
	return (0);
}

int	ft_recv_one(int socket, t_send_client *player, int size)
{
	int	ret;
	int	i;
	
	i = 1;
	ret = 0;
	while (i)
	{
		i = recv(socket, player + ret, size, MSG_WAITALL);
		ret += i;
		if (ret == size || !i)
			return (0);
		if (ret < 0 || i < 0)
			return (1);
	}
	return (0);
}
