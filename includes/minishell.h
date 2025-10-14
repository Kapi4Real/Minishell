/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:00:00 by user              #+#    #+#             */
/*   Updated: 2023/05/01 12:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "parsing.h"
# include <sys/resource.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>

extern int					g_sig;
extern int					g_exit_status;
extern char					**g_env;
extern volatile sig_atomic_t	g_sigint_received;

typedef struct s_token		t_token;
typedef struct s_cmd		t_cmd;
typedef struct s_env		t_env;

typedef struct s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	t_cmd			*commands;
	int				n_line;
	t_env			*env;
}	t_minishell;

/* Builtins */
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(char **env);
int		ft_exit(char **args);
int		ft_unset(char **args);
int		ft_export(char **args);
int		ft_cd(char **args);
int		is_builtin(char *cmd);
int		run_builtin(t_cmd *cmd);

/* Environment */
t_env	*envp_to_lst(char **envp);
char	**env_to_array(t_env *env);
t_env	*env_new(char *name, char *val);
void	env_add_back(t_env **env, t_env *new);
void	env_clear(t_env *lst);
void	expand_tokens(t_token **tokens, t_env *env);
char	*remove_quotes(const char *str, t_env *env);
char	*expand_vars_in_string(char *str, t_env *env);

/* Execution */
int		exec_external(t_cmd *cmd, char **envp);
int		exec_commands(t_cmd *cmds, char **envp);
int		exec_single_command(t_cmd *cmd, char **envp);
char	*find_executable(char *cmd);

/* Signals */
void	setup_signals(void);
void	handle_sigint(int sig);

/* Utils */
void	free_array(char **array);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
int		handle_redirections(t_token *token);
char	*build_full_path(char *dir, char *cmd);
void	cmd_not_found(char *cmd);
void	exec_child(char *path, char **args, char **envp);
int		fork_error(char *path, char **args);
int		handle_heredoc(char *delimiter, int *input_fd, int first_exit_s,
			int n_line);
t_cmd	*cmd(t_token *token, t_env *env);
t_cmd	*parser(t_token *tokens, t_env *env);
t_cmd	*create_cmd(t_token **tokens, t_env *env);
char	**env_to_array(t_env *env);
void	free_str_array(char **array);
char	**list_to_str_array(t_list *lst);
void	handle_var_assignment(char *input, t_env **env);
bool	is_valid_var_name(const char *name);
t_env	*find_env_var(t_env *env, const char *name);

#endif
