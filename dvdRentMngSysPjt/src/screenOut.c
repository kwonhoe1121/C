/* Name: screenOut.c  ver 1.0
 * Content: 콘솔 출력을 위한 함수들의 정의.
 * Implementation: KJJ
 * 
 * Last modified 2020/01/27
 */

#include "common.h"
#include "cusInfo.h"

/* 프로그램 사용을 위한 메뉴 */
void ShowMenu(void)
{
    system("cls");   //stdlib.h
    
    printf("━━━━━ 메  뉴 ━━━━━━━ \n");
    printf(" 1. 신규가입 \n");
    printf(" 2. 고객검색 \n");
    printf(" 3. 종료 \n");
    printf("━━━━━━━━━━━━━━━━ \n");
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
    
    getchar(); // 키 입력시 넘어가기 위해서..
}


/* end of file */
