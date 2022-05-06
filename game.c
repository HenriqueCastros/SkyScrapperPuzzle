/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hecastro <hecastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 01:09:54 by hecastro          #+#    #+#             */
/*   Updated: 2022/04/18 01:52:57 by hecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "rush.h"

void	print_game(t_Game game)
{
	int		i;
	int		j;
	int		k;
	char	aux;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4 && game.towers[j][i][k] == '-')
				k++;
			aux = game.towers[j][i][k];
			write(1, &aux, 1);
			if (j != 3)
				write(1, " ", 1);
			j++;
		}
		i++;
		write(1, "\n", 1);
	}
}

// uses the colup/coldown and rowleft/rowright pairs
//	to evaluate which combination the col/row should follow
//	i.e.: rowup = 4, rowdown = 1 --> 1234;
void	set_combinations(t_Game *game)
{
	int	i;
	int	a;
	int	b;

	i = 0;
	while (i < 4)
	{
		a = game->col_up[i];
		b = game->col_down[i];
		game->combinations[i] = (char **) get_possible_combinations(a, b);
		i++;
	}
	while (i < 8)
	{
		a = game->row_left[i - 4];
		b = game->row_right[i - 4];
		game->combinations[i] = (char **) get_possible_combinations(a, b);
		i++;
	}
}

// Initializes all tower with the values 1234\0
t_Game	*init_posibilities(t_Game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			game->towers[i][j][0] = '1';
			game->towers[i][j][1] = '2';
			game->towers[i][j][2] = '3';
			game->towers[i][j][3] = '4';
			game->towers[i][j][4] = '\0';
			j++;
		}
		i++;
	}
	return (game);
}

// Initializes a game object
// 	Step 1: refer to init_posibilities
//	Step 2: sets colup, coldown, rowleft and rowright values based on param
//	Step 3: refer to set_combinations
// @param *view -> array passed by user with coll and row restrictions
t_Game	*init_game(int *view)
{
	t_Game	*game;
	int		i;
	int		j;

	game = malloc(sizeof(t_Game));
	game = init_posibilities(game);
	i = 0;
	j = 0;
	while (j < 4)
		game->col_up[j++] = view[i++];
	j = 0;
	while (j < 4)
		game->col_down[j++] = view[i++];
	j = 0;
	while (j < 4)
		game->row_left[j++] = view[i++];
	j = 0;
	while (j < 4)
		game->row_right[j++] = view[i++];
	set_combinations(game);
	return (game);
}
