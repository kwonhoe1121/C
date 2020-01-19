/* Name: screenOut.h  ver 1.0
 * Content: 콘솔 출력을 위한 함수 선언
 * Implementation: YSW
 * 
 * Last modified 2008/01/01
 */

#ifndef __SCREENOUT_H__
#define __SCREENOUT_H__

#include "phoneData.h"

void ShowMenu(void);
//void ShowPhoneInfo(phoneData phone); //구조체 배열
void ShowPhoneInfoByPtr(phoneData * phone); //구조체 포인터 배열

#endif

/* end of file */

