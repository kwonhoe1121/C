/* Name: gameContinue.c  ver 1.0
 * Content: 게임 저장/복원 관련 함수 정의.
 * Implementation: KJJ
 * 
 * Last modified 2020/01/26
 */
#include <time.h>
#include "common.h"
#include "game.h"
#include "gameTimes.h"
#include "gameMoney.h"
#include "gameContinue.h"

static int exitStatus;

/* 함   수: void setExitStatus(int exit)
 * 기   능: 종료 상태 저장 함수
 * 반   환:
 *
 */
void setExitStatus(int exit)
{
    if(exit != STORE_EXIT)
    {
        exitStatus = NRM_EXIT;
        debug("setExitStatus() exitStatus value is %d ", exit);
        return;
    }

    exitStatus = exit;
    debug("setExitStatus() exitStatus value is %d ", exit);
}

/* 함   수: int getExitStatus(void)
 * 기   능: 종료 상태 반환 함수
 * 반   환:
 *
 */
int getExitStatus(void)
{
    return exitStatus;
}

/* 함   수: int storeExitStauts(void)
 * 기   능: 종료 상태 파일 저장 함수
 * 반   환:
 *
 */
int storeExitStauts(void)
{
    int exitSts;

    FILE * fp = fopen("exit-status", "wb");

    check(fp, "exit-status file open failed!");

    exitSts = getExitStatus();

    debug("exitSts value is %d in storeExitStauts()", exitSts);

    fwrite(&exitSts, sizeof(int), 1, fp);

    fclose(fp);

    return RC_NRM;

error:
    if(fp) fclose(fp);
    return RC_ERR;
}

/* 함   수: int loadExitStatus(void)
 * 기   능: 종료 상태 파일 읽기 함수
 * 반   환:
 *
 */
int loadExitStatus(void)
{
    int exitSts;

    FILE * fp = fopen("exit-status", "rb");

    check(fp, "exit-status file open failed!!");

    fread(&exitSts, sizeof(int), 1, fp);

    setExitStatus(exitSts);
    debug("exitSts value is %d in loadExitStatus()", exitSts);

    fclose(fp);

    return RC_NRM;

error:
    if(fp) fclose(fp);
    return RC_ERR;
}

int loadYourGameEnv(void)
{
    int rc;

    rc = loadExitStatus();
    //check(rc == RC_NRM, "loadExitStatus() function error!");
    if(rc == RC_ERR) //파일이 없으면
        setExitStatus(NRM_EXIT);

    debug("%d", getExitStatus());
    if(getExitStatus() != STORE_EXIT) { 
        initYourGame();
    }else{
        rc = isContinueYourGame();
        check(rc == RC_NRM, "loadYourGameEnv() function failed!!");
    }

	printf("당신의 게임 머니: %d \n", getUsrMoney());
    printf("컴퓨터의 게임 머니: %d \n", getComMoney());
    puts("");

    return RC_NRM;

error:
    return RC_ERR;
}

int storeYourGameEnv(void)
{
    int rc;

	debug("after showRst() exitStatus value is %d", getExitStatus());

    if(getExitStatus() != NRM_EXIT) {
        rc = isStoreYourGameInfo();
        check(rc == RC_NRM, "isStoreYourGameInfo() function failed!");
    }else{
        rc = storeExitStauts();
        check(rc == RC_NRM, "storeExitStauts() function failed!!");
    }

    return RC_NRM;

error:
    return RC_ERR;
} 

int isStoreYourGameInfo(void)
{
    int isYourChoice;
    int rc;

    while(1)
    {
        fputs("게임 내용을 저장하시겠습니까? <Yes 1, No 0>: ", stdout);
        scanf("%d", &isYourChoice);
        
        if(isYourChoice == 1 || isYourChoice == 0)
            break;
    }

    if(isYourChoice == 1) {
        
        setExitStatus(STORE_EXIT);
        debug("exitStatus in isStoreYourGameInfo() function is %d", getExitStatus());

        rc = storeExitStauts();
        check(rc == RC_NRM, "storeExitStauts() function failed!");

        rc = storeMoneyInfo();
        check(rc == RC_NRM, "storeMoneyInfo() function failed!");

        rc = storeTimesInfo();
        check(rc == RC_NRM, "storeTimesInfo() function failed!");
    }

    if(isYourChoice == 0) {
        setExitStatus(NRM_EXIT);
        rc = storeExitStauts();
        check(rc == RC_NRM, "storeExitStauts() function failed!");
    }

    return RC_NRM;

error:
    return RC_ERR;
}

int isContinueYourGame(void)
{
    int yourChoice;
    int rc;

    while(1)
    {
        fputs("게임을 이어서 하시겠습니까? <Yes 1, No 0> : ", stdout);
        scanf("%d", &yourChoice);

        if(yourChoice == 1 || yourChoice == 0)
            break;
    }

    if(yourChoice == 1)
    {
        rc = loadTimesInfo();
        check(rc == RC_NRM, "loadTimesInfo() function error!");
        rc = loadMoneyInfo();
        check(rc == RC_NRM, "loadMoneyInfo() function error!");
    }

    if(yourChoice == 0)
    {
        initYourGame();
    }

    return RC_NRM;

error:
    return RC_ERR;
}

/* end of file */
