/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:54:09 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 18:55:02 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

char	*ft_get_ip_input(void)
{
	char	*buf;
	int		r;

	buf = ft_malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf)
		return (NULL);
	r = read(STDIN_FILENO, buf, BUFFER_SIZE);
	if (r < 0)
		return (NULL);
	buf[r] = 0;
	return (buf);
}

int	ft_init_client_first(void)
{
	if (recv(_var()->socket, &(_player()->id), sizeof(int), MSG_WAITALL) <= 0)
		return (EXIT_FAILURE);
	if (recv(_var()->socket, &(_var()->nb_player), sizeof(int),
			MSG_WAITALL) <= 0)
		return (EXIT_FAILURE);
	if (recv(_var()->socket, &(_var()->pid), sizeof(int), MSG_WAITALL) <= 0)
		return (EXIT_FAILURE);
	if (_player()->id == 0)
	{
		if (send(_var()->socket, &(_var()->map), sizeof(_var()->map), 0) <= 0)
			return (EXIT_FAILURE);
		if (send(_var()->socket, &(_var()->map_width),
				sizeof(_var()->map_width), 0) <= 0)
			return (EXIT_FAILURE);
		if (send(_var()->socket, &(_var()->map_height),
				sizeof(_var()->map_height), 0) <= 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
