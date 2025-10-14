/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_arrays.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:00:00 by user              #+#    #+#             */
/*   Updated: 2023/05/01 12:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	free_str_array(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		free(array[i]);
	free(array);
}

char	**list_to_str_array(t_list *lst)
{
	char	**array;
	int		count;
	int		i;
	t_list	*tmp;

	count = ft_lstsize(lst);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		array[i] = ft_strdup((char *)tmp->content);
		if (!array[i])
		{
			free_str_array(array);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
