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

/* 함    수: int getRatio(void).
 * 기    능: 판돈 반환
 * 반    환: 
 *
 */
int getRatio(void) 
{
    return ratio;
}

/* 함    수: void setMoneyInfo(int usrMoney, int comMoney, int ratio)
 * 기    능: 
 * 반    환: 
 *
 */
void setMoneyInfo(int usrMoney, int comMoney, int ratio)
{
    setUsrMoney(usrMoney);
    setComMoney(comMoney);
    setRatio(ratio);
}

void initYourGame(void)
{
    int youChoiceMoney;

    puts("자! 게임을 시작합니다.");
    puts("");

    fputs("# 당신의 머니를 입력하세요: ", stdout);
    scanf("%d", &youChoiceMoney);
    setFirstChoiceUsrMoney(youChoiceMoney);
    setFirstChoiceComMoney(1000);
}


/* 함   수: int storeMoneyInfo(void)
 * 기   능: 머니 관련 정보 파일 저장
 * 반   환:
 *
 */
int storeMoneyInfo(void)
{
    int usrMoney = getUsrMoney();
    int comMoney = getComMoney();
    int ratio = getRatio();

    FILE * fp = fopen("money-info", "wb");

    check(fp, "money-info file open failed!!");

    debug("usrMoney: %d, comMoney: %d, ratio: %d", usrMoney, comMoney, ratio);

    fwrite(&usrMoney, sizeof(int), 1, fp);
    fwrite(&comMoney, sizeof(int), 1, fp);
    fwrite(&ratio, sizeof(int), 1, fp);

    fclose(fp);

    return RC_NRM;

error:
    if(fp) fclose(fp);
    return RC_ERR;
}

/* 함   수: int loadMoneyInfo(void)
 * 기   능: 머니 관련 정보 파일 불러오기
 * 반   환:
 *
 */
int loadMoneyInfo(void)
{
    int usrMoney;
    int comMoney;
    int ratio;

    FILE * fp = fopen("money-info", "rb");

    check(fp, "money-info file open failed!!");

    fread(&usrMoney, sizeof(int), 1, fp);
    fread(&comMoney, sizeof(int), 1, fp);
    fread(&ratio, sizeof(int), 1, fp);

    setMoneyInfo(usrMoney, comMoney, ratio);
    debug("usrMoney: %d, comMoney: %d, ratio: %d", usrMoney, comMoney, ratio);

    fclose(fp);

    return RC_NRM;

error:
    if(fp) fclose(fp);
    return RC_ERR;
}

/* end of file */


