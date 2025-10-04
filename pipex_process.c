/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:50:49 by byeolee           #+#    #+#             */
/*   Updated: 2025/04/16 10:51:08 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	child_process(char **av, char **env, int *pipefd)
{
	int		infile;
	pid_t	pid;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
	{
		error_message(av[1], 1);
		infile = open("/dev/null", O_RDONLY);
		if (infile < 0)
		{
			close(infile);
			exit(1);
		}
	}
	pid = fork();
	if (pid < 0)
		exit (0);
	if (pid == 0)
	{
		close(pipefd[0]);
		pipe_func(av[2], env, infile, pipefd[1]);
	}
	close(infile);
	return (pid);
}

pid_t	parents_process(char **av, char **env, int *pipefd)
{
	int		outfile;
	pid_t	pid;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		perror("outfile");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(1);
	}
	pid = fork();
	if (pid < 0)
		exit (0);
	if (pid == 0)
	{
		close(pipefd[1]);
		pipe_func(av[3], env, pipefd[0], outfile);
	}
	close(outfile);
	return (pid);
}
