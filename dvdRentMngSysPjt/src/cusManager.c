/* Name: cusManager.c  ver 1.0
 * Content: 고객 관련 업무 처리 함수.
 * Implementation: KJJ
 * 
 * Last modified 2020/01/27
 */

#include "common.h"
#include "cusInfo.h"
#include "cusInfoAccess.h"
#include "screenOut.h"

/* 함    수: void RegistCustomer(void)
 * 기    능: 신규 회원 가입. 
 * 반    환: int
 *
 */
int RegistCustomer(void)
{
    cusInfo * enrCus;
    int rc;

    enrCus = (cusInfo*)malloc(sizeof(cusInfo));
    check(enrCus != NULL, "Memory allocate failed in RegistCustomer()");
    memset(enrCus, 0x00, sizeof(cusInfo));

    fputs("ID 입력: ", stdout);
    scanf("%s", enrCus->ID);

    rc = IsRegistID(enrCus->ID);

    if(rc == RC_NRM) {
        puts("해당 ID는 사용 중에 있습니다. 다른 ID를 선택해주세요!");
        return RC_DUP;
    }

    fputs("이름 입력 : ", stdout);
    scanf("%s", enrCus->name);
    fputs("전화번호 입력 : ", stdout);
    scanf("%s", enrCus->phoneNum);

    rc = AddCusInfo(enrCus->ID, enrCus->name, enrCus->phoneNum);
    if(rc == RC_NRM) {
        puts("해당 ID 저장에 실패하였습니다!"); 
        return RC_ERR;
    }

    puts("가입이 완료되었습니다.");

    return RC_NRM;

error:
    if(enrCus) {
        free(enrCus);
        enrCus = NULL;
    }
    return RC_ERR;
}

/* 함    수: void SearchCusInfo(void)
 * 기    능: ID를 통한 회원 정보 검색
 * 반    환: int
 * 
 */
int SearchCusInfo(void)
{
    char schId[ID_LEN];
    int rc;

    fputs("찾는 ID 입력: ", stdout);
    scanf("%s", schId);

    rc = IsRegistID(schId);

    if(rc == RC_NFD) {
        puts("찾는 ID는 가입되어 있지 않습니다.");
        return RC_NFD;
    }

    ShowCustomerInfo(GetCusPtrByID(schId));
    return RC_NRM;
}

/* end of file */
