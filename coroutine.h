#ifndef __COROUTINE__H__
#define __COROUTINE__H__

#define DEFCODE(__name__,__expression__,...) if(0){__name__:if(__expression__){__VA_ARGS__}};
#define CONTROL(__CONTROL_code_name__) goto __CONTROL_code_name__;

#endif  //!__COROUTINE__H__