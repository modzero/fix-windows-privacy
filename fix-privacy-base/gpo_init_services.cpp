
/* !!! DO NOT EDIT !!! 
 * Auto-Generated source-code!
 * Edit generate-windsows-service-rules.py or service-rules.txt instead
 */
 
//#include "stdafx.h"
#include <stdio.h>

#include "windows.h"
#include "Strsafe.h"
#include "gpedit.h"

#include "gpo_init_services.h"
#include "m0gpo.h"


DWORD m0_init_services(m0_privsvc_t service[], DWORD maxsvc)
{
	DWORD count = 0;

	printf("[d] vorher\n");

	ZeroMemory(service, maxsvc * sizeof(m0_privsvc_t));
	printf("[d] nacher\n");

	//
	// dmwappushservice,WS_STARTUP_DELETE,WS_STATUS_STOP,,
	//

	/*
	[+] read 5 token
	[-] tok[0] = dmwappushservice
	[-] tok[1] = WS_STARTUP_DELETE
	[-] tok[2] = WS_STATUS_STOP
	[-] tok[3] = 
	[-] tok[4] = 
	*/
	StringCbCopy(service[count].service_name,    sizeof(service[0].service_name),   L"dmwappushservice");
	StringCbCopy(service[count].service_path,    sizeof(service[0].service_path),   L"");
	StringCbCopy(service[count].service_params,  sizeof(service[0].service_params), L"");
	service[count].service_startup = WS_STARTUP_DELETE;
	service[count].service_status  = WS_STATUS_STOP;
	count++;

	//
	// DiagTrack,WS_STARTUP_DELETE,WS_STATUS_STOP,,
	//

	/*
	[+] read 5 token
	[-] tok[0] = DiagTrack
	[-] tok[1] = WS_STARTUP_DELETE
	[-] tok[2] = WS_STATUS_STOP
	[-] tok[3] = 
	[-] tok[4] = 
	*/
	StringCbCopy(service[count].service_name,    sizeof(service[0].service_name),   L"DiagTrack");
	StringCbCopy(service[count].service_path,    sizeof(service[0].service_path),   L"");
	StringCbCopy(service[count].service_params,  sizeof(service[0].service_params), L"");
	service[count].service_startup = WS_STARTUP_DELETE;
	service[count].service_status  = WS_STATUS_STOP;
	count++;

	//
	// iphlpsvc,WS_STARTUP_DISABLED,WS_STATUS_STOP,,
	//

	/*
	[+] read 5 token
	[-] tok[0] = iphlpsvc
	[-] tok[1] = WS_STARTUP_DISABLED
	[-] tok[2] = WS_STATUS_STOP
	[-] tok[3] = 
	[-] tok[4] = 
	*/
	StringCbCopy(service[count].service_name,    sizeof(service[0].service_name),   L"iphlpsvc");
	StringCbCopy(service[count].service_path,    sizeof(service[0].service_path),   L"");
	StringCbCopy(service[count].service_params,  sizeof(service[0].service_params), L"");
	service[count].service_startup = WS_STARTUP_DISABLED;
	service[count].service_status  = WS_STATUS_STOP;
	count++;

	//
	// WinHttpAutoProxySvc,WS_STARTUP_DISABLED,WS_STATUS_STOP,,
	//

	/*
	[+] read 5 token
	[-] tok[0] = WinHttpAutoProxySvc
	[-] tok[1] = WS_STARTUP_DISABLED
	[-] tok[2] = WS_STATUS_STOP
	[-] tok[3] = 
	[-] tok[4] = 
	*/
	StringCbCopy(service[count].service_name,    sizeof(service[0].service_name),   L"WinHttpAutoProxySvc");
	StringCbCopy(service[count].service_path,    sizeof(service[0].service_path),   L"");
	StringCbCopy(service[count].service_params,  sizeof(service[0].service_params), L"");
	service[count].service_startup = WS_STARTUP_DISABLED;
	service[count].service_status  = WS_STATUS_STOP;
	count++;

	//
	// lfsvc,WS_STARTUP_DISABLED,WS_STATUS_STOP,,
	//

	/*
	[+] read 5 token
	[-] tok[0] = lfsvc
	[-] tok[1] = WS_STARTUP_DISABLED
	[-] tok[2] = WS_STATUS_STOP
	[-] tok[3] = 
	[-] tok[4] = 
	*/
	StringCbCopy(service[count].service_name,    sizeof(service[0].service_name),   L"lfsvc");
	StringCbCopy(service[count].service_path,    sizeof(service[0].service_path),   L"");
	StringCbCopy(service[count].service_params,  sizeof(service[0].service_params), L"");
	service[count].service_startup = WS_STARTUP_DISABLED;
	service[count].service_status  = WS_STATUS_STOP;
	count++;

	//
	// SshBroker,WS_STARTUP_DISABLED,WS_STATUS_STOP,,
	//

	/*
	[+] read 5 token
	[-] tok[0] = SshBroker
	[-] tok[1] = WS_STARTUP_DISABLED
	[-] tok[2] = WS_STATUS_STOP
	[-] tok[3] = 
	[-] tok[4] = 
	*/
	StringCbCopy(service[count].service_name,    sizeof(service[0].service_name),   L"SshBroker");
	StringCbCopy(service[count].service_path,    sizeof(service[0].service_path),   L"");
	StringCbCopy(service[count].service_params,  sizeof(service[0].service_params), L"");
	service[count].service_startup = WS_STARTUP_DISABLED;
	service[count].service_status  = WS_STATUS_STOP;
	count++;

	//
	// SshProxy,WS_STARTUP_DISABLED,WS_STATUS_STOP,,
	//

	/*
	[+] read 5 token
	[-] tok[0] = SshProxy
	[-] tok[1] = WS_STARTUP_DISABLED
	[-] tok[2] = WS_STATUS_STOP
	[-] tok[3] = 
	[-] tok[4] = 
	*/
	StringCbCopy(service[count].service_name,    sizeof(service[0].service_name),   L"SshProxy");
	StringCbCopy(service[count].service_path,    sizeof(service[0].service_path),   L"");
	StringCbCopy(service[count].service_params,  sizeof(service[0].service_params), L"");
	service[count].service_startup = WS_STARTUP_DISABLED;
	service[count].service_status  = WS_STATUS_STOP;
	count++;

	//
	// XblAuthManager,WS_STARTUP_DISABLED,WS_STATUS_STOP,,
	//

	/*
	[+] read 5 token
	[-] tok[0] = XblAuthManager
	[-] tok[1] = WS_STARTUP_DISABLED
	[-] tok[2] = WS_STATUS_STOP
	[-] tok[3] = 
	[-] tok[4] = 
	*/
	StringCbCopy(service[count].service_name,    sizeof(service[0].service_name),   L"XblAuthManager");
	StringCbCopy(service[count].service_path,    sizeof(service[0].service_path),   L"");
	StringCbCopy(service[count].service_params,  sizeof(service[0].service_params), L"");
	service[count].service_startup = WS_STARTUP_DISABLED;
	service[count].service_status  = WS_STATUS_STOP;
	count++;

	//
	// XblGameSave,WS_STARTUP_DISABLED,WS_STATUS_STOP,,
	//

	/*
	[+] read 5 token
	[-] tok[0] = XblGameSave
	[-] tok[1] = WS_STARTUP_DISABLED
	[-] tok[2] = WS_STATUS_STOP
	[-] tok[3] = 
	[-] tok[4] = 
	*/
	StringCbCopy(service[count].service_name,    sizeof(service[0].service_name),   L"XblGameSave");
	StringCbCopy(service[count].service_path,    sizeof(service[0].service_path),   L"");
	StringCbCopy(service[count].service_params,  sizeof(service[0].service_params), L"");
	service[count].service_startup = WS_STARTUP_DISABLED;
	service[count].service_status  = WS_STATUS_STOP;
	count++;

	//
	// XboxNetApiSvc,WS_STARTUP_DISABLED,WS_STATUS_STOP,,
	//

	/*
	[+] read 5 token
	[-] tok[0] = XboxNetApiSvc
	[-] tok[1] = WS_STARTUP_DISABLED
	[-] tok[2] = WS_STATUS_STOP
	[-] tok[3] = 
	[-] tok[4] = 
	*/
	StringCbCopy(service[count].service_name,    sizeof(service[0].service_name),   L"XboxNetApiSvc");
	StringCbCopy(service[count].service_path,    sizeof(service[0].service_path),   L"");
	StringCbCopy(service[count].service_params,  sizeof(service[0].service_params), L"");
	service[count].service_startup = WS_STARTUP_DISABLED;
	service[count].service_status  = WS_STATUS_STOP;
	count++;
	

	return count;
}	

	
