/* Name: rentInfoAccess.c  ver 1.1
 * Content: DVD 대여 정보 저장/참조 함수들의 정의.
 * Implementation: KJJ 
 * 
 * Last modified 2020/02/02
 */

#include "common.h"
#include "rentInfo.h"
#include "cusInfo.h"
#include "cusInfoAccess.h"
#include "screenOut.h"
#include "rentInfoAccess.h"

#define RENT_LEN  100

static dvdRentInfo rentList[RENT_LEN]; // 구조체 배열 선언!!
static int numOfRentCus=0;

/* 함    수: void AddRentList(char * ISBN, char * cusID, int rentDay)
 * 기    능: 대여 정보를 저장
 * 반    환: void
 * 
 */
void AddRentList(char * ISBN, char * cusID, int rentDay)
{
    memset(&rentList[numOfRentCus], 0x00, sizeof(dvdRentInfo));
    memcpy(rentList[numOfRentCus].ISBN, ISBN, ISBN_LEN);
    memcpy(rentList[numOfRentCus].cusID, cusID, ID_LEN);
    rentList[numOfRentCus].rentDay = rentDay;
    numOfRentCus++;

    StoreRentInfo();

}


/* 함    수: void PrintOutRentAllCusInfo(char * ISBN)
 * 기    능: 특정 ISBN의 DVD 대여 고객 정보 출력
 * 반    환: void
 * 
 */
void PrintOutRentAllCusInfo(char * ISBN)   // CusInfo, 고객 정보 출력
{
    cusInfo * cusInfo;
    int i;

    // 따로 구조체로 떼어 냈기 때문에 모든 반복문을 돌아서 일치하는 ISBN값을 확인하고 rent 정보를 출력해야한다.
    for(i = 0; i < numOfRentCus; i+=1)
    {
        if(strcmp(rentList[i].ISBN, ISBN) == 0) { 
            printf("대여일: %d \n", rentList[i].rentDay);
            cusInfo = GetCusPtrByID(rentList[i].cusID);
            if(!cusInfo) return;
            ShowCustomerInfo(cusInfo);
        }
    }
    
}

/* 함    수: void PrintOutCusAllRentInfo(char * ID, unsigned int start, unsigned int end)
 * 기    능: 일정 기간 안에 이뤄진 특정 고객의 DVD 대여 정보 출력
 * 반    환: void
 * 
 */
void PrintOutCusAllRentInfo   //RentInfo, 대여 정보 출력
    (char * ID, unsigned int start, unsigned int end)
{
    int i;

    for(i = 0; i < numOfRentCus; i+=1)
    {
        if(strcmp(rentList[i].cusID, ID) == 0 
            && rentList[i].rentDay >= start 
            && rentList[i].rentDay <= end) 
        {
            ShowRentDayInfo(&rentList[i]); //구조체 배열로 선언 했으므로 주소값 넘긴다.
        }
    }
}

/* 함    수: int StoreRentInfo(void)
 * 기    능: Rent 정보 저장. numOfRentCus, rentList[RENT_LEN]
 * 반    환: rc
 *
 */
int StoreRentInfo(void)
{
    int rc;
    int i;
    FILE * fp;

    fp = fopen("file/rent-info", "wb");
    check(fp != NULL, "rent-info file open failed!!");

    fwrite(&numOfRentCus, sizeof(int), 1, fp);
    for(i = 0; i < numOfRentCus; i+=1)
    {
        fwrite(&rentList[i], sizeof(dvdRentInfo), 1, fp);
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

/* 함    수: int LoadRentInfo(void)
 * 기    능: Rent 정보 불러오기. numOfRentCus, rentList[RENT_LEN]
 * 반    환: rc
 *
 */
int LoadRentInfo(void)
{
    int rc;
    int i;
    FILE * fp;

    fp = fopen("file/rent-info", "rb");
    check(fp != NULL, "rent-info file open failed!!");

    fread(&numOfRentCus, sizeof(int), 1, fp);
//    for(i = 0; i < numOfRentCus; i+=1)
//    {
//        fread(&rentList[i], sizeof(dvdRentInfo), 1, fp);
//    }
    fread(rentList, sizeof(dvdInfo), numOfRentCus, fp); //구조체 배열인 경우는 메모리가 미리 할당 되어 있기 때문에 데이터 복원을 한번에 할 수 있다. 훨씬 빠르다.
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

/* end of file */
