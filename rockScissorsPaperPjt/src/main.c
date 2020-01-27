/* Name: main.c  ver 1.0
 * Content: 게임 main 함수.
 * Implementation: KJJ
 * 
 * Last modified 2020/01/26
 */

#include "common.h"
#include "game.h"
#include "gameTimes.h"
#include "gameMoney.h"
#include "gameContinue.h"

int main(void)
{
    int com;
    int you;
    int youChoiceRatio;
    int rc;

    system("clear");

    rc = loadYourGameEnv();
    check(rc == RC_NRM, "loadYourGameEnv() function failed()!!");
    
    while(1) {
		puts("☆☆☆☆☆☆ 대결! ☆☆☆☆☆☆!!");

		you=ChoiceOfMe();
        if(you == EXIT) {
            setExitStatus(STORE_EXIT);
            break;
        }
        com=ChoiceOfCom();

        puts("$ 판돈을 설정해주세요! $");
        fputs("판돈 입력 : ", stdout);
        scanf("%d", &youChoiceRatio);
        puts("");

//        if(youChoiceRatio > getUsrMoney()) {
//            puts("소유하고 있는 금액 내에서 거세요!");
//            continue;
//        }
//
//        if(youChoiceRatio > getComMoney()) {
//            puts("컴퓨터 소유 금액 초과입니다!");
//            continue;
//        }
//        setRatio(youChoiceRatio);

        rc = setRatioByUsr(youChoiceRatio); //setRatio 함수를 추가 확장하여 경계값을 포함시킴.
        if(rc == 1) {
            puts("소유하고 있는 금액 내에서 거세요!");
            continue;
        }

        if(rc == -1) {
            puts("컴퓨터 소유 금액 초과입니다!");
            continue;
        }


		puts("");
	   
		puts("★★★★★★ 결과! ★★★★★★!!");
		WhoIsWinner(com, you);
		
	//	if(com==SCISSORS)
	//        puts("▷ 컴퓨터의 선택은 가위. ");
	//    else if(com==ROCK)
	//        puts("▷ 컴퓨터의 선택은 바위. ");
	//    else
	//        puts("▷ 컴퓨터의 선택은 보. ");
		fputs("▷ 컴퓨터의 선택은 ", stdout);
		ShowRSP(com);
		
	//    if(you==EVEN)
	//        puts("▷ 당신의 선택은 짝수. ");
	//    else
	//        puts("▷ 당신의 선택은 홀수. ");

	//	if(you==SCISSORS)
	//        puts("▷ 당신의 선택은 가위. ");
	//    else if(you==ROCK)
	//        puts("▷ 당신의 선택은 바위. ");
	//    else
	//        puts("▷ 당신의 선택은 보. ");
		fputs("▷ 당신의 선택은 ", stdout);
		ShowRSP(you);

        printf("승률: %d %% \n", rtnOdds());
        printf("게이머 머니: %d  \n", getUsrMoney());
        printf("컴퓨터 머니: %d  \n", getComMoney());

        if(getUsrMoney() == 0 || getComMoney() == 0) {
            setExitStatus(NRM_EXIT); //게임이 파산으로 끝나면 그냥 종료 
            break;
        }

        puts("");

    }
    puts("");
    
    showRst();

    rc = storeYourGameEnv();
    check(rc == RC_NRM, "storeYourGameEnv() function failed!!");

    fputs("이용해 주셔서 고마워요~ \n", stdout);

    return RC_NRM;

error:
    return RC_ERR;
}
