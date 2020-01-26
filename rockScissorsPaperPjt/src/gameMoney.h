/* Name: gameMoney.h  ver 1.0
 * Content: 게임 머니 관련 함수 선언
 * Implementation: KJJ
 * 
 * Last modified 2020/01/26
 */

#ifndef __GAME_MONEY_H__
#define __GAME_MONEY_H__

void calMoney(int rst);
void setRatio(int money);

void setUsrWinRstMoney(void);
void setComWinRstMoney(void);

void setUsrMoney(int money);
void setComMoney(int money);
int getUsrMoney(void);
int getComMoney(void);

#endif

/* end of file */

