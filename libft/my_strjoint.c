/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strjoint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:25:27 by alukongo          #+#    #+#             */
/*   Updated: 2022/09/12 13:25:33 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*my_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*my_strjoin(char const *s1, char const*s2)
{
	char	*str;
	int		i;

	i = ft_strlen(s1) + ft_strlen(s2);
	if (s1 && s2)
	{
		str = malloc(sizeof(char) * i + 1);
		if (!str)
			return (0);
		ft_strcpy(str, s1);
		my_strcat(str, s2);
		return (str);
	}
	else
		return (0);
}
