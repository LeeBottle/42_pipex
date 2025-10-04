/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:19:07 by byeolee           #+#    #+#             */
/*   Updated: 2025/06/30 13:51:58 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "get_next_line/get_next_line.h"

void	input_infile(char **infile, char *LIMITER)
{
	char	*line;
	char	*temp;

	(*infile)[0] = '\0';
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, LIMITER, ft_strlen(LIMITER)) == 0
			&& line[ft_strlen(LIMITER)] == '\n')
		{
			free(line);
			break ;
		}
		temp = ft_strjoin(*infile, line);
		free(*infile);
		*infile = temp;
		free(line);
	}
}

static void	here_doc_single_processes(int ac, char **av, char **env, int infile)
{
	int		outfile;
	pid_t	pid;

	outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile < 0)
	{
		perror("outfile");
		close(infile);
		exit(1);
	}
	pid = solo_process(av[3], env, infile, outfile);
	close(infile);
	close(outfile);
	waitpid(pid, NULL, 0);
}

static void	here_doc_processes(int ac, char **av, char **env, int infile)
{
	int		i;
	int		pipefd[2];
	int		prev_read;
	pid_t	*pid;

	pid = malloc(sizeof(pid_t) * (ac - 3));
	if (!pid)
		return ;
	pipe(pipefd);
	pid[0] = child_process_hd(av, env, pipefd, infile);
	prev_read = pipefd[0];
	i = 4;
	while (i <= ac - 3)
	{
		pipe(pipefd);
		pid[i - 3] = middle_process(av[i], env, prev_read, pipefd);
		prev_read = pipefd[0];
		i++;
	}
	pid[i - 3] = parents_process_hd(av[ac - 2], env, prev_read, av[ac - 1]);
	free_pid(pipefd, pid, ac - 4);
}

void	here_doc_process(int ac, char **av, char **env)
{
	int		heredoc_pipe[2];
	char	*infile;

	if (pipe(heredoc_pipe) == -1)
	{
		perror("pipe");
		exit(1);
	}
	infile = ft_strdup("");
	if (!infile)
		exit (1);
	input_infile(&infile, av[2]);
	write(heredoc_pipe[1], infile, ft_strlen(infile));
	close(heredoc_pipe[1]);
	free(infile);
	if (!commands_checker(ac, av, env, 1))
		return ;
	if (ac == 5)
		here_doc_single_processes(ac, av, env, heredoc_pipe[0]);
	else
		here_doc_processes(ac, av, env, heredoc_pipe[0]);
}
