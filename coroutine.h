#ifndef __COROUTINE__H__
#define __COROUTINE__H__

#define DEFCODE(__name__,__expression__,codes...) if(0){__name__:if(__expression__){codes}};
#define CONTROL(codes...) __CONTROL__: codes;
#define EXECUTE(codes) goto codes;

#endif  //!__COROUTINE__H__