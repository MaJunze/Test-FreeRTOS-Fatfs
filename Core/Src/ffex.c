/*
 * ffex.c
 *
 *  Created on: 2020.11.24
 *      Author: NB163
 */

#include "ffex.h"
#include <stdio.h>
#include <string.h>

FRESULT f_list(const TCHAR *path)
{
  FRESULT res = 0;
  FILINFO fno = {0};
  DIR dir = {0};
  TCHAR file[_MAX_LFN + 2] = {0};
  res += f_opendir(&dir, path);
  if(res == FR_OK)
  {
    while(FR_OK == f_readdir(&dir, &fno))
    {
      if(0 == strlen(fno.fname)) break;
      memset(file, 0, sizeof(file));
      sprintf((char *)file, "%s/%s", path, fno.fname);
      printf("%s\r\n", file);
      if (fno.fattrib & AM_DIR)
      {
        res += f_list(file);
      }
    }
    res += f_closedir(&dir);
  }
  return res;
}

FRESULT f_deldir(const TCHAR *path)
{
  FRESULT res = 0;
  FILINFO fno = {0};
  DIR dir = {0};
  TCHAR file[_MAX_LFN + 2] = {0};
  res += f_opendir(&dir, path);
  if(FR_OK == res)
  {
    while(FR_OK == f_readdir(&dir, &fno))
    {
      if(0 == strlen(fno.fname)) break;
      memset(file, 0, sizeof(file));
      sprintf((char*)file, "%s/%s", path, fno.fname);
      if (fno.fattrib & AM_DIR)
      {
        res += f_deldir(file);
      }
      else
      {
        res += f_unlink(file);
      }
    }
    res += f_unlink(path);
  }
  return res;
}
