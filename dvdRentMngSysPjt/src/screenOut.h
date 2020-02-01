/* Name: screenOut.h  ver 1.0
 * Content: 콘솔 출력을 위한 함수들의 선언.
 * Implementation: KJJ
 * 
 * Last modified 2020/01/27
 */

#ifndef __SCREENOUT_H__
#define __SCREENOUT_H__

#include "cusInfo.h"
#include "dvdInfo.h"

void ShowMenu(void);
void ShowCustomerInfo(cusInfo * pCus);
void ShowDvdInfo(dvdInfo * pDvd);
void showGenre(int gen);

#endif

/* end of file */
