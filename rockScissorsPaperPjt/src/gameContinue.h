/* Name: gameContinue.h  ver 1.0
 * Content: 게임 저장 관련 함수 선언
 * Implementation: KJJ
 * 
 * Last modified 2020/01/26
 */

#ifndef __GAME_CONTINUE_H__
#define __GAME_CONTINUE_H__

enum {STORE_EXIT=1, NRM_EXIT};

int getExitStatus(void);
void setExitStatus(int exit);

int isStoreYourGameInfo(void);
int isContinueYourGame(void);

int loadExitStatus(void);
int storeExitStauts(void);

int loadYourGameEnv(void);
int storeYourGameEnv(void);

#endif

/* end of file */

