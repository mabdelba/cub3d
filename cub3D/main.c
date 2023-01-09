/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:27:20 by mabdelba          #+#    #+#             */
/*   Updated: 2023/01/09 19:53:39 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// typedef struct s_vars {
// 	void	*mlx;
// 	void	*win;
// }				t_vars;

// int	key_hook(int keycode)
// {
// 	if (keycode == 53)
// 		exit(0);
// 	return (0);
// }
// int	mouse_hook(int keycode)
// {
// 	if (keycode == 3)
// 		exit(0);
// 	return (0);
// }

void	check_texdata(t_data *data)
{
	if(!data->no || !data->so || !data->we || 
				!data->ea || !data->f || !data->c)
		error_function("Incomplet Map");
}

void	print_map(char **str)
{
	printf("####################################\n");
	int i = 0;
	while(str[i])
	{
		printf("{%s}\n", str[i]);
		i++;
	}
	printf("####################################\n");
}
int main(int ac, char **av)
{
	t_data data;
	t_map	map;
	parsing(ac, av, &data, &map);
	check_texdata(&data);
	printf("\nValide Map\n");
	printf("NO: %s\n", data.no);
	printf("SO: %s\n", data.so);
	printf("WE: %s\n", data.we);
	printf("EA: %s\n", data.ea);
	printf("F: %s\n", data.f);
	printf("C: %s\n", data.c);
	
	print_map(map.matrice);

	printf("x of player: %d\n", map.x);
	printf("y of player: %d\n", map.y);

	
	// system("leaks cub3D");
	// t_vars	vars;

	// vars.mlx = mlx_init();
	// vars.win = mlx_new_window(vars.mlx, 640, 400, "Abdelbar");
	// mlx_key_hook(vars.win, key_hook, &vars);
	// mlx_mouse_hook(vars.win, mouse_hook, &vars);
	// mlx_loop(vars.mlx);
}

