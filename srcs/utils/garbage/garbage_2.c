/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:10:38 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 19:18:34 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

t_list	*_lstimg(void)
{
	static t_list	*lst = NULL;

	if (!lst)
	{
		lst = malloc(sizeof(t_list));
		if (!lst)
			ft_black_hole(139);
		lst->next = NULL;
		lst->content = NULL;
	}
	return (lst);
}

t_list	*_lstmedia(void)
{
	static t_list	*lst = NULL;

	if (!lst)
	{
		lst = malloc(sizeof(t_list));
		if (!lst)
			ft_black_hole(139);
		lst->next = NULL;
		lst->content = NULL;
	}
	return (lst);
}

t_list	*ft_new_node(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		ft_black_hole(139);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	*ft_malloc(int size)
{
	void	*output;
	t_list	*tmp;

	output = malloc(size);
	tmp = _lst();
	if (!output)
		ft_black_hole(139);
	ft_lstadd_back(&tmp, ft_new_node(output));
	return (output);
}

void	exit_say_error(int exit_code)
{
	if (exit_code == 11)
		printf("Error\nInvalid numbers of arguments\n");
	else if (exit_code == 10)
		printf("Error\nMap to big: Max 1024 * 1024\n");
	else if (exit_code == 12)
		printf("Error\nMap not closed\n");
	else if (exit_code == 13)
		printf("Error\nInvalid numbers of arguments\n");
	else if (exit_code == 14)
		printf("Error\nUnrecognized argument\n");
	else if (exit_code == 15)
		printf("Error\nInvalid numbers of arguments\n");
	else if (exit_code == 16)
		printf("Error\nNumber not in color range (0-255)\n");
	else if (exit_code == 17)
		printf("Error\nToo many instructions\n");
	else if (exit_code == 18)
		printf("Error\nUnrecognized token\n");
	else if (exit_code == 19)
		printf("Error\nMap is not closed");
	else if (exit_code == 20)
		printf("Error\nInvalid path\n");
	else if (exit_code == 21)
		printf("Error\nInvalid syntax\n");
	else if (exit_code == 22)
		printf("Error\nWrong teams positions given\n");
}
