/* Name: cusInfoCAccess.c  ver 1.0
 * Content: 고객 정보 저장 및 참조 함수들의 정의
 * Implementation: KJJ
 * 
 * Last modified 2020/01/27
 */
#include "common.h"
#include "cusInfo.h"

#define MAX_CUSTOMER  100

static cusInfo * cusList[MAX_CUSTOMER]; //구조체 포인터 배열임을 유의한다.
static int numOfCustomer=0;

/* 함    수: int AddCusInfo (char * ID, char * name, char * num)
 * 기    능: cusInfo 할당 및 저장. 
 * 반    환: 성공 시 '등록된 정보의 수', 실패 시 RC_ERR을 반환으로 수정.
 *
 */
int AddCusInfo(char * ID, char * name, char * num)
{
    if(numOfCustomer + 1 > MAX_CUSTOMER)
        return RC_ERR;

    cusList[numOfCustomer] = (cusInfo*)malloc(sizeof(cusInfo));
    check(cusList[numOfCustomer] != NULL, "cusList[%d] memory allocation failed!!", numOfCustomer);

    memcpy(cusList[numOfCustomer]->ID, ID, ID_LEN);
    memcpy(cusList[numOfCustomer]->name, name, NAME_LEN);
    memcpy(cusList[numOfCustomer]->phoneNum, num, PHONE_LEN);

    return ++numOfCustomer;

error:
    if(cusList[numOfCustomer]) {
        free(cusList[numOfCustomer]);
        cusList[numOfCustomer] = NULL;
    }
    return RC_ERR;
}


/* 함    수: cusInfo * GetCusPtrByID(char * ID)
 * 기    능: 해당 ID의 정보를 담고 있는 변수의 포인터 반환 
 * 반    환: 등록 안된 ID의 경우 NULL 포인터 반환.
 *
 */
cusInfo * GetCusPtrByID(char * ID)
{
    int i;

    for(i=0; i<numOfCustomer; i+=1)
    {
        if(strcmp(ID, cusList[i]->ID) == 0)
            return cusList[i];
    }
    return NULL;
}


/* 함    수: int IsRegistID(char * ID)
 * 기    능: 가입 된 ID인지 확인. 
 * 반    환: 가입 되었으면 RC_NRM, 아니면 RC_NFD 반환.
 *
 */
int IsRegistID(char * ID)
{
    int i;

    for(i=0; i<numOfCustomer; i+=1)
    {
        if(strcmp(ID, cusList[i]->ID) == 0) {
            return RC_NRM;
        }
    }

    return RC_NFD;
}

/* end of file */
