/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:53:14 by byeolee           #+#    #+#             */
/*   Updated: 2025/06/27 16:12:09 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

int		main(int ac, char **av, char **env);
pid_t	child_process(char **av, char **env, int *pipefd);
pid_t	parents_process(char **av, char **env, int *pipefd);
void	free_split(char **arr);
void	close_all(int *pipefd, pid_t *pid);
int		is_space(char c);
int		is_quote(char c);
char	*get_cmd_path(char *cmd, char **env);
char	*get_cmd_fullpath(char **paths, char *cmd);
void	error_message(char *input, int type);
void	setup_process(int ac, int *pipefd);
void	pipe_func(char *cmd, char **env, int infile, int outfile);
char	**ft_split_quotes(const char *str);

#endif