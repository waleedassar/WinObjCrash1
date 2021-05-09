#pragma once




#define ulong unsigned long
#define ulonglong unsigned long long
#define longlong long long
#define ULONG unsigned long
#define ULONGLONG unsigned long long
#define ushort unsigned short
#define USHORT unsigned short
#define uchar unsigned char

#define OBJ_CASE_INSENSITIVE 0x40

typedef struct _UNICODE_STRING
{
	unsigned short Length;
	unsigned short MaxLength;
	unsigned long Pad;
	wchar_t* Buffer;
}UNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES {
  ULONGLONG           Length;
  HANDLE          RootDirectory;
  _UNICODE_STRING* ObjectName;
  ULONGLONG           Attributes;
  PVOID           SecurityDescriptor;
  PVOID           SecurityQualityOfService;
} OBJECT_ATTRIBUTES;



extern "C"
{
	int  NtCreateSymbolicLinkObject(HANDLE *pHandle, ulong  DesiredAccess, _OBJECT_ATTRIBUTES *pObjAttr, _UNICODE_STRING *pUniLinkTarget);
	int  NtOpenSymbolicLinkObject(HANDLE *pHandle,		ACCESS_MASK DesiredAccess,		_OBJECT_ATTRIBUTES *pObjAttr);
	int  NtQuerySymbolicLinkObject(HANDLE LinkHandle,_UNICODE_STRING* pLinkTarget,unsigned long* pReturnedLength);
}