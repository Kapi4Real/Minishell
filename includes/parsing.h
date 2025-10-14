/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:32:10 by togomez           #+#    #+#             */
/*   Updated: 2025/04/25 11:21:11 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "libft.h"
# include <sys/types.h>

typedef enum e_arg_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	EXPAND_VAR
}	t_arg;

typedef struct s_token
{
	t_arg			type;
	char			*val;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	t_list			*arguments;
	t_token			*redirection;
	int				exit_s;
	int				input_fd;
	int				output_fd;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

t_token	*token_new(char *content, t_arg type);
t_token	*token_last(t_token *lst);
t_token	*tokenizer(char *input);
void	token_add_back(t_token **lst, t_token *new);
void	token_clear(t_token *token);
t_cmd	*cmd_new(void);
t_cmd	*cmd_last(t_cmd *lst);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
void	cmd_clear(t_cmd **cmd);
int		check_quotes(char *input);
int		parsing(t_token **token);
int		var_len(char *str);
t_token	*create_token(char *val, t_arg type);
void	add_token(t_token **lst, t_token *new);
t_token	*lexer(char *input);

#endif