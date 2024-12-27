#pragma once
#include <ntddk.h>

PVOID UtlGetModuleExport(
	_In_ PVOID Module,
	_In_ PCHAR ExportName
);

PVOID UtlGetModuleBase(
	_In_ PEPROCESS Process,
	_In_ PUNI