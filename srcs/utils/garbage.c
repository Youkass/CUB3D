/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:09:39 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/30 19:51:58 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (*lst)
	{
		while (*lst != NULL)
		{
			tmp = (*lst)->next;
			if ((*lst)->content != NULL)
				(del)((*lst)->content);
			free(*lst);
			*lst = tmp;
		}
	}
}

void	ft_lstclear_img(t_list **lst)
{
	t_list	*tmp;

	if (*lst)
	{
		while (*lst != NULL)
		{
			tmp = (*lst)->next;
			if ((*lst)->content != NULL)
				mlx_destroy_image(_mlx()->mlx, (*lst)->content);
			free(*lst);
			*lst = tmp;
		}
	}
}

void	ft_lstclear_media(t_list **lst)
{
	t_list	*tmp;

	if (*lst)
	{
		while (*lst != NULL)
		{
			tmp = (*lst)->next;
			if ((*lst)->content != NULL)
				ma_sound_uninit((*lst)->content);
			free(*lst);
			*lst = tmp;
		}
	}
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = *alst;
	if (tmp == NULL)
	{
		*alst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_list	*_lst(void)
{
	static t_list	*lst = NULL;

	if (!lst)
	{
		lst = malloc(sizeof(t_list));
		if (!lst)
			ft_black_hole(1); //TODO this gotta be the first exit 
		lst->next = NULL;
		lst->content = NULL;
	}
	return (lst);
}

t_list	*_lstimg(void)
{
	static t_list	*lst = NULL;

	if (!lst)
	{
		lst = malloc(sizeof(t_list));
		if (!lst)
			ft_black_hole(139); //TODO this gotta be the first exit 
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
			ft_black_hole(139); //TODO this gotta be the first exit 
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
		ft_black_hole(139); //TODO
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
}

void	ft_black_hole(int exit_code)
{
	t_list	*tmp;
	t_list	*tmp_2;
	t_list	*tmp_3;
	t_media	*media;

	exit_say_error(exit_code);
	tmp = _lst();
	tmp_2 = _lstimg();
	ft_lstclear_img(&tmp_2);
	if (IS_MUSIC == 1)
	{
		tmp_3 = _lstmedia();
		media = _media();
		ft_lstclear_media(&tmp_3);
		ma_engine_uninit(&media->engine);
	}
	mlx_destroy_image(_mlx()->mlx, _img()->img);
	mlx_destroy_window(_mlx()->mlx, _mlx()->mlx_win);
	mlx_destroy_display(_mlx()->mlx);
	free(_mlx()->mlx);
	ft_lstclear(&tmp, free);
	exit(exit_code);
}
