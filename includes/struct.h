/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:30:30 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/27 14:59:41 by yobougre         ###   ########.fr       */
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

#endif
