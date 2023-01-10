#include "map_symbols.h"


/**
 * @brief constroy_map Auxiliar function, called in case of error in malloc
 * free map and set to NULL
 * 
 * @param map t_map
 * @param position	the index position to malloc that failed
 */
static void error_malloc_map(t_map map, int position)
{
	int index = 0;

	while (index < position)
	{
		free(map[index]);
		index++;
	}
	free(map);
	map = NULL;
}

t_map constroy_map(int height)
{
	t_map map = (t_map)malloc(sizeof(char *) * 256);
	if (!map)
		return (NULL);
	for (int i = 0; i < 256; i++) {
		map[i] = (char *)calloc((height + 1), sizeof(char));
		if (!map[i])
			return (error_malloc_map(map, i), NULL);
	}
	map[255] = NULL;
	return (map);
}

void	fill_map(t_map map, t_node *tree, char *path_as_bits, int index)
{
	char	left[index];
	char	right[index];

	if (is_leaf(tree))
		strcpy(map[tree->symbol], path_as_bits);
	else
	{
		strcpy(left, path_as_bits);
		strcpy(right, path_as_bits);
		strcat(left, "0");
		strcat(right, "1");

		fill_map(map, tree->left, left, index);
		fill_map(map, tree->right, right, index);
	}
}

void	print_map(t_map map)
{
	for (int i = 0; i < 255; i++) {
		if (strlen(map[i]))
			printf("Char(DEC) = %3d  code = %s\n", i, map[i]);
	}
}

int		get_code_size(t_map map, char *str)
{
	int size = 0;

	for (int i = 0; str[i]; i++)
		size += strlen(map[str[i]]);
	return (size);
}