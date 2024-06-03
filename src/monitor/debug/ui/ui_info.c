#include <isa.h>

#include <stdlib.h>
#include <readline/readline.h>

static int info_r(char *args)
{
  (void) args;

  isa_reg_display();

  return 0;
}

static struct {
  char *name;
  char *description;
  int (*handler) (char *);
} info_table [] = {
  { "r", "Show register", info_r },
};

#define NR_INFO (sizeof(info_table) / sizeof(info_table[0]))

int cmd_info(char *args)
{ 
  int i                 = 0;
  int iRet              = 0;
  char *cmd             = NULL;
  char *args_in_start   = NULL;
  char *args_end        = NULL;
  
  if (NULL == args)
  {
    Log("info args is NULL, shows nothing\n");
    return 0;
  }

  args_end = args + strlen(args);
  
  /* get command */
  cmd = strtok(args, " ");
  if (NULL == cmd)
  {
    Log("arg is null, args: %s\n", args);
    return 0;
  }

  /* try to pass additional args */
  args_in_start = cmd + strlen(cmd) + 1;
  if (args_in_start >= args_end)
  {
    args_in_start = NULL;
  }

  for (i = 0; i < NR_INFO; i++)
  {
    if (strcmp(cmd, info_table[i].name) == 0)
    {
      iRet = info_table[i].handler(args_in_start);
      break;
    }
  }

  return iRet;
}