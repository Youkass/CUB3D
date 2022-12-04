/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:50:49 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

int	ft_recv_players(t_send_server *o_player, int size)
{
	int	i;

	i = recv(_var()->socket, o_player, size, MSG_WAITALL);
	if (i < 0)
		return (1);
	return (0);
}

int	ft_recv_one(int socket, t_send_client *player, int size)
{
	int	i;

	i = recv(socket, player, size, MSG_WAITALL);
	if (i < 0)
		return (1);
	return (0);
}
