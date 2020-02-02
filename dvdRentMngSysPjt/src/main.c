/* Name: main.c  ver 1.0
 * Content: DVD 대여 관리 프로그램 main 
 * Implementation: KJJ
 * 
 * Last modified 2020/01/27
 */

#include "common.h"
#include "blManager.h"

enum{CUS_REGIST=1, CUS_SEARCH, DVD_REGIST, DVD_SEARCH, DVD_RENT, DVD_RETURN,  DVD_HIST, CUS_HIST, QUIT};

int main(void)
{
    int inputMenu = 0;
    int rc = RC_NRM;
    
    rc = LoadDvdSysEnv();
    //check(rc == RC_NRM, "failed load your DVD System Enviroment!!");

    while(1)
    {
        ShowMenu();
        scanf("%d", &inputMenu);
        //fflush(stdin);
  		        
        switch(inputMenu)
        {
        case CUS_REGIST:
            RegistCustomer();
            break;
        
        case CUS_SEARCH:
            SearchCusInfo();
            break;
            
        case DVD_REGIST:
            RegistDvd();
            break;

        case DVD_SEARCH:
            SearchDvdInfo();
            break;

        case DVD_RENT:
            rentDvd();
            break;

        case DVD_RETURN:
            returnDvd();
            break;
            
        case DVD_HIST:
            showAllRntDvdHis();
            break;

        case CUS_HIST:
            showAllRntCusHis();
            break;
        }
        
        if(inputMenu==QUIT)
        {
            StoreDvdSysEnv();
            freeListMem();

            puts("이용해 주셔서 고마워요~");
            break;
        }
    }    

    return rc;

error:

    freeListMem();

    return RC_ERR;
}

/* end of file */
