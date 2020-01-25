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

void SearchPhoneData(void);
void DeletePhoneData(void);
void ChangePhoneData(void);

void StoreDataToFile(void);
void LoadDataFromFile(void);

void StoreDataToFileInStruct(void);
void LoadDataFromFileInStruct(void);

#endif

/* end of file */

