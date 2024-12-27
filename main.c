#include <ntddk.h>
#include "inj.h"

DRIVER_INITIALIZE DriverEntry;
#pragma alloc_text(INIT, DriverEntry)

#define MODULE_MAX_LENGTH 512
#define IOCTL_INJECT_MODULE \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct _INJECTION_DATA
{
	ULONG64	ProcessId;
	wchar_t	ModulePath[MODULE_MAX_LENGTH];
} INJECTION_DATA, *PINJECTION_DATA;

static UNICODE_STRING DeviceName		= RTL_CONSTANT_STRING(L"\\Device\\KeInject");
static UNICODE_STRING DeviceSymlink		= RTL_CONSTANT_STRING(L"\\??\\KeInject");
static BOOLEAN DoCleanup				= FALSE;

VOID DriverUnload(
	_In_ PDRIVER_OBJECT DriverObject
)
{
	if (DoCleanup)
	{
		IoDeleteSymbolicLink(&DeviceSymlink);
		IoDeleteDevice(DriverObject->DeviceObject);

		DoCleanup = FALSE;
	}
}

NTSTATUS DeviceDefaultDispatch(
	_In_ PDEVICE_OBJECT DeviceObject,
	_In_ PIRP Irp
)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Irp);

	return STATUS_SUCCESS;
}

NTSTATUS DeviceControlDispatch(
	_In_ PDEVICE_OBJECT DeviceObject,
	_In_ PIRP Irp
)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	PIO_STACK_LOCATION StackLocation = IoGetCurrentIrpStackLocation(Irp);
	NTSTATUS Stat