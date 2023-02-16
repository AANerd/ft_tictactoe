/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliferre <aliferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:44:31 by aliferre          #+#    #+#             */
/*   Updated: 2023/02/16 19:07:31 by aliferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define POS_TAKEN 1
#define WRONG_POS 2

#define NO_WIN -1
#define TIE 0
#define X_WIN 1
#define O_WIN 2

void	show_grid(char *grid)
{
	int	i;
	int	j;

	printf("  | A | B | C | \n");
	printf("--+---+---+---+ \n");
	i = 0;
	while (i < 3)
	{
		printf("%c | ", i + '1');
		j = 0;
		while (j < 3)
		{
			printf("%c | ", grid[3 * i + j]);
			j++;
		}
		printf("\n--+---+---+---+\n");
		i++;
	}
}

int	play(char c, char *grid, char *pos)
{
	if ('A' <= pos[0] && pos[0] <= 'C' && '1' <= pos[1] && pos[1] <= '3')
	{
		if (grid[3 * (pos[1] - '1') + pos[0] - 'A'] != ' ')
			return (POS_TAKEN);
		grid[3 * (pos[1] - '1') + pos[0] - 'A'] = c;
		return (SUCCESS);
	}
	else if ('1' <= pos[0] && pos[0] <= '3' && 'A' <= pos[1] && pos[1] <= 'C')
	{
		if (grid[3 * (pos[0] - '1') + pos[1] - 'A'] != ' ')
			return (POS_TAKEN);
		grid[3 * (pos[0] - '1') + pos[1] - 'A'] = c;
		return (SUCCESS);
	}
	else
		return (WRONG_POS);
}

int		check_win(char *grid)
{
	if ((grid[0] == 'X' && grid[1] == 'X' && grid[2] == 'X')
		|| (grid[3] == 'X' && grid[4] == 'X' && grid[5] == 'X')
		|| (grid[6] == 'X' && grid[7] == 'X' && grid[8] == 'X')
		|| (grid[0] == 'X' && grid[3] == 'X' && grid[6] == 'X')
		|| (grid[1] == 'X' && grid[4] == 'X' && grid[7] == 'X')
		|| (grid[2] == 'X' && grid[5] == 'X' && grid[8] == 'X')
		|| (grid[0] == 'X' && grid[4] == 'X' && grid[8] == 'X')
		|| (grid[2] == 'X' && grid[4] == 'X' && grid[6] == 'X'))
		return (X_WIN);
	else if ((grid[0] == 'O' && grid[1] == 'O' && grid[2] == 'O')
		|| (grid[3] == 'O' && grid[4] == 'O' && grid[5] == 'O')
		|| (grid[6] == 'O' && grid[7] == 'O' && grid[8] == 'O')
		|| (grid[0] == 'O' && grid[3] == 'O' && grid[6] == 'O')
		|| (grid[1] == 'O' && grid[4] == 'O' && grid[7] == 'O')
		|| (grid[2] == 'O' && grid[5] == 'O' && grid[8] == 'O')
		|| (grid[0] == 'O' && grid[4] == 'O' && grid[8] == 'O')
		|| (grid[2] == 'O' && grid[4] == 'O' && grid[6] == 'O'))
		return (O_WIN);
	else if (grid[0] != ' ' && grid[1] != ' ' && grid[2] != ' '
			&& grid[3] != ' ' && grid[4] != ' ' && grid[5] != ' '
			&& grid[6] != ' ' && grid[7] != ' ' && grid[8] != ' ')
		return (TIE);
	else
		return (NO_WIN);
}

void	turn(char player, char *grid)
{
	int		result;
	char	pos[3];

	printf("Where to put a %c: ", player);
	scanf("%s", pos);
	if (pos[0] == 'q')
		exit(0);
	result = play(player, grid, pos);
	if (result == WRONG_POS)
	{
		printf("That position does not exist!\n");
		turn(player, grid);
	}
	else if (result == POS_TAKEN)
	{
		printf("There is already something in that position!\n");
		turn(player, grid);
	}
	else if (result == SUCCESS)
	{
		printf("\n");
		show_grid(grid);
		result = check_win(grid);
		if (result == TIE)
			printf("The game has tied, nobody won!\n");
		else if (result == X_WIN)
			printf("Player X has won the game!\n");
		else if (result == O_WIN)
			printf("Player O has won the game!\n");
		else if (result == NO_WIN)
		{
			if (player == 'X')
				turn('O', grid);
			else if (player == 'O')
				turn('X', grid);
			else
				printf("Something unexpected has happened... (player is %c)", player);
		}
		else
			printf("Something unexpected has happened... (check_win return is %d)", result);
	}
	else
		printf("Something unexpected has happened... (play return is %d)", result);
}

int	main(int argc, char **argv)
{
	char	grid[] = "         ";
	
	show_grid(grid);
	turn('X', grid);
	return (0);
}
