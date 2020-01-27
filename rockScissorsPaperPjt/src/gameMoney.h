/* Name: gameMoney.h  ver 1.0
 * Content: 게임 머니 관련 함수 선언
 * Implementation: KJJ
 * 
 * Last modified 2020/01/26
 */

#ifndef __GAME_MONEY_H__
#define __GAME_MONEY_H__

void setUsrMoney(int money);
void setComMoney(int money);
int getUsrMoney(void);
int getComMoney(void);
int getRatio(void);

//void calMoney(int rst);
void setUsrWinRstMoney(void);
void setComWinRstMoney(void);
void setRatio(int money);

/* 함수를 경계검사, 유효값 검사 등 추가 확장 시 이전에 정의했던 함수를 추가적으로 정의하는 것이 좋다 */
void setFirstChoiceUsrMoney(int money);
void setFirstChoiceComMoney(int money);
int setRatioByUsr(int ratio);

void setMoneyInfo(int usrMoney, int common, int ratio);
int loadMoneyInfo(void);
int storeMoneyInfo(void);
void initYourGame(void);

#endif

/* end of file */

