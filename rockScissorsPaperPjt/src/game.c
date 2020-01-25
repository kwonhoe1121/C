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

    //return rand()%100; // 0~99 범위 설정.
    return (rand()%3) + 1; // 1~3 범위 설정.

}

/* 함    수: int ChoiceOfMe(void).
 * 기    능: 사용자의 선택을 입력받음.
 * 반    환: 사용자 입력.
 *
 */
int ChoiceOfMe(void)
{
    int usrChoice;

    while(1)
    {
        fputs("가위<1> 바위<2> 보<3> 당신의 선택은? ", stdout);
        scanf("%d", &usrChoice);
        if(usrChoice == 1 || usrChoice == 2 || usrChoice == 3) 
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
//    if((com % 2) == (you % 2))
//        fputs("당신이 승자입니다! \n", stdout);
//    else
//        fputs("컴퓨터가 승자이군요! \n", stdout);

//    if(com == you) {
//        fputs("비겼습니다.\n", stdout);
//        return;
//    }
//
//    if(you == SCISSORS){
//        if(com == ROCK)
//            fputs("컴퓨터가 승자이군요!\n", stdout);
//        else
//            fputs("당신이 승자입니다!\n", stdout);
//    }
//
//    if(you == ROCK){
//        if(com == SCISSORS)
//           fputs("당신이 승자입니다!\n", stdout);
//        else
//           fputs("컴퓨터가 승자이군요!\n", stdout);
//    }
//
//    if(you == PAPER){
//        if(com == ROCK)
//          fputs("당신이 승자이군요!\n", stdout);
//        else
//          fputs("컴퓨터가 승자이군요!\n", stdout);
//    }

    int outcome = you - com; //유저 기준으로 판단.

    switch(outcome)
    {
        case 0:
            fputs("비겼습니다. \n", stdout);
            return;

        case 1: case -2: //유저가 이기는 경우만 선택한다.
            fputs("당신이 승자입니다.\n", stdout);
            return;
    }

    fputs("컴퓨터가 승자입니다.\n", stdout); //유저가 이기는 경우를 제외하면 모두 컴퓨터가 승자인 경우만 남는다.
}

/* 함    수: void ShowRSP(int rsp)
 * 기    능: 상수에 따른 문자열(가위, 바위, 보) 출력
 * 반    환: void
 *
 */
void ShowRSP(int rsp)
{
    switch(rsp)
    {
        case SCISSORS:
            fputs("가위\n", stdout);
            break;
        case ROCK:
            fputs("바위\n", stdout);
            break;
        case PAPER:
            fputs("보\n", stdout);
            break;
    }
}


/* end of file */
