/* Name: screenOut.c  ver 1.0
 * Content: 콘솔 출력을 위한 함수들의 정의.
 * Implementation: KJJ
 * 
 * Last modified 2020/01/27
 */

#include "common.h"
#include "cusInfo.h"
#include "dvdInfo.h"
#include "rentInfo.h"
#include "screenOut.h" // 함수 내에서 함수 정의된 순서에 상관없이 함수들을 호출하고 싶으면 해당 해더파일도 추가해야한다.

/* 프로그램 사용을 위한 메뉴 */
void ShowMenu(void)
{
    //system("cls");   //stdlib.h
    
    printf("━━━━━ 메  뉴 ━━━━━━━ \n");
    printf(" 1. 신규가입 \n");
    printf(" 2. 고객검색 \n");
    printf("-------------------- \n");
    printf(" 3. DVD 등록 \n");
    printf(" 4. DVD 검색 \n");
    printf("-------------------- \n");
    printf(" 5. DVD 대여 \n");
    printf(" 6. DVD 반납 \n");
    printf("-------------------- \n");
    printf(" 7. DVD 대여고객 전체 조회 \n");
    printf(" 8. 고객 대여 DVD 전체 조회 \n");
    printf("-------------------- \n");
    printf(" 9. 종료 \n");
    printf("━━━━━━━━━━━━━━━━━━━━ \n");
    printf("선택》 ");
}


/* 고객 개인의 기본 정보 출력 */
void ShowCustomerInfo(cusInfo * pCus)
{    
    printf("┏━━━━━━━━━━━━━━━━ \n");
    printf("┃ ▶ ID: %s \n", pCus->ID);
    printf("┃ ▶ 이름: %s \n", pCus->name);
    printf("┃ ▶ 전화번호: %s \n", pCus->phoneNum);
    printf("┗━━━━━━━━━━━━━━━━ \n\n");
    
    //getchar(); // 키 입력시 넘어가기 위해서..
}

/* DVD 기본 정보 출력 */
void ShowDvdInfo(dvdInfo * pDvd)
{    
    printf("┏━━━━━━━━━━━━━━━━ \n");
    printf("┃ ▶ ISBN: %s \n", pDvd->ISBN);
    printf("┃ ▶ 타이틀: %s \n", pDvd->title);
    printf("┃ ▶ 장르: "); showGenre(pDvd->genre);
    printf("┗━━━━━━━━━━━━━━━━ \n\n");
    
    //getchar(); // 키 입력시 넘어가기 위해서..
}

/* DVD 대여 정보 출력 */
void ShowRentDayInfo(dvdRentInfo * pRnt)
{    
    printf("┏━━━━━━━━━━━━━━━━ \n");
    printf("┃ ▶ ISBN: %s \n", pRnt->ISBN);
    printf("┃ ▶ 대여일: %d \n", pRnt->rentDay);
    printf("┗━━━━━━━━━━━━━━━━ \n\n");
    
    //getchar(); // 키 입력시 넘어가기 위해서..
}

void showGenre(int gen)
{
    switch(gen)
    {
        case ACTION:
            fputs("액션 \n", stdout);
            break;
        case COMIC:
            fputs("코믹 \n", stdout);
            break;
        case SF:
            fputs("SF \n", stdout);
            break;
        case ROMANTIC:
            fputs("로맨스 \n", stdout);
            break;
        default:
            debug("Must not be shown this message when calling showGenre()");
            break;
    }
}


/* end of file */
