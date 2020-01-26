/* Name: gameTimes.c  ver 1.0
 * Content: 게임 승률 관련 함수 정의.
 * Implementation: KJJ
 * 
 * Last modified 2020/01/26
 */
#include <time.h>
#include "common.h"
#include "game.h"
#include "gameTimes.h"

static int win = 0;  //static 변수는 외부 파일에서 접근 불가.
static int lose = 0;
static int draw = 0;

/* 함    수: int recodeRst(int rst).
 * 기    능: 게임 결과를 기록한다.
 * 반    환: 
 *
 */
void recodeRst(int rst) 
{
    if(rst == WIN) win++;
    if(rst == LOSE) lose++;
    if(rst == DRAW) draw++;
}

/* 함    수: int rtnOdds(void).
 * 기    능: 승률 반환한다.
 * 반    환: 
 *
 */
int rtnOdds(void) 
{
    return (double)win/(win+lose+draw)*100;
}

/* 함    수: void showRst(void).
 * 기    능: 최종 결과 출력한다.
 * 반    환: 
 *
 */
void showRst(void) 
{
    fputs("☆☆☆☆☆☆ 최종 결과 ☆☆☆☆☆☆ \n", stdout);	
    printf("최종 승률: %d %% \n", rtnOdds());
    fputs("이용해 주셔서 고마워요~ \n", stdout);
}

/* end of file */
