#include <isa.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <errno.h>
#include "ui_str2ul.h"
#include <memory/paddr.h>

int prase_x_args(char *args, uint64_t *pulNum, uint64_t *pulAddr){
    int iRet            = 0;
    // uint64_t ulAddr = 0;
    uint64_t ulNum      = 0;
    uint64_t ulAddr     = 0;
    uint64_t ulTmp      = 0;
    char *pucPtr        = NULL;
    char *pucPtrNext    = NULL;

    iRet = prase_str2ul(args, &pucPtrNext, &ulNum);
    if (0 != iRet)
    {
        Log("Fail to get first args from from args: %s, iRet = %d.", args, iRet);
        return iRet;
    }

    pucPtr = pucPtrNext;
    iRet = prase_str2ul(pucPtr, &pucPtrNext, &ulAddr);
    if (0 != iRet)
    {
        Log("Fail to get secend args from args: %s, iRet = %d.", args, iRet);
        return iRet;
    }

    /* juest get 2 args */
    pucPtr = pucPtrNext;
    iRet = prase_str2ul(pucPtr, &pucPtrNext, &ulTmp);
    if (0 == iRet)
    {
        Log("invalid input args: %s", args);
        return -1;
    }

    *pulAddr = ulAddr;
    *pulNum = ulNum;

    return 0;
}

#define UI_X_PRINT_WIDTH 4
#define UI_X_PRINT_NUM_IN_LINE 16

void ui_x_print(uint64_t ulNum, paddr_t addr)
{
  paddr_t stOffset = 0;

  for (stOffset=0; stOffset < ulNum; stOffset = stOffset + UI_X_PRINT_WIDTH)
  {
    /* not first line */
    if ((0 != stOffset) && (0 == (stOffset % UI_X_PRINT_NUM_IN_LINE)))
    {
      printf("\n");
    }
    
    if (0 == (stOffset % UI_X_PRINT_NUM_IN_LINE))
    {
      printf("0x%x: ", (addr + stOffset));
    }

    printf("0x%.8x ", paddr_read(addr + stOffset, UI_X_PRINT_WIDTH));
  }

  /* set \n in then last line */
  printf("\n");

  return;
}

int cmd_x(char *args) {
  int iRet = 0;
  uint64_t ulAddr = 0;
  uint64_t ulNum = 0;

  printf("cmd_x: %s\n", args);
  iRet = prase_x_args(args, &ulNum, &ulAddr);
  if (0 != iRet)
  {
    Log("Failed to prase args, iRet = %d.", iRet);
    return 0;
  }

  ui_x_print(ulNum, ulAddr);

  return 0;
}