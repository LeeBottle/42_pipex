/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:53:14 by byeolee           #+#    #+#             */
/*   Updated: 2025/06/30 13:35:14 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

int		main(int ac, char **av, char **env);
void	free_pid(int *pipefd, pid_t *pid, int count);
void	free_split(char **arr);
int		is_space(char c);
int		is_quote(char c);
int		commands_checker(int ac, char **av, char **env, int type);
void	error_message(char *input, int type);
char	*get_cmd_path(char *cmd, char **env);
void	pipe_func(char *cmd, char **env, int infile, int outfile);
char	**ft_split_quotes(const char *str);
void	here_doc_process(int ac, char **av, char **env);
void	input_infile(char **infile, char *LIMITER);
pid_t	solo_process(char *cmd, char **env, int infile, int outfile);
pid_t	child_process(char **av, char **env, int *pipefd);
pid_t	middle_process(char *cmd, char **env, int prev_read, int *pipefd);
pid_t	parents_process(char *cmd, char **env, int prev_read, char *name);
pid_t	child_process_hd(char **av, char **env, int *pipefd, int infile);
pid_t	parents_process_hd(char *cmd, char **env, int prev_read, char *name);

#endif