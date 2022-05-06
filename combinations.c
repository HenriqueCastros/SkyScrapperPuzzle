/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combinations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hecastro <hecastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 12:42:55 by hecastro          #+#    #+#             */
/*   Updated: 2022/04/18 02:19:18 by hecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

const char	*g_see11[] = {NULL};
const char	*g_see12[] = {"4123", "4213", NULL};
const char	*g_see13[] = {"4312", "4231", "4132", NULL};
const char	*g_see14[] = {"4321", NULL};

const char	*g_see21[] = {"3214", "3124", NULL};
const char	*g_see22[] = {NULL};
const char	*g_see23[] = {"3421", "2431", "1432", NULL};
const char	*g_see24[] = {NULL};

const char	*g_see31[] = {"2134", "2314", "1324", NULL};
const char	*g_see32[] = {"1243", "1342", "2341", NULL};
const char	*g_see33[] = {NULL};
const char	*g_see34[] = {NULL};

const char	*g_see41[] = {"1234", NULL};
const char	*g_see42[] = {NULL};
const char	*g_see43[] = {NULL};
const char	*g_see44[] = {NULL};

const char	**g_combination[] = {
	g_see11, g_see12, g_see13, g_see14,
	g_see21, g_see22, g_see23, g_see24,
	g_see31, g_see32, g_see33, g_see34,
	g_see41, g_see42, g_see43, g_see44,
};

const char	**get_possible_combinations(int view_front, int view_back)
{
	return (g_combination[4 * (view_front - 1) + (view_back - 1)]);
}
