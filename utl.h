#pragma once
#include <ntddk.h>

PVOID UtlGetModuleExport(
	_In_ PVOID Module,
	_In_ PCHAR Ex