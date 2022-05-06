/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hecastro <hecastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:40:18 by hecastro          #+#    #+#             */
/*   Updated: 2022/04/18 02:48:41 by hecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "rush.h"

// Evaluates which values a tower CANNOT have based upon
//	its row and col restriction. 
// @param col - current tower column
// @param row - current tower row
// To do that it does the following:
// Step 1: initializes possible_values, an array that indicates
//			wether a value is possible in the col and row
// Step 2: if a value is possible for the current col, set possible value to 1 
//				I.e.: if 2 is valid then possible_values[2] = 1
// Step 3: if value is valid for row 
//			AND was valid for col (possible_values[x] = 1), pos_values[x] = 2
// Step 4: if value wasnt value for col OR for row, then it isnt valid. 
//			set it to '-'. I.e.: if possible_values[x] != 2 then  x = '-' 
void	eval_tower(t_Game *game, int col, int row)
{
	int	i;
	int	possible_values[4];

	i = 0;
	while (i < 4)
		possible_values[i++] = 0;
	i = 0;
	while (game->combinations[col][i])
		possible_values[game->combinations[col][i++][row] - 49] = 1;
	i = 0;
	while (game->combinations[row + 4][	])
	{
		if (possible_values[game->combinations[row + 4][i][col] - 49] == 1)
			possible_values[game->combinations[row + 4][i][col] - 49] = 2;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (possible_values[i] != 2)
			game->towers[col][row][i] = '-';
		i++;
	}
}

// Based on a tower's position return wether if it has only one possible value
// @return -1 --> indicates that there are no possible values (error)
// @return -2 --> there are more than possible value for the tower
//				 (yes, there is probably a better value for this return LOL)
// @return  X --> If there is just one possible value for a tower,
// 					return the value
int	get_possible_values(t_Game *game, int col, int row)
{
	int		values;
	int		flag;
	char	*tower_values;
	int		j;

	tower_values = game->towers[col][row];
	values = 0;
	j = 0;
	while (j < 4)
	{
		if (tower_values[j] != '-')
		{
			values++;
			flag = j;
		}
		j++;
	}
	if (values == 0)
		return (-1);
	if (values == 1)
		return (flag);
	return (-2);
}

// Removes specified value from all towers in specified col and row, excluding
// 	the tower on (col, row) position. After removing the value from a tower
//	the function will check if it was left with just one value
//	If so the function will b called recursive
// @param remove --> value to be removed
void	remove_value(t_Game *game, int remove, int col, int row)
{
	int	aux;
	int	i;

	i = 0;
	while (i < 4)
	{
		if (i != row && game->towers[col][i][remove] != '-')
		{
			game->towers[col][i][remove] = '-';
			aux = get_possible_values(game, col, i);
			if (aux >= 0)
				remove_value(game, aux, col, i);
		}
		if (i != col && game->towers[i][row][remove] != '-')
		{
			game->towers[i][row][remove] = '-';
			aux = get_possible_values(game, i, row);
			if (aux >= 0)
				remove_value(game, aux, i, row);
		}
		i++;
	}
}

// If a tower has ONLY ONE possible value, remove the value from other towers
//	possible value list. The towers that will have the value removed are the
//	in the same col or same row as the current tower
int	assign_tower(t_Game *game, int col, int row)
{
	int		values;
	char	*tower_values;

	tower_values = game->towers[col][row];
	values = get_possible_values(game, col, row);
	if (values == -1)
	{
		error();
		return (1);
	}
	else if (values >= 0)
		remove_value(game, values, col, row);
	return (0);
}

// Solves the game int two steps:
//	Step 1: removes values that dont follow the specified restrictions
//	Step 2: searches towers that have only one possible value remaning
//			 and removes it from other towers' possible values
int	solve_game(t_Game *game)
{
	int	k;
	int	j;
	int	error_flag;

	k = 0;
	while (k < 4)
	{
		j = 0;
		while (j < 4)
		{
			eval_tower(game, k, j);
			j++;
		}
		k++;
	}
	error_flag = 0;
	k = 0;
	while (k < 4 && error_flag == 0)
	{
		j = 0;
		while (j < 4 && error_flag == 0)
			error_flag = assign_tower(game, k, j++);
		k++;
	}
	return (error_flag);
}
