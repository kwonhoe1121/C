/* Name: dvdManager.c  ver 1.0
 * Content: DVD 관련 업무 처리 함수.
 * Implementation: KJJ
 * 
 * Last modified 2020/02/01
 */

#include "common.h"
#include "dvdInfo.h"
#include "dvdInfoAccess.h"
#include "cusInfoAccess.h"
#include "screenOut.h"
#include "dvdManager.h"

/* 함    수: void RegistDvd(void)
 * 기    능: dvd 신규 등록 함수
 * 반    환: int
 *
 */
int RegistDvd(void)
{
    dvdInfo * enrDvd;
    int rc;

    enrDvd = (dvdInfo*)malloc(sizeof(dvdInfo));
    check(enrDvd != NULL, "Memory allocate failed in RegistDvd()");
    memset(enrDvd, 0x00, sizeof(dvdInfo));

    fputs("ISBN 입력: ", stdout);
    scanf("%s", enrDvd->ISBN);

    rc = IsRegistISBN(enrDvd->ISBN);
    if(rc == RC_NRM) {
        puts("해당 ISBN는 사용 중에 있습니다. 다른 ISBN를 선택해주세요!");
        return RC_DUP;
    }

    fputs("제목 입력 : ", stdout);
    scanf("%s", enrDvd->title);
    while(1)
    {
        fputs("장르 입력 <액션 1, 코믹 2, SF 3, 로맨틱 4>: ", stdout);
        scanf("%d", &enrDvd->genre);

        if(enrDvd->genre > 0 && enrDvd->genre < 5)
            break;
    }

    rc = AddDvdInfo(enrDvd->ISBN, enrDvd->title, enrDvd->genre);
    if(rc == RC_NRM) {
        puts("해당 ISBN 저장에 실패하였습니다!"); 
        return RC_ERR;
    }

    puts("가입이 완료되었습니다.");

    return RC_NRM;

error:
    if(enrDvd) {
        free(enrDvd);
        enrDvd = NULL;
    }
    return RC_ERR;
}

/* 함    수: void SearchDvdInfo(void)
 * 기    능: ISBN를 통한 회원 정보 검색
 * 반    환: int
 * 
 */
int SearchDvdInfo(void)
{
	char schIsbn[ISBN_LEN];
    int rc;

    fputs("찾는 ISBN 입력: ", stdout);
    scanf("%s", schIsbn);

    rc = IsRegistISBN(schIsbn);

    if(rc == RC_NFD) {
        puts("찾는 ISBN는 등록되어 있지 않습니다.");
        return RC_NFD;
    }

    ShowDvdInfo(GetDvdPtrByISBN(schIsbn));
    return RC_NRM;

}

/* 함    수: int rentDvd(void)
 * 기    능: dvd 대여 함수
 * 반    환: int
 * 
 */
int rentDvd(void)
{
    int rc;
    char schIsbn[ISBN_LEN];
    dvdInfo * schDvdInfo;
    dvdRentInfo * rentDvdInfo;

    fputs("대여 DVD ISBN 입력: ", stdout);
    scanf("%s", schIsbn);

    rc = IsRegistISBN(schIsbn);

    if(rc == RC_NFD) {
        puts("찾는 ISBN는 등록되어 있지 않습니다.");
        return RC_NFD;
    }

    schDvdInfo = GetDvdPtrByISBN(schIsbn);
    if(schDvdInfo->rentState == RENTED) {
        puts("대여 중이라 대여가 불가능합니다.");
        return RC_NRM;
    }

    fputs("대여가 가능합니다. 대여 과정을 진행합니다. \n", stdout);
    rentDvdInfo = (dvdRentInfo *)malloc(sizeof(dvdRentInfo));
    check(rentDvdInfo != NULL, "memory allocate failed! to rentDvdInfo");
    memset(rentDvdInfo, 0x00, sizeof(dvdRentInfo));

    fputs("대여 고객 ID 입력: ",stdout);
    scanf("%s", rentDvdInfo->cusID);
    fputs("대여 날짜 입력: ", stdout);
    scanf("%d", &rentDvdInfo->rentDay);

    rc = IsRegistID(rentDvdInfo->cusID);
    if(rc == RC_NFD) {
        fputs("가입 고객이 아닙니다.\n", stdout);
        return RC_NFD;
    }

    if(schDvdInfo->numOfRentCus >= RENT_LEN) {
        fputs("등록된 대여 정보의 개수를 초과하여 대여 정보를 기록할 수 없습니다.\n", stdout);
        return RC_ERR;
    }
    schDvdInfo->rentState = RENTED;
    //schDvdInfo->rentList[schDvdInfo->numOfRentCus] = *rentDvdInfo;
    memcpy(schDvdInfo->rentList[schDvdInfo->numOfRentCus].cusID, rentDvdInfo->cusID, ID_LEN);
    schDvdInfo->rentList[schDvdInfo->numOfRentCus].rentDay = rentDvdInfo->rentDay;
    schDvdInfo->numOfRentCus++;
//    setDvdRentedInfo(schIsbn, rentDvdInfo->cusID, rentDvdInfo->rentDay);

    free(rentDvdInfo);
    rentDvdInfo = NULL;

    fputs("대여가 완료되었습니다. \n", stdout);

    return RC_NRM;

error:
    if(schDvdInfo) {
        free(schDvdInfo);
        schDvdInfo = NULL;
    }
    if(rentDvdInfo) {
        free(rentDvdInfo);
        rentDvdInfo = NULL;
    }
    return RC_ERR;
}


/* 함    수: int returnDvd(void)
 * 기    능: dvd 반납 함수
 * 반    환: int
 * 
 */
int returnDvd(void)
{
    char rntIsbn[ISBN_LEN];
    dvdInfo * dvdInfo;
    int rc;

    fputs("반납 DVD ISBN 입력: ", stdout);
    scanf("%s", rntIsbn);

    rc = IsRegistISBN(rntIsbn);
    if(rc == RC_NFD) {
        fputs("등록 되지 않은 ISBN입니다.\n", stdout);
        return RC_ERR;
    }

    dvdInfo = GetDvdPtrByISBN(rntIsbn);
    if(dvdInfo == NULL) return RC_ERR;

    if(dvdInfo->rentState == RETURNED) {
        fputs("대여되지 않은 DVD 입니다. \n", stdout);
        return RC_ERR;
    }

    dvdInfo->rentState = RETURNED;
//    setDvdRented(rntIsbn);
    fputs("반납이 완료되었습니다 \n", stdout);

    return RC_NRM;

error:
    return RC_ERR;
}



/* 함    수: int showAllRntHis(void)
 * 기    능: dvd 대여 히스토리 출력 함수.
 * 반    환: int
 * 
 */
int showAllRntHis(void)
{
    char schIsbn[ISBN_LEN];
    dvdInfo * dvdInfo;
    int rc;
    int i;

    fputs("찾는 ISBN 입력: ", stdout);
    scanf("%s", schIsbn);

    rc = IsRegistISBN(schIsbn);
    if(rc == RC_NFD) {
        puts("등록된 DVD가 아닙니다.");
        return RC_ERR;
    }

    dvdInfo = GetDvdPtrByISBN(schIsbn);
    if(!dvdInfo) return RC_ERR;

    for(i = 0; i < dvdInfo->numOfRentCus; i+=1)
    {
        printf("대여일: %d \n", dvdInfo->rentList[i].rentDay);
        ShowCustomerInfo(GetCusPtrByID(dvdInfo->rentList[i].cusID));
    } 
    puts("조회를 완료하였습니다.");
    puts("");

    return RC_NRM;
error:
    return RC_ERR;
}

/* end of file */
