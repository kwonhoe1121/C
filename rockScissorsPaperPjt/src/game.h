/* Name: game.h  ver 1.0
 * Content: 게임 관련 함수 선언
 * Implementation: KJJ
 * 
 * Last modified 2008/01/01
 */

#ifndef __GAME_H__
#define __GAME_H__

//enum {ODD=1, EVEN};
enum {SCISSORS=1, ROCK, PAPER, EXIT};

int ChoiceOfCom(void);
int ChoiceOfMe(void);
void WhoIsWinner(int com, int you);
void ShowRSP(int rsp);

#endif

/* end of file */

