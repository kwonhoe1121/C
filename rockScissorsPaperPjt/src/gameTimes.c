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
#include "gameMoney.h"

static int win = 0;  //static 변수는 외부 파일에서 접근 불가.
static int lose = 0;
static int draw = 0;


/* 함    수: int getWin(void).
 * 기    능: 유저가 승리한 횟수 반환
 * 반    환: 
 *
 */
int getWin(void)
{
    return win;
}

/* 함    수: int getLose(void).
 * 기    능: 유저가 진 횟수 반환
 * 반    환: 
 *
 */
int getLose(void)
{
    return lose;
}

/* 함    수: int getDraw(void).
 * 기    능: 유저가 무승부 횟수 반환
 * 반    환: 
 *
 */
int getDraw(void)
{
    return draw;
}

/* 함    수: void setWin(int inWin).
 * 기    능: 
 * 반    환: 
 *
 */
void setWin(int inWin)
{
    win = inWin;
}

/* 함    수: void setLose(int inLose).
 * 기    능: 
 * 반    환: 
 *
 */
void setLose(int inLose)
{
    lose = inLose;
}

/* 함    수: void setDraw(int inDraw).
 * 기    능: 
 * 반    환: 
 *
 */
void setDraw(int inDraw)
{
    draw = inDraw;
}

/* 함    수: void setTimesInfo(int win, int lose, int draw)
 * 기    능: 
 * 반    환: 
 *
 */
void setTimesInfo(int win, int lose, int draw)
{
    setWin(win);
    setLose(lose);
    setDraw(draw);
}
/* 함    수: int recodeRst(int rst).
 * 기    능: 게임 결과를 기록한다.
 * 반    환: 
 *
 */
void recodeRst(int rst) 
{
    if(rst == WIN) {
        win++; 
        return;
    }

    if(rst == LOSE) {
        lose++; 
        return;
    }

    if(rst == DRAW) {
        draw++; 
        return;
    }
}

/* 함    수: int rtnOdds(void).
 * 기    능: 승률 반환한다.
 * 반    환: 
 *
 */
int rtnOdds(void) 
{
    //return (double)(win/(win+lose+draw))*100;
    debug("win %d", win);
    debug("lose %d", lose);
    debug("draw %d", draw);
    return (win*100)/(win+lose+draw);
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
}

/* 함   수: int storeTimesInfo(void)
 * 기   능: 승률 관련 정보 파일 저장
 * 반   환:
 *
 */
int storeTimesInfo(void)
{
    int win = getWin();
    int lose = getLose();
    int draw = getDraw();

    FILE * fp = fopen("times-info", "wb");

    check(fp, "times-info file open failed!!");

    debug("win: %d, lose: %d, draw: %d", win, lose, draw);

    fwrite(&win, sizeof(int), 1, fp);
    fwrite(&lose, sizeof(int), 1, fp);
    fwrite(&draw, sizeof(int), 1, fp);

    fclose(fp);

    return RC_NRM;

error:
    if(fp) fclose(fp);
    return RC_ERR;
}

/* 함   수: int loadTimesInfo(void)
 * 기   능: 승률 관련 정보 파일 불러오기
 * 반   환:
 *
 */
int loadTimesInfo(void)
{
    int win;
    int lose;
    int draw;

    FILE * fp = fopen("times-info", "rb");

    check(fp, "times-info file open failed!!");

    fread(&win, sizeof(int), 1, fp);
    fread(&lose, sizeof(int), 1, fp);
    fread(&draw, sizeof(int), 1, fp);

    setTimesInfo(win, lose, draw);
    debug("win: %d, lose: %d, draw: %d", win, lose, draw);

    fclose(fp);

    return RC_NRM;

error:
    if(fp) fclose(fp);
    return RC_ERR;
}

/* end of file */
