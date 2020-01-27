/* Name: gameTimes.h  ver 1.0
 * Content: 게임 승률 관련 함수 선언
 * Implementation: KJJ
 * 
 * Last modified 2020/01/26
 */

#ifndef __GAME_TIMES_H__
#define __GAME_TIMES_H__

enum {WIN=1, LOSE, DRAW};

void recodeRst(int rst);
int rtnOdds(void);
void showRst(void);

int getWin(void);
int getLose(void);
int getDraw(void);

void setDraw(int inDraw);
void setLose(int inLose);
void setWin(int inWin);

void setTimesInfo(int win, int lose, int draw);
int loadTimesInfo(void);
int storeTimesInfo(void);

#endif

/* end of file */

