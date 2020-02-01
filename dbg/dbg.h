/* Description 
 * C 언어는 오류 코드를 반환하고 오류를 점검할 수 있도록 전역변수 errno값을 설정하는 것으로 문제점을 해결한다.
 * C 코드량이 늘어날수록 아래와 같은 패턴으로 작성하게 될 것이다.
 *     - 함수를 호출한다.
 *     - 반환 값이 오류인지 확인한다(반드시 매번 그 값을 확인해야 한다.)
 *     - 그런 다음 생성했던 모든 자원을 지운다.
 *     - 마지막으로 도움이 되리라 기대하면서 오류 메시지를 출력한다.
 * 이를 위해 이 시스템은 언제든지 오류가 발생하면 함수가 error: 부분으로 점프하여 모든 것을 정리하고 오류 코드를 반환시키도록 하는 규칙을 적용하였다.
 * 매크로를 사용하기 위해 check를 호출하여 반환 코드를 점검하고 오류 메시지를 출력한 다음, 정리하는 섹션으로 점프시킬 수 있다.
 * 또한 유용한 디버그 메시지를 출력하기 위하여 로그 함수를 엮을 수도 있다.
 * 
 * Debugging 시 반복적으로 컴파일 및 실행을 하기 때문에 이를 위한 셸 프로그램을 작성하여 디버깅 시간을 줄인다.
 *
 * C 전처리기 활용
 *   - C전처리기의 Point는 블록 생성 능력이다. 
 *      ex) check 매크로가 if 명령문을 이용하여 오류 점검 하는 방법(check 매크로는 if 명령문으로 치환된다.)
 *      if(!(rc == 0)) {                           ==    check(rc == 0, "There was an error.")       
 *          log_err("There was an error.");
 *          errno=0;                              
 *          goto error;
 *      }
 *   - C 전처리기는 재귀적인 템플릿 시스템이다. C 전처리기의 힘은 인수를 사용하는 코드의 전체 블록을 생성하는 능력에 있으며, 궁극적으로 편리한 코드 생성 도구가 되는데 기여한다.
 *   - 매크로 check로 if 명령문을 감싸서 이 부분은 단지 오류 점검일 뿐 프로그램의 주 흐름과는 큰 관계가 없음을 명확하게 알려줄 수 있다.
 *   - C 전처리기는 조건부로 코드의 일부를 컴파일 할 수 있기 때문에 이를 이용하여 개발자 버저이나 디버그 버전 코드만을 빌드 할 수 있다.    
 *
 * Usage:
 *  int main(int argc, char *arg[]){
 *      int rc // 함수 리턴코드
 *
 *      rc = doSomethingFunc();
 *      check(rc == -1, "Failed doSomethingFunc()."); //check(doSomethingFunc() == -1, "Failed doSomethingFunc().");
 *
 *      return 0;
 *
 *      error:
 *          return -1;
 *  } 
 */
#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

/* 모든 함수가 일관된 오류 코드를 반환하도록 한다. */
#define RC_NRM  0
#define RC_ERR -1
#define RC_NFD -2
#define RC_DUP -3

/* NDEBUG가 정의 되어 있으면 debug() 메시지 남기지 않는다. 정의하고 싶으면 맨 위에 #define 해서 정의한다.
 * M은 출력 format이고, ...는 format에 있는 서식문자를 채울 가변 인자들이 온다. ... 와, ##__VA_ARGS__ 세트
 */
//#define NDEBUG
#ifdef NDEBUG 
#define debug(M, ...) 
#else 
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__)
#endif

/* clean_errno 매크로는 안전하게 errno를 읽을 수 있도록 해준다.
 */
#define clean_errno() (errno == 0 ? "None" : strerror(errno)) 

/* log_err, log_warn, log_info 모두 debug처럼 동작하지만 컴파일될 수 없다.
 */
#define log_err(M, ...) fprintf(stderr,\
        "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__,\
        clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr,\
        "[WARN] (%s:%d: errno: %s) " M "\n",\
        __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__)

/* A가 NULL이면 오류 메시지 M을 (log_err에 사용되는 다른 가변 인수-__FILE__,__LINE__,clean_errno()-와 함께) 로그로 남긴 후 함수 내 error:로 점프하여 정리 작업을 수행한다.
 * "A가 참인지 점검하고 거짓인 경우 M이라고 출력한 다음 점프한다." if(!(A)){//NULL이면, 거짓이면 수행} if(A){//NULL이 아니면, 참이면 수행}
 *
 */
#define check(A, M, ...) if(!(A)) {\
   log_err(M, ##__VA_ARGS__); errno=0; goto error; }

/* 함수 내 어디에나 놓을 수 있지만 절대 실행되어서는 안 되는 매크로로, 만일 실행하는 일이 발생하면 오류 메시지를 출력한 다음 error:로 점프 한다.
 * 이 매크로는 if명령문이나 switch 명령문에서 사용되어 default: 등과 같이 절대 일어나면 안 될 만한 곳에 놓는다.
 */
#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__);\
    errno=0; goto error; }

/* 포인터를 점검하여 유효하지 않은 경우 "Out of memory."오류 메시지를 출력한다. */
#define check_mem(A) check((A), "Out of memory.")

/* 이 매크로는 오류 출력을 위해 log_err 대신 debug를 사용하기 때문에 NDEBUG를 정의해놓으면 점검도 하고 오류 발생 시 error:로 점프도 하지만 메시지는 출력하지 않는다. */
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__);\
    errno=0; goto error; }

#endif
 
