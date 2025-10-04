/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:19:23 by byeolee           #+#    #+#             */
/*   Updated: 2025/06/30 13:51:23 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_pid(int *pipefd, pid_t *pid, int count)
{
	int	j;

	close(pipefd[0]);
	close(pipefd[1]);
	j = 0;
	while (j < count)
		waitpid(pid[j++], NULL, 0);
	free(pid);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"' || c == '{' || c == '}');
}

void	error_message(char *input, int type)
{
	if (type == 1)
	{
		write(2, "zsh: no such file or directory: ", 32);
		write(2, input, ft_strlen(input));
		write(2, "\n", 1);
	}
	if (type == 2)
	{
		write(2, "zsh: command not found: ", 24);
		write(2, input, ft_strlen(input));
		write(2, "\n", 1);
	}
}
