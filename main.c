/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hecastro <hecastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:16:47 by hecastro          #+#    #+#             */
/*   Updated: 2022/04/18 02:12:26 by hecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "rush.h"

// Validates arg passed on cli. Validations rules are as followed:
// 	1 -	If arg count is different than 2, args are invalid.
// 	2 -	If any char other than 1, 2, 3, 4 and ' ' is invalid
// 	3 -	Number must be followed by either a ' ' or \0.
// @return -> 0 	 - arguments invalid
//		   -> *views - arguments valid and returned
int	*validate_args(int argc, char *argv)
{
	int	*views;
	int	i;

	i = 0;
	if (argc != 2)
		return (0);
	views = (int *) malloc(16 * sizeof(int));
	while (*argv != '\0')
	{
		if ((*argv < '1' || *argv > '4') && *argv != ' ')
			return (0);
		if (*argv >= '1' && *argv <= '4')
		{
			if (*(argv + 1) != ' ' && *(argv + 1) != '\0')
				return (0);
			views[i++] = *argv - '0';
		}
		if (i > 16)
			return (0);
		argv++;
	}
	if (i < 16)
		return (0);
	return (views);
}

int	main(int argc, char *argv[])
{
	int		*views;
	t_Game	*game;

	views = validate_args(argc, argv[1]);
	if (views != 0) // se ele nao for nulo
	{
		game = init_game(views);
		if (!solve_game(game))
			print_game(*game);
	} // se ele for nulo
	else
		error();
	return (0);
}
