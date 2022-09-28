/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:45:17 by darian            #+#    #+#             */
/*   Updated: 2022/09/27 18:14:42 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, t_alloc **alloc)
{
	int		i;
	char	*str;

	i = 0;
	printf("llo\n");
	str = ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1), alloc);
	if (!str)
		return (NULL);
	while (s1 && *s1)
	{
		str[i++] = *s1;
		s1++;
	}
	while (s2 && *s2)
	{
		str[i++] = *s2;
		s2++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strjoin_char(char const *s1, char const s2, t_alloc **alloc)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_malloc(sizeof(char) * (ft_strlen(s1) + 2), alloc);
	if (!str)
		return (NULL);
	while (s1 && *s1)
	{
		str[i++] = *s1;
		s1++;
	}
	str[i++] = s2;
	str[i] = 0;
	return (str);
}
