/* Name: dvdInfoAccess.h  ver 1.0
 * Content: dvd 정보 저장 및 참조 함수들의 선언.
 * Implementation: KJJ
 * 
 * Last modified 2020/02/01
 */

#ifndef __DVDACCESS_H__
#define __DVDACCESS_H__

#include "dvdInfo.h"

int IsRegistISBN(char * ISBN);
dvdInfo * GetDvdPtrByISBN(char * ISBN);
int AddDvdInfo (char * ISBN, char * title, int genre);

int setDvdRentedState(char * isbn);
int setDvdRented(char * isbn);

#endif

/* end of file */
