#pragma once
#include <ntddk.h>

NTSTATUS ApcQueueExecution(
	_In_ PEPROCESS Process,
	_In_