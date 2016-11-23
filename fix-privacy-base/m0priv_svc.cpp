/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* Copyright (c) 2016, Thorsten Schroeder, modzero GmbH
*
* All rights reserved.
*
* This file is part of fix-windows-privacy.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
*  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*  The views and conclusions contained in the software and documentation are those
*  of the authors and should not be interpreted as representing official policies,
*  either expressed or implied, of the fix-windows-privacy Project, modzero or
*  Thorsten Schroeder.
*
* NON-MILITARY-USAGE CLAUSE
* Redistribution and use in source and binary form for military use and
* military research is not permitted. Infringement of these clauses may
* result in publishing the source code of the utilizing applications and
* libraries to the public. As this software is developed, tested and
* reviewed by *international* volunteers, this clause shall not be refused
* due to the matter of *national* security concerns.
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//#include "stdafx.h"
#include "windows.h"
#include "InitGuid.h"
#include "gpedit.h"
#include "Strsafe.h"

#include "m0gpo.h"

static SC_HANDLE schSCManager;
static SC_HANDLE schService;

extern DWORD status_count;

fixpriv_status_t m0_svc_check(m0_privsvc_t privsvc)
{
	fixpriv_status_t ret = FIXPRIV_RED;

	DWORD svc_startuptype = 0xffffffff;

	svc_startuptype = DoQuerySvc(privsvc.service_name);

	if (privsvc.service_startup == svc_startuptype)
		ret = FIXPRIV_GREEN;

	if (privsvc.service_startup == WS_STARTUP_DISABLED && svc_startuptype == WS_STARTUP_DELETE)
		ret = FIXPRIV_GREEN;
	
	if (privsvc.service_startup == WS_STARTUP_DELETE && svc_startuptype == WS_STARTUP_DISABLED)
		ret = FIXPRIV_YELLOW;

	if (svc_startuptype == -2) //permission denied
		ret = (fixpriv_status_t )-2;

	return ret;
	
}


DWORD m0_svc_read(m0_privsvc_t *privsvc)
{
	DWORD ret = READSVC_SUCCESS;
	privsvc->service_status  = WS_STATUS_UNCHANGED;
	privsvc->service_startup = (ws_startup_t) DoQuerySvc(privsvc->service_name);
	if (privsvc->service_startup == -2)
		ret = READSVC_FAIL;

	return ret;
}

HRESULT m0_svc_modify(m0_privsvc_t privsvc)
{
	HRESULT hr = S_OK;

	switch (privsvc.service_status) {
	case WS_STATUS_STOP:
		DoStopSvc(privsvc.service_name);
		break;
	case WS_STATUS_START:
		DoStartSvc(privsvc.service_name);
		break;
	case WS_STATUS_UNCHANGED:
	default:
		break;
	}

	switch (privsvc.service_startup) {
	case WS_STARTUP_AUTOMATIC_DELAYED:
		printf("[E] WS_STARTUP_AUTOMATIC_DELAYED not implemented\n");
		break;
	case WS_STARTUP_AUTOMATIC:
		printf("[E] WS_STARTUP_AUTOMATIC not implemented\n");
		break;
	case WS_STARTUP_MANUAL:
		DoEnableSvc(privsvc.service_name);
		break;
	case WS_STARTUP_DISABLED:
		DoDisableSvc(privsvc.service_name);
		break;
	case WS_STARTUP_DELETE:
		DoDeleteSvc(privsvc.service_name);
		break;
	case WS_STARTUP_UNCHANGED:
	default:
		break;
	}

	return hr;
}





