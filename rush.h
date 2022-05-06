/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hecastro <hecastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:10:06 by hecastro          #+#    #+#             */
/*   Updated: 2022/04/17 20:56:48 by hecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH_H
# define RUSH_H

// Main data structure
// colXup, colYdown, rowZleft, rowWright - values passed in cli
// towers - matrix with all towers and their posible values
//			(1,2,3,4, \0)
// combinations - array with all posible tower values based upon
//				  colup, coldown, etc.. restrictions
typedef struct t_Game {
	int		col_up[4];
	int		col_down[4];
	int		row_left[4];
	int		row_right[4];
	char	**combinations[8];
	char	towers[4][4][5];
}	t_Game;

// game.c
// functions that will be used to initialize a game "object"
void		set_combinations(t_Game *game);
t_Game		*init_posibilities(t_Game *game);
t_Game		*init_game(int *view);
void		print_game(t_Game game);

// procedures.c
// functions that will be use to solve the puzzle
//	after initializing the game structute
void		eval_tower(t_Game *game, int col, int row);
void		remove_value(t_Game *game, int remove, int col, int row);
int			assign_tower(t_Game *game, int col, int row);
int			solve_game(t_Game *game);
int			get_possible_values(t_Game *game, int col, int row);

// error.c
void		error(void);

// combinations.c
// Returns possible combinations based upon colup/coldown or rowleft/rowright
const char	**get_possible_combinations(int view_front, int view_back);

#endif
