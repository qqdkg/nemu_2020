#include <isa.h>

#include <stdlib.h>
#include <readline/readline.h>
#include <errno.h>

void cpu_exec(uint64_t);

static uint64_t prase_s_args(char *args)
{
  uint64_t n = 0;
  char *endptr = NULL;

  n = strtoul(args, &endptr, 10);

  if (endptr == args)
  {
    Log("No digits were found from args: %s\n", args);
    return 0;
  }
  else if (ERANGE == errno)
  {
    Log("the number: %s is out of range.\n", args);
    return 0;
  }
  else if (NULL == endptr)
  {
    Log("endptr is NULL, args: %s\n", args);
  }
  else if ('\0' != *endptr)
  {
    Log("args: %s, use %ld\n", args, n);
  }

  return n;
}

/* step n by: dkg */
int cmd_s(char *args) {
  uint64_t nSteps = 0;

  if (NULL != args)
  {
    nSteps = prase_s_args(args);

    /* process n stemp */
    cpu_exec(nSteps);
  }
  else
  {
    /* process a step. */
    cpu_exec(1);
  }

  return 0;
}