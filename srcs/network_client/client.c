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

void	ft_copy_data_before_pong(t_obj *player)
{
	player->id = _player()->id;
	player->x = _player()->x;
	player->y = _player()->y;
	player->z = _player()->z;
	player->c = _player()->c;
	player->dx = _player()->dx;
	player->dy = _player()->dy;
	player->da = _player()->da;
	player->old_dx = _player()->old_dx;
	player->old_dy = _player()->old_dy;
	player->angle = _player()->angle;
	player->move_speed = _player()->move_speed;
	player->rot_speed = _player()->rot_speed;
	player->is_walking = _player()->is_walking;
	player->is_dead = _player()->is_dead;
	player->start_dead = _player()->start_dead;
	player->death_n = _player()->death_n;
	player->death_start = _player()->death_start;
	player->shooted = _player()->shooted;
	player->dif = _player()->dif;
	player->old_plane = _player()->old_plane;
	player->hb = _player()->hb;
	player->pitch = _player()->pitch;
    player->health = _player()->health;
    player->weapon_id = _player()->weapon_id;
    player->ammo = _player()->ammo;
}

void	ft_pong_client(void)
{
	t_obj	player;
	int		i;
	
	i = 0;
	memset(&player, 0, sizeof(player));
	ft_copy_data_before_pong(&player);
	send(_img()->socket, &player, sizeof(player), 0);
	while (i < _img()->nb_player)
	{
		recv(_img()->socket, &player, sizeof(player), 0);
		if (player.shooted.shoot == 1 && player.shooted.id == _player()->id)
			_player()->health -= _var()->weapon[player.weapon_id].power;
		if (player.shooted.shoot == 1 && player.id == _player()->id)
		{
			_player()->shooted.shoot = 0;
			_player()->shooted.id = -1;
		}
		_var()->o_player[player.id] = player;
		++i;
	}
}
