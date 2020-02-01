/* Name: main.c  ver 1.0
 * Content: DVD 대여 관리 프로그램 main 
 * Implementation: KJJ
 * 
 * Last modified 2020/01/27
 */

#include "common.h"
#include "cusManager.h"
#include "dvdManager.h"
#include "screenOut.h"

enum{CUS_REGIST=1, CUS_SEARCH, DVD_REGIST, DVD_SEARCH, QUIT};

int main(void)
{
    int inputMenu = 0;
    int rc;
    
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
        }
        
        if(inputMenu==QUIT)
        {
            //동적할당 메모리 해제해줘야 한다.
            puts("이용해 주셔서 고마워요~");
            break;
        }
    }    

    return RC_NRM;

error:
    
    return RC_ERR;
}

/* end of file */
