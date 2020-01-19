/* Name: phoneFunc.h  ver 1.1
 * Content: 전화번호 컨트롤 함수 선언.
 * Implementation: KJJ
 * 
 * Last modified 2020/01/12
 */
#ifndef __PHONEFUNC_H__
#define __PHONEFUNC_H__

#include "phoneData.h"

void InputPhoneData(void);
void ShowAllData(void);

int SearchPhoneData(void);
void DeletePhoneData(void);

void StoreDataToFile(void);
void LoadDataFromFile(void);

#endif

/* end of file */

