/* Name: rentInfoAccess.h  ver 1.0
 * Content: dvd 대여 정보 저장 및 참조 함수들의 선언.
 * Implementation: KJJ
 * 
 * Last modified 2020/02/02
 */

#ifndef __RENT_DVDACCESS_H__
#define __RENT_DVDACCESS_H__ 

#include "rentInfo.h"

void AddRentList(char * ISBN, char * cusID, int rentDay);
void PrintOutRentAllCusInfo(char * ISBN);
void PrintOutCusAllRentInfo(char * ID, unsigned int start, unsigned int end);

int StoreRentInfo(void);
int LoadRentInfo(void);

#endif

/* end of file */
