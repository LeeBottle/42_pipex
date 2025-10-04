/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_funcs_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:19:07 by byeolee           #+#    #+#             */
/*   Updated: 2025/06/30 13:49:19 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipe_func(char *cmd, char **env, int infile, int outfile)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split_quotes(cmd);
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror("dup2 infile");
		exit(1);
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		perror("dup2 outfile");
		exit(1);
	}
	cmd_path = get_cmd_path(cmd_args[0], env);
	execve(cmd_path, cmd_args, env);
	free(cmd_path);
	free_split(cmd_args);
	exit(0);
}
