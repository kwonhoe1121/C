/* Name: main.c  ver 1.0
 * Content: DVD 대여 관리 프로그램 main 
 * Implementation: KJJ
 * 
 * Last modified 2020/01/27
 */

#include "common.h"
#include "cusManager.h"
#include "screenOut.h"

enum{CUS_REGIST=1, CUS_SEARCH, QUIT};

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
        }
        
        if(inputMenu==QUIT)
        {
            puts("이용해 주셔서 고마워요~");
            break;
        }
    }    

    return RC_NRM;

error:
    
    return RC_ERR;
}

/* end of file */
