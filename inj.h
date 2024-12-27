#pragma once
#include <ntddk.h>

NTSTATUS InjPerformInjection(
	_In_ HANDLE ProcessId,
	_In_ P