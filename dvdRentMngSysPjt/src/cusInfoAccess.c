/* Name: cusInfoCAccess.c  ver 1.0
 * Content: 고객 정보 저장 및 참조 함수들의 정의
 * Implementation: KJJ
 * 
 * Last modified 2020/01/27
 */
#include "common.h"
#include "cusInfo.h"
#include "cusInfoAccess.h"

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
    if(numOfCustomer >= MAX_CUSTOMER)
        return RC_ERR;

    cusList[numOfCustomer] = (cusInfo*)malloc(sizeof(cusInfo));
    check(cusList[numOfCustomer] != NULL, "cusList[%d] memory allocation failed!!", numOfCustomer);

    memset(cusList[numOfCustomer], 0x00, sizeof(cusInfo)); //memset으로 초기화 해주지 않으면 segmentation 오류 발생.
    memcpy(cusList[numOfCustomer]->ID, ID, ID_LEN);
    memcpy(cusList[numOfCustomer]->name, name, NAME_LEN);
    memcpy(cusList[numOfCustomer]->phoneNum, num, PHONE_LEN);

    StoreCusInfo();

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
 * numOfCustomer, cusList[MAX_CUSTOMER]
 */
int IsRegistID(char * ID)
{
//    int i;
//
//    for(i=0; i<numOfCustomer; i+=1)
//    {
//        if(strcmp(ID, cusList[i]->ID) == 0) {
//            return RC_NRM;
//        }
//    }
    if(GetCusPtrByID(ID))
        return RC_NRM;

    return RC_NFD;
}

/* 함    수: int StoreCusInfo(void)
 * 기    능: customer 정보 저장. numOfCustomer, cusList[MAX_CUSTOMER]
 * 반    환: rc
 *
 */
int StoreCusInfo(void)
{
    int rc;
    int i;
    FILE * fp;

    fp = fopen("file/cus-info", "wb");
    check(fp != NULL, "cus-info file open failed!!");

    fwrite(&numOfCustomer, sizeof(int), 1, fp);
    for(i = 0; i < numOfCustomer; i+=1)
    {
        fwrite(cusList[i], sizeof(cusInfo), 1, fp);
    }
    fclose(fp);
    fp = NULL;

    return RC_NRM;

error:
    if(fp) {
        fclose(fp);
        fp = NULL;
    }
    return RC_ERR;
}

/* 함    수: int LoadCusInfo(void)
 * 기    능: customer 정보 불러오기. numOfCustomer, cusList[MAX_CUSTOMER]
 * 반    환: rc
 *
 */
int LoadCusInfo(void)
{

    int rc;
    int i = 0;
    FILE * fp;

    fp = fopen("file/cus-info", "rb");
    check(fp != NULL, "cus-info file open failed!!");

    fread(&numOfCustomer, sizeof(int), 1, fp);

    for(i = 0; i < numOfCustomer; i+=1)
    {
        cusList[i] = (cusInfo*)malloc(sizeof(cusInfo));// 엄청 삽질한 부분.. 당연히 파일 불러 올때도 메모리가 필요함을 까먹었다.
        check(cusList[i] != NULL, "failed memmory allocate at LoadCusInfo");
        fread(cusList[i], sizeof(cusInfo), 1, fp);
    }

    fclose(fp);
    fp = NULL;

    return RC_NRM;

error:
    if(fp) {
        fclose(fp);
        fp = NULL;
    }
    if(cusList[i]) {
        free(cusList[i]);
        cusList[i] = NULL;
    }
    return RC_ERR;
}

/* 함    수: void freeCusListMem(void)
 * 기    능: cusList 적재된 메모리 해제 시키는 함수
 * 반    환: 
 *
 */
void freeCusListMem(void)
{
    int i;
    int rc;

    for(i = 0; i < numOfCustomer; i+=1)
    {
        if(cusList[i]) {
            free(cusList[i]);
            cusList[i] = NULL;
        }
    }
}

/* end of file */
