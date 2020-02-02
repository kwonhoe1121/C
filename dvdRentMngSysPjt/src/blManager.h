/* Name: blManager.h  ver 1.0
 * Content: DVD 관련 Business Logic업무 처리 함수들의 선언.
 * Implementation: KJJ
 * 
 * Last modified 2020/02/02
 */

#ifndef __BLMGR_H__
#define __BLMGR_H__

#include "cusInfo.h"
#include "dvdInfo.h"
#include "rentInfo.h"
#include "dvdInfoAccess.h"
#include "cusInfoAccess.h"
#include "rentInfoAccess.h"
#include "screenOut.h"

int RegistCustomer(void);
int SearchCusInfo(void);

int RegistDvd(void);
int SearchDvdInfo(void);

int rentDvd(void);
int returnDvd(void);

int showAllRntDvdHis(void);
int showAllRntCusHis(void);

int StoreDvdSysEnv(void);
int LoadDvdSysEnv(void);
void freeListMem(void);

#endif

/* end of file */
