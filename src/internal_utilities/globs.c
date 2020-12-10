#include "gl.h"

t_globs     *globs(void)
{
	static t_globs	globs;

	return (&globs);
}
