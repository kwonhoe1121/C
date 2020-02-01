/* Name: dvdManager.c  ver 1.0
 * Content: DVD 관련 업무 처리 함수.
 * Implementation: KJJ
 * 
 * Last modified 2020/02/01
 */

#include "common.h"
#include "dvdInfo.h"
#include "dvdInfoAccess.h"
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
        puts("찾는 ISBN는 가입되어 있지 않습니다.");
        return RC_NFD;
    }

    ShowDvdInfo(GetDvdPtrByISBN(schIsbn));
    return RC_NRM;

}

/* end of file */
