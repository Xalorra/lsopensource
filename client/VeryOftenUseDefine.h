#pragma once


//HARDCODE: 이 헤더에는 정말 자주쓰이는, 특히 앞으로 "변하지 않을" define 만을 집어 넣는다.
//			이 헤더를 수정한다는 것은 전체 컴파일을 감수해야한다는것 명심

#define COMPARE(x,min,max) (((x)>=(min))&&((x)<(max)))
#define SAFEDELETE(x)		if(x != NULL) { delete x; x = NULL; }
#define SAFEDELETEARRAY(x)	if(x != NULL) { delete [] x; x = NULL; }
#define SAFERELEASE(x)		if(x != NULL) { x->Release(); x = NULL; }

template <typename type>					// RADtoDEG
type  RADtoDEG (type val) {return (type) (val * 57.2957795132);}
template <typename type>					// DEGtoRAD
type  DEGtoRAD (type val) {return (type) (val * 0.0174532925199);}

