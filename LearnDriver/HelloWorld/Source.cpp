#include <fltKernel.h>
extern "C" {
	void HelloWorldUnload(_In_ struct _DRIVER_OBJECT *DriverObject) {
		UNREFERENCED_PARAMETER(DriverObject);
	}

	NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
		UNREFERENCED_PARAMETER(RegistryPath);
		DriverObject->DriverUnload = HelloWorldUnload;
		DbgPrint("This is my first Driver");
		return STATUS_SUCCESS;
	}
}