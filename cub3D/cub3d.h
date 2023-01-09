/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:29:08 by mabdelba          #+#    #+#             */
/*   Updated: 2023/01/09 19:30:17 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mlx.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef	struct textsize
{
	int	textlines;
	int maplines;
	int	longest;
}				s_size;

typedef	struct s_map
{
	char	**matrice;
	int		x;
	int		y;
}				t_map;

typedef struct s_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
}			t_data;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
int		ft_schr(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_sjoin(char *s1, char *s2);
void	parsing(int ac, char **av, t_data *data, t_map *map);
int		ft_spllen(char **spl);
int		openfile(char *str);
void	error_function(char *str);
s_size	ft_textsize(int fd);
bool	check_extension(char *str, char *ext);
void	check_map(t_map *map);

#endif