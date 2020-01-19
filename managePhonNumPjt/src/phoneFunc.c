/* Name: phoneFunc.c  ver 1.2
 * Content: 전화번호 컨트롤 함수.
 * Implementation: KJJ
 * 
 * Last modified 2020/01/12
 */

#include "common.h"
#include "phoneData.h"
#include "screenOut.h"

#define LIST_NUM   100

int numOfData=0;
//phoneData phoneList[LIST_NUM];  //구조체 배열 선언
phoneData * phoneList[LIST_NUM]; //구조체 포인터 배열 선언

/* 함    수: void InputPhoneData(void)
 * 기    능: 전화번호 관련 데이터 입력 받아서 저장. 
 * 반    환: void.
 *
 */
void InputPhoneData(void)
{
    //phoneData data;
    phoneData * pData;
	int i = 0;
    
    if(numOfData>=LIST_NUM)
    {
        puts("메모리 공간이 부족합니다.");
        return;
    }

	pData = (phoneData*)malloc(sizeof(phoneData));
    
    fputs("이름 입력: ", stdout);
    gets(pData->name);
    //gets(data.name);
    
    fputs("전화번호 입력: ", stdout);
   gets(pData->phoneNum);
    //gets(data.phoneNum);
    
	//phoneList[numOfData] = (phoneData*)malloc(sizeof(phoneData)); 
    //phoneList[numOfData]=&data;
	//memcpy(phoneList[numOfData]->name, data.name, sizeof(NAME_LEN));
	//memcpy(phoneList[numOfData]->phoneNum, data.phoneNum, sizeof(PHONE_LEN));
    //phoneList[numOfData]=&data;  //data는 지역 변수로 설정 되기 때문에 함수 호출이 끝나면 메로리가 사라짐. -> 힙 영역으로 메모리를 할당 받아야 한다. 일반 대입은 데이터 복사가 이뤄짐으로 데이터가 유지 될 수 있지만 주소 복사는 불가능하다!!!!!!! 중요!!
	for(i=0; i<numOfData; i+=1) {
		if(memcmp(pData->name, phoneList[i]->name, sizeof(NAME_LEN)) == 0 && memcmp(pData->phoneNum, phoneList[i]->phoneNum, sizeof(PHONE_LEN)) == 0){
			fputs("이미 입력된 데이터 입니다. ", stdout);
			free(pData); //동적 할당된 메모리 해제
			getchar();
			return;
		}
	}

	phoneList[numOfData] = pData;
    numOfData++;
    
    puts("입력이 완료되었습니다.");
    getchar();
}

/* 함    수: void ShowAllData(void)
 * 기    능: 저장된 데이터 전체 출력. 
 * 반    환: void.
 *
 */
void ShowAllData(void)
{
    int i;
    
    for(i=0; i<numOfData; i++)
    {
        ShowPhoneInfoByPtr(phoneList[i]);
    }
    
    puts("출력이 완료되었습니다.");
    getchar();
}

/* 함    수: int ShearchPhoneData(void)
 * 기    능: 저장된 데이터 검색. 
 * 반    환: int.
 *
 */
int SearchPhoneData(void)
{
	//phoneData data;
//	phoneData * pData;
	char searchName[NAME_LEN];
	int i;
	int isName=0; //검색된 이름 개수 반환한다. 

	fputs("찾는 이름은? ", stdout);
	scanf("%s", searchName);
	
	for(i=0; i<numOfData; i+=1){
		if(memcmp(searchName, phoneList[i]->name, sizeof(NAME_LEN)) == 0){
			ShowPhoneInfoByPtr(phoneList[i]);
			isName++;
		}
	}
	
	if(isName){
		fputs("검색이 완료되었습니다.\n", stdout);
		return isName;
	}else{
		fputs("검색에 실패하였습니다.\n", stdout);	
		return isName;
	}
}

/* 함    수: void DeletePhoneData(void)
 * 기    능: 저장된 데이터 삭제. 
 * 반    환: void.
 *
 */
void DeletePhoneData(void)
{
	//phoneData data;
	//phoneData * pData;
	char deleteName[NAME_LEN];
	int i; 
//	int nameCnt=0;
//	int selectedNum=0;
	int idxOfMatchingData[LIST_NUM]; //삭제 시킬 idx 주소값을 저장시켜놓는 배열
	int matchedCount=0;
	int selection=0;
	int delIdx=0;

	fputs("찾는 이름은? ", stdout);
	scanf("%s", deleteName);
//
//	for(i=0; i<numOfData; i+=1){
//		if(memcmp(pData.name, phoneList[i].name, sizeof(NAME_LEN)) == 0) {
//			if(i != (numOfData-1)){
//				for(j=i; j<numOfData; j+=1){
//					phoneList[j]=phoneList[j+1];
//				}
//				isDelete=1;
//				numOfData--;
//			}else{
//				isDelete=1;
//				numOfData--;
//			}
//		}
//	}	
//
//	for(i=0; i<numOfData; i+=1){
//		if(memcmp(data.name, phoneList[i]->name, sizeof(NAME_LEN)) == 0) {
//			for(j=i; j<numOfData-1; j+=1){
//				phoneList[j]=phoneList[j+1];
//			}
//			numOfData--;
//			fputs("삭제가 완료되었습니다. \n", stdout);
//			return;
//		}
//	}	

//	for(i=0; i<numOfData; i+=1){ //동명이인이 있는지 먼저 확인한다.
//		if(memcmp(deleteName, phoneList[i]->name, sizeof(NAME_LEN)) == 0) {
//			nameCnt++;
//			if(nameCnt > 1) break;
//		}
//	}
//	
//	if(nameCnt > 1) { //동명이인이 존재할 경우
//		nameCnt=0;
//		for(i=0; i<numOfData; i+=1){
//			if(memcmp(deleteName, phoneList[i]->name, sizeof(NAME_LEN)) == 0) {
//				printf("NUM. %d\n", ++nameCnt);
//				ShowPhoneInfoByPtr(phoneList[i]);
//			}
//		}
//		fputs("선택: ", stdout); 
//		scanf("%d", &selectedNum);
//		
//		nameCnt=0;
//		for(i=0; i<numOfData; i+=1) {
//			if(memcmp(deleteName, phoneList[i]->name, sizeof(NAME_LEN)) == 0) {
//				nameCnt++;
//				if(selectedNum == nameCnt) {
//					free(phoneList[i]);
//					for(j=i; j<numOfData-1; j+=1){
//						phoneList[j]=phoneList[j+1];
//					}
//					numOfData--;
//					fputs("삭제가 완료되었습니다. \n", stdout);
//					return;
//				}
//			}
//		}
//	}else{ 
//		for(i=0; i<numOfData; i+=1){
//			if(memcmp(deleteName, phoneList[i]->name, sizeof(NAME_LEN)) == 0) {
//				free(phoneList[i]);
//				for(j=i; j<numOfData-1; j+=1){
//					phoneList[j]=phoneList[j+1];
//				}
//				numOfData--;
//				fputs("삭제가 완료되었습니다. \n", stdout);
//				return;
//			}
//		}	
//	}
//
//	fputs("해당 이름은 존재하지 않습니다 \n", stdout);

	for(i=0; i<numOfData; i+=1) {
		if(memcmp(phoneList[i]->name, deleteName, sizeof(NAME_LEN))==0){
			idxOfMatchingData[matchedCount++]=i;
		}
	}

	if(matchedCount==0){ //삭제시킬 delIdx값 선택
		puts("찾는 이름의 데이터가 존재하지 않습니다.");
		getchar();
		return;
	}else if(matchedCount==1){
		delIdx=idxOfMatchingData[0];
	}else{
		for(i=0; i<matchedCount; i+=1){
			printf("NUM. %d \n", i+1);
			ShowPhoneInfoByPtr(phoneList[idxOfMatchingData[i]]);
		}
		
		fputs("선택 : ", stdout);
		scanf("%d", &selection);
		getchar();

		delIdx=idxOfMatchingData[selection-1];
	}

	free(phoneList[delIdx]);
	for(i=delIdx; i<numOfData-1; i+=1){
		phoneList[i]=phoneList[i+1];
	}
	numOfData-=1;
	puts("삭제가 완료되었습니다.");
	getchar();
}

/* 함    수: void StoreDataToFile(void);
 * 기    능: 종료 직전, 파일에 데이터 저장 
 * 반    환: void.
 *
 */
void StoreDataToFile(void){
	FILE *pWData = NULL;
	int i;
	int rc;

	pWData = fopen("phone-data-list", "w");

	if(!pWData) {
		fputs("파일을 읽을 수 없습니다. \n", stdout);
		return;
	}

	fwrite(&numOfData, sizeof(int), 1, pWData);
	for(i=0; i<numOfData; i+=1){
		fprintf(pWData, "%s\n%s\n", phoneList[i]->name, phoneList[i]->phoneNum);
		free(phoneList[i]);
	}

	fclose(pWData);
}
		

/* 함    수: void LoadDataFromFile(void)
 * 기    능: 실행 직후, 곧바로 파일로부터 데이터 복원 
 * 반    환: void.
 *
 */
void LoadDataFromFile(void){
	FILE * pRData = NULL;
	phoneData * pData = NULL;
	int i, sLen;

	pRData = fopen("phone-data-list", "r");

	if(!pRData) {
		fputs("파일을 읽을 수 없습니다. \n", stdout);
		return;
	}

//	for(i=0; i<numOfData; i+=1) {
//		if(feof(pRData) != 0) {
//			fgets(phoneList[i]->name, sizeof(NAME_LEN), pRData);
//			fgets(phoneList[i]->phoneNum, sizeof(PHONE_LEN), pRData);
//		}else{
//			break;
//		}
//	}

	//데이터 생성 시 메모리 동적 할당 해줘야 한다. 내가 삽질한 이유.. 
//	while(feof(pRData) != EOF){
//		pData = (phoneData*)malloc(sizeof(phoneData));
//
//		fgets(pData->name, NAME_LEN, pRData);
//		
//		fgets(pData->phoneNum, PHONE_LEN, pRData);
//		phoneList[numOfData++] = pData;
//
//	}
	
	fread(&numOfData, sizeof(int), 1, pRData);

	for(i=0; i<numOfData; i+=1){
		phoneList[i]=(phoneData*)malloc(sizeof(phoneData));

		fgets(phoneList[i]->name, NAME_LEN, pRData);
		sLen = strlen(phoneList[i]->name);
		phoneList[i]->name[sLen-1] = 0;

		fgets(phoneList[i]->phoneNum, PHONE_LEN, pRData);
		sLen = strlen(phoneList[i]->phoneNum);
		phoneList[i]->phoneNum[sLen-1] = 0;
	}	

	fclose(pRData);
}
				

/* end of file */
 
