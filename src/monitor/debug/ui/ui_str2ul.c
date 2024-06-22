#include <isa.h>

#include <stdlib.h>
#include <readline/readline.h>
#include <errno.h>

int prase_str2ul(char *args, char **ppucNext, uint64_t *pulVal)
{
  uint64_t n = 0;
  char *endptr = NULL;

  if (NULL == args)
  {
    Log("args is null.");
    return -1;
  }

  n = strtoul(args, &endptr, 0);

  if (endptr == args)
  {
    // Log("No digits were found from args: %s\n", args);
    return -1;
  }
  else if (ERANGE == errno)
  {
    Log("the number: %s is out of range.\n", args);
    return -1;
  }

  *pulVal = n;
  *ppucNext = endptr;

  return 0;
}
