/* ************************************************************************** */
/*                                                                            */ /*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:45:15 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/18 00:22:03 by yuro4ka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

char	*ft_get_ip_input(void)
{
	char	*buf;
	int		r;

	printf("Enter Host Ip on the next line : \n");
	buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf)
		return (NULL);
	r = read(STDIN_FILENO, buf, BUFFER_SIZE);
	if (r < 0)
		return (NULL);
	buf[r] = 0;
	return (buf);

}

int	ft_init_client(void)
{
	int			ret;

	_img()->socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_img()->is_host == SERVER)
		_img()->client.sin_addr.s_addr = inet_addr(ft_get_host_ip());
	else if (_img()->is_host == CLIENT) 
		_img()->client.sin_addr.s_addr = inet_addr(ft_get_ip_input());
	_img()->client.sin_family = AF_INET;
	_img()->client.sin_port = htons(30000);
	printf("MAIS NIQUE TA MERE\n");
	ret = connect(_img()->socket,
		(const struct sockaddr *)&(_img()->client), sizeof(_img()->client));
	if (ret < 0)
		return (EXIT_FAILURE);
	printf("connecté\n");
	recv(_img()->socket, &ret, sizeof(ret), 0);
	_player()->id = ret;
	return (EXIT_SUCCESS);
}

void	ft_pong_client()
{
	t_obj	player;
	int		i;
	
	player = *_player();
	i = 0;
	send(_img()->socket, &player, sizeof(player), 0);
	while (i < _img()->nb_player)
	{
		if (player.id != i)
		{
			recv(_img()->socket, &player, sizeof(player), 0);
			_var()->o_player[player.id] = player;
		}
		++i;
	}

}
