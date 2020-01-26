/* Name: gameMoney.c  ver 1.0
 * Content: 게임 머니 관련 함수 정의.
 * Implementation: KJJ
 * 
 * Last modified 2020/01/26
 */
#include <time.h>
#include "common.h"
#include "game.h"
#include "gameTimes.h"
#include "gameMoney.h"

static int usrMoney;
static int comMoney;
static int ratio;

/* 함    수: void calMoney(int rst).
 * 기    능: 결과에 근거해서 돈계산한다.
 * 반    환: 
 *
 */
//void calMoney(int rst) 
//{
//    if(rst == WIN) {
//        setUsrMoney(usrMoney += ratio);
//        setComMoney(comMoney -= ratio);
//        return;
//    }
//
//    if(rst == LOSE) {
//        setUsrMoney(usrMoney -= ratio);
//        setComMoney(comMoney += ratio);
//        return;
//    }
//
//    if(rst == DRAW) {
//        return;
//    }
//}

/* 함   수: void setUsrWinRstMoney(void)
 * 기   능: 유저가 이긴 경우 돈 계산하는 함수
 * 반   환:
 *
 */
void setUsrWinRstMoney(void)
{
    usrMoney += ratio;
    comMoney -= ratio;
}

/* 함   수: void setComWinRstMoney(void)
 * 기   능: 컴퓨터가 이긴 경우 돈 계산하는 함수
 * 반   환:
 *
 */
void setComWinRstMoney(void)
{
    usrMoney -= ratio;
    comMoney += ratio;
}

/* 함   수: void setRatio(int money)
 * 기   능: 판돈 설정
 * 반   환:
 *
 */
void setRatio(int money)
{
    if(money < 0)
        ratio=0;
    else
        ratio=money;
}

/* 함   수: void setFirstChoiceUsrMoney(int money)
 * 기   능: 사용자 최초 머니 선택 설정.
 * 반   환:
 *
 */
void setFirstChoiceUsrMoney(int money)
{
    setUsrMoney(money);
}

/* 함   수: void setFirstChoiceComMoney(int money)
 * 기   능: 컴퓨터 최초 머니 선택 설정.
 * 반   환:
 *
 */
void setFirstChoiceComMoney(int money)
{
    setComMoney(money);
}

/* 함   수: int setRatioByUsr(int ratio)
 * 기   능: 유저가 선택한 판돈 경계검사 후 설정
 * 반   환:
 *
 */
int setRatioByUsr(int ratio)
{
    if(ratio > getUsrMoney()) //유저 소유 금액 초과
        return 1;
    if(ratio > getComMoney()) //컴퓨터 소유 금액 초과
        return -1;

    setRatio(ratio);
    return 0;
}
    

/* getter setter 개념을 생각한다. */

/* 함   수: void setUsrMoney(int money)
 * 기   능: 유저 머니 설정
 * 반   환:
 *
 */
void setUsrMoney(int money)
{
    if(money < 0) return;

    usrMoney = money;
}

/* 함   수: void setComMoney(int money)
 * 기   능: 컴퓨터 머니 설정
 * 반   환:
 *
 */
void setComMoney(int money)
{
    if(money < 0) return;

    comMoney = money;
}

/* 함    수: int getUsrMoney(void).
 * 기    능: 유저 돈 반환
 * 반    환: 
 *
 */
int getUsrMoney(void) 
{
    return usrMoney;
}

/* 함    수: int getComMoney(void).
 * 기    능: 컴퓨터 돈 반환
 * 반    환: 
 *
 */
int getComMoney(void) 
{
    return comMoney;
}

/* end of file */
