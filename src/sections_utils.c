/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 00:50:22 by mirifern          #+#    #+#             */
/*   Updated: 2024/09/30 20:13:48 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_first_redir(t_section *section, t_tokens **tokens, int *i)
{
	int	len_name;

	len_name = ft_strlen(tokens[*i + 1]->value);
	section->files = malloc(sizeof(t_red));
	if (!section->files)
		exit(EXIT_FAILURE);
	section->files->file = malloc(sizeof(char) * (len_name + 1));
	if (!section->files->file)
		exit(EXIT_FAILURE);
	ft_strlcpy(section->files->file, tokens[*i + 1]->value, len_name + 1);
	section->files->redi = tokens[*i]->type;
	(*i)++;
	section->files->next = NULL;
}

void	add_rest_redir(t_section *section, t_tokens **tokens, int *i)
{
	int		len_name;
	t_red	*temp;

	if (!section->files)
	{
		add_first_redir(section, tokens, i);
		return ;
	}
	len_name = ft_strlen(tokens[*i + 1]->value);
	temp = section->files;
	while (temp->next)
		temp = temp->next;
	temp->next = malloc(sizeof(t_red));
	if (!temp->next)
		exit(EXIT_FAILURE);
	temp->next->file = malloc(sizeof(char) * (len_name + 1));
	if (!temp->next->file)
		exit(EXIT_FAILURE);
	ft_strlcpy(temp->next->file, tokens[*i + 1]->value, len_name + 1);
	temp->next->redi = tokens[*i]->type;
	(*i)++;
	temp->next->next = NULL;
}

/* Funcion que crea el primer comando del array **/
char	**create_cmd(t_section *section, char *arg)
{
	section->cmd = malloc(sizeof(char *) * 2);
	if (!section->cmd)
		exit(EXIT_FAILURE); //ft_malloc para todos errores de malloc
	section->cmd[0] = ft_strdup(arg);
	if (!section->cmd[0])
		exit(EXIT_FAILURE); //ft_malloc
	section->cmd[1] = NULL;
	return (section->cmd);
}

/**CREAR size_cmd(cmd)*/
int	size_cmd(char **cmd)
{
	int	i;

	while (cmd[i])
		i++;
	return (i);
}

char	**add_arg(t_section *section, char *arg)
{
	int		i;
	char	**new_cmd;

	i = 0;
	if (!section->cmd)
		return (create_cmd(section, arg));
	while (section->cmd[i])
		i++;
	new_cmd = malloc(sizeof(char *) * (i + 2));
	if (!new_cmd)
		exit(EXIT_FAILURE);
	i = 0;
	while (section->cmd[i])
	{
		new_cmd[i] = section->cmd[i];
		i++;
	}
	new_cmd[i] = ft_strdup(arg);
	new_cmd[i + 1] = NULL;
	free(section->cmd);
	return (new_cmd);
}
