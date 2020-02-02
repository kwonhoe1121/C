/* Name: dvdInfoAccess.c  ver 1.0
 * Content: dvd 정보 저장 및 참조 함수들의 정의
 * Implementation: KJJ
 * 
 * Last modified 2020/02/01
 */
#include "common.h"
#include "dvdInfo.h"
#include "dvdInfoAccess.h"
#include "rentInfoAccess.h"

#define MAX_DVD  100

static dvdInfo * dvdList[MAX_DVD]; //구조체 포인터 배열임을 유의한다.
static int numOfDvd=0;

/* 함    수: int AddDvdInfo (char * ISBN, char * title, char * genre)
 * 기    능: dvdInfo 할당 및 저장. 
 * 반    환: 성공 시 '등록된 정보의 수', 실패 시 RC_ERR을 반환으로 수정.
 *
 */
int AddDvdInfo (char * ISBN, char * title, int genre)
{
    if(numOfDvd >= MAX_DVD)
        return RC_ERR;

    dvdList[numOfDvd] = (dvdInfo*)malloc(sizeof(dvdInfo));
    check(dvdList[numOfDvd] != NULL, "dvdList[%d] memory allocation failed!!", numOfDvd);

    memset(dvdList[numOfDvd], 0x00, sizeof(dvdInfo)); //memset 으로 할당받은 메모리 초기화 해주지 않으면 segmentation오류 발생
    memcpy(dvdList[numOfDvd]->ISBN, ISBN, ISBN_LEN);
    memcpy(dvdList[numOfDvd]->title, title, TITLE_LEN);
    memcpy(&dvdList[numOfDvd]->genre, &genre, sizeof(genre));

    dvdList[numOfDvd]->rentState = RETURNED; 
    //dvdList[numOfDvd]->numOfRentCus = 0;
    StoreDvdInfo();

    return ++numOfDvd;

error:
    if(dvdList[numOfDvd]) {
        free(dvdList[numOfDvd]);
        dvdList[numOfDvd] = NULL;
    }
    return RC_ERR;
}

/* 함    수: int setDvdRented(char * isbn)
 * 기    능: 대여된 dvd 대여시키는 함수.
 * 반    환: int
 *
 */
int setDvdRented(char * isbn)
{
    dvdInfo * slctDvd;
    int rc;

    slctDvd = GetDvdPtrByISBN(isbn);
    if(!slctDvd) return RC_ERR;

    slctDvd->rentState = RENTED;

    StoreDvdInfo();

    return RC_NRM;
error:
    return RC_ERR;
}

/* 함    수: int setDvdReturned(char * isbn)
 * 기    능: 대여된 dvd 반납시키는 함수.
 * 반    환: int
 *
 */
int setDvdReturned(char * isbn)
{
    dvdInfo * slctDvd;
    int rc;

    slctDvd = GetDvdPtrByISBN(isbn);
    if(!slctDvd) return RC_ERR;

    slctDvd->rentState = RETURNED;

    StoreDvdInfo();

    return RC_NRM;
error:
    return RC_ERR;
}


/* 함    수: dvdInfo * GetDvdPtrByISBN(char * ISBN)
 * 기    능: 해당 DVD의 정보를 담고 있는 변수의 포인터 반환 
 * 반    환: 등록 안된 DVD의 경우 NULL 포인터 반환.
 *
 */
dvdInfo * GetDvdPtrByISBN(char * ISBN)
{
    int i;

    for(i=0; i<numOfDvd; i+=1)
    {
        if(strcmp(ISBN, dvdList[i]->ISBN) == 0)
            return dvdList[i];
    }
    return NULL;
}


/* 함    수: int IsRegistISBN(char * ISBN)
 * 기    능: 가입 된 DVD인지 확인. 
 * 반    환: 가입 되었으면 RC_NRM, 아니면 RC_NFD 반환.
 *
 */
int IsRegistISBN(char * ISBN)
{
//    int i;
//
//    for(i=0; i<numOfDvd; i+=1)
//    {
//        if(strcmp(ISBN, dvdList[i]->ISBN) == 0) {
//            return RC_NRM;
//        }
//    }
    if(GetDvdPtrByISBN(ISBN))
        return RC_NRM;

    return RC_NFD;
}


/* 함    수: int StoreDvdInfo(void)
 * 기    능: DVD 정보 저장. numOfDvd, dvdList[MAX_DVD]
 * 반    환: rc
 *
 */
int StoreDvdInfo(void)
{
    int rc;
    int i;
    FILE * fp;

    fp = fopen("file/dvd-info", "wb");
    check(fp != NULL, "dvd-info file open failed!!");

    fwrite(&numOfDvd, sizeof(int), 1, fp);
    for(i = 0; i < numOfDvd; i+=1)
    {
        fwrite(dvdList[i], sizeof(dvdInfo), 1, fp);
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

/* 함    수: int LoadDvdInfo(void)
 * 기    능: DVD 정보 불러오기. numOfDvd, dvdList[MAX_DVD]
 * 반    환: rc
 *
 */
int LoadDvdInfo(void)
{
    int rc;
    int i;
    FILE * fp;

    fp = fopen("file/dvd-info", "rb");
    check(fp != NULL, "dvd-info file open failed!!");

    fread(&numOfDvd, sizeof(int), 1, fp);

    for(i = 0; i < numOfDvd; i+=1)
    {
        dvdList[i] = (dvdInfo*)malloc(sizeof(dvdInfo));
        check(dvdList[i] != NULL, "failed memmory allocate at LoadDvdInfo");
        fread(dvdList[i], sizeof(dvdInfo), 1, fp);
    }

    fclose(fp);
    fp = NULL;

    return RC_NRM;

error:
    if(fp) {
        fclose(fp);
        fp = NULL;
    }
    if(dvdList[i]) {
        free(dvdList[i]);
        dvdList[i] = NULL;
    }
    return RC_ERR;
}

/* 함    수: void freeDvdListMem(void)
 * 기    능: dvdList 적재된 메모리 해제 시키는 함수
 * 반    환: 
 *
 */
void freeDvdListMem(void)
{
    int i;
    int rc;

    for(i = 0; i < numOfDvd; i+=1)
    {
        if(dvdList[i]) {
            free(dvdList[i]);
            dvdList[i] = NULL;
        }
    }
}

/* end of file */
