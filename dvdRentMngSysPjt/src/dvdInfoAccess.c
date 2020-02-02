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

    return ++numOfDvd;

error:
    if(dvdList[numOfDvd]) {
        free(dvdList[numOfDvd]);
        dvdList[numOfDvd] = NULL;
    }
    return RC_ERR;
}

/* 함    수: int setDvdRentedInfo(char * isbn)
 * 기    능: 대여된 dvd 대여 상태 설정 함수
 * 반    환: int
 *
 */
int setDvdRentedState(char * isbn)
{
    dvdInfo * slctDvd;
    int rc;

    slctDvd = GetDvdPtrByISBN(isbn);
    if(!slctDvd) return RC_ERR;

//   if(slctDvd->numOfRentCus >= RENT_LEN) {
//        fputs("등록된 대여 정보의 개수를 초과하여 대여 정보를 기록할 수 없습니다.\n", stdout);
//        return RC_ERR;
//    }
//    debug("id is %s", id);
//    debug("rntDay is %d", rntDay);
//    slctDvd->rentState = RENTED;
//    //slctDvd->rentList[slctDvd->numOfRentCus] = *rentDvdInfo;
//    memcpy(slctDvd->rentList[slctDvd->numOfRentCus].cusID, id, ID_LEN);
//    slctDvd->rentList[slctDvd->numOfRentCus].rentDay = rntDay;
//    slctDvd->numOfRentCus++;
    slctDvd->rentState = RENTED;

    return RC_NRM;

error:
    return RC_ERR;
}

/* 함    수: int setDvdRented(char * isbn)
 * 기    능: 대여된 dvd 반납시키는 함수.
 * 반    환: int
 *
 */
int setDvdRented(char * isbn)
{
    dvdInfo * slctDvd;
    int rc;

    slctDvd = GetDvdPtrByISBN(isbn);
    if(!slctDvd) return RC_ERR;

    slctDvd->rentState = RETURNED;

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

/* end of file */
