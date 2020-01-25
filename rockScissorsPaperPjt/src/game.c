/* Name: game.c  ver 1.0
 * Content: 게임 관련 함수 정의.
 * Implementation: YSW
 * 
 * Last modified 2008/01/01
 */
#include <time.h>
#include "common.h"
#include "game.h"

/* 함    수: int ChoiceOfCom(void).
 * 기    능: 무작위 값을 반환.
 * 반    환: 0~99의 범위에 있는 값을 반환.
 *
 */
int ChoiceOfCom(void) 
{
    //srand(time(NULL));  //seed 값 매번 다른 시간값으로 동적 생성.
    srand((unsigned int)time(NULL));  //seed 값 매번 다른 시간값으로 동적 생성.

    return rand()%100; // 0~99 범위 설정.

}

/* 함    수: int ChoiceOfMe(void).
 * 기    능: 사용자의 선택을 입력받음.
 * 반    환: 사용자 입력.
 *
 */
int ChoiceOfMe(void)
{
    int usrChoice;

    fputs("홀수이면 1, 짝수이면 2를 입력: ", stdout);

    while(1)
    {
        scanf("%d", &usrChoice);
        if(usrChoice == 1 || usrChoice == 2) 
            return usrChoice;
    }
}

/* 함    수: void WhoIsWinner(int com, int you)
 * 기    능: 승자를 가림. 
 * 반    환: void
 *
 */
void WhoIsWinner(int com, int you)
{
//    if(you == EVEN){
//        if(com % 2 == 0){
//            fputs("당신이 승자입니다!\n", stdout);
//        }else{
//            fputs("컴퓨터가 승자이군요!\n", stdout);
//        }
//    }else{
//        if(com % 2 == 0){
//            fputs("컴퓨터가 승자이군요!\n", stdout);
//        }else{
//            fputs("당신이 승자입니다!\n", stdout);
//        }
//    }
    if((com % 2) == (you % 2))
        fputs("당신이 승자입니다! \n", stdout);
    else
        fputs("컴퓨터가 승자이군요! \n", stdout);
}

/* end of file */
