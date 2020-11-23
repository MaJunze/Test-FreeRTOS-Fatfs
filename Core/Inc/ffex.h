/*
 * ffex.h
 *
 *  Created on: 2020.11.24.
 *      Author: NB163
 */

#ifndef INC_FFEX_H_
#define INC_FFEX_H_

#include "ff.h"

FRESULT f_list(const TCHAR *path);
FRESULT f_deldir(const TCHAR *path);

#endif /* INC_FFEX_H_ */
