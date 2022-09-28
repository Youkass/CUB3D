/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:30:30 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/28 11:13:48 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUC_H
# define STRUC_H

typedef struct s_vector2D
{
    int x;
    int y;
}   t_vector2D;

typedef struct s_vector3D
{
    int x;
    int y;
    int z;
}   t_vector3D;

typedef struct	s_mlx
{
	void	*mlx;
	void	*mlx_win;
}	t_mlx;

typedef struct	s_data
{	
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_data;

typedef struct	s_enum_key
{
	int	id;
	int	(*ft_hook_key)(void);
}	t_enum_key;

typedef struct	s_enum_mouse
{
	int	id;
	int	(*ft_hook_mouse)(void);
}	t_enum_mouse;

typedef struct  s_menu
{
    t_data  **buttons;
    t_data  **bar;
}   t_menu;

typedef struct  s_var
{
    t_menu  *menu;
}   t_var;

#endif
