/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:16:19 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/03 20:51:38 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
-Cast two int in t_vector2D.
*/
t_vector2D	pos(int x, int y)
{
	t_vector2D	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

/*
-Cast two int in t_vector2F.
*/
t_vector2F	posf(float x, float y)
{
	t_vector2F	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vector3F	pos3f(float x, float y, float z)
{
	t_vector3F	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

char	*ft_strdup(const char *s)
{
	char	*new;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	new = ft_malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = 0;
	return (new);
}
