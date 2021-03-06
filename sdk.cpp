#include "sdk.hpp"

#include "string.h"

InterfaceReg* InterfaceReg::s_pInterfaceRegs = nullptr;

static void* CreateInterfaceInternal(const char* pName, int* pReturnCode) {
	InterfaceReg* pCur;
	for(pCur = InterfaceReg::s_pInterfaceRegs; pCur; pCur = pCur->m_pNext) {
		if(!strcmp(pCur->m_pName, pName)) {
			if(pReturnCode) *pReturnCode = 0;
			return pCur->m_CreateFn();
		}
	}
	if(pReturnCode) *pReturnCode = 1;
	return nullptr;
}

// exported function expected to be located inside a plugin
// it allows for getting the required interface by it's version
extern "C" void* CreateInterface(const char* pName, int* pReturnCode) {
	return CreateInterfaceInternal(pName, pReturnCode);
}

