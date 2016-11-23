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

#pragma once

#define WINDOWS_SERVICE	0x23234223
#include <Windows.h>

#include <stdint.h>

typedef union _regval {
	DWORD	dwVal;
	WORD	dVal;
	BOOL	bVal;
	BYTE	cVal;
	BYTE	szVal[64];
	WCHAR	wcsVal[64];
} regval_t;

typedef enum _regmode {
	POL_NOTCONFIGURED,
	POL_ENABLED,
	POL_DISABLED,
	POL_DELETE
} m0_polregmode_t;

typedef enum _value_type {
	POL_DWORD,
	POL_WSTRING,
	POL_ASTRING,
	POL_BOOL
} value_data_type_t;

typedef enum _wsstartup_type {
	WS_STARTUP_UNCHANGED,
	WS_STARTUP_AUTOMATIC_DELAYED,
	WS_STARTUP_AUTOMATIC,
	WS_STARTUP_MANUAL,
	WS_STARTUP_DISABLED,
	WS_STARTUP_DELETE
} ws_startup_t;

typedef enum _wsstatus_type {
	WS_STATUS_UNCHANGED,
	WS_STATUS_START,
	WS_STATUS_STOP,
	WS_STATUS_PAUSE,
	WS_STATUS_RESUME
} ws_status_t;

typedef enum _key_type {
	WS_KEY_HKCU,
	WS_KEY_HKLM,
	WS_KEY_GPOU,
	WS_KEY_GPOM
} ws_key_t;

typedef enum _fixpriv_status {
	FIXPRIV_NEUTRAL,
	FIXPRIV_GREEN,
	FIXPRIV_YELLOW,
	FIXPRIV_RED
} fixpriv_status_t;

enum {
	READREG_SUCCESS,
	READREG_NOTFOUND,
	READREG_DISABLED,
	READREG_FAIL
};

enum {
	READSVC_SUCCESS,
	READSVC_NOTFOUND,
	READSVC_DISABLED,
	READSVC_FAIL
};


typedef struct _m0_priv_policy {
	WCHAR pol_key[256];
	WCHAR pol_value_name[64];
	WCHAR pol_value_data[256];
	value_data_type_t pol_datatype;
	m0_polregmode_t pol_mode;
	ws_key_t section_key;
} m0_privpol_t;

typedef struct _m0_privsvc {
	WCHAR service_name[64];
	WCHAR service_path[256];
	WCHAR service_params[256];
	ws_startup_t	service_startup;
	ws_status_t		service_status;
} m0_privsvc_t;


HRESULT modify_policy(m0_privpol_t privpol);
HRESULT modify_regkey_user(m0_privpol_t privpol);
fixpriv_status_t check_regkey(m0_privpol_t privpol);
DWORD read_regkey(m0_privpol_t *privpol);

HRESULT modify_gpo_regkey_user(m0_privpol_t privpol);
HRESULT modify_gpo_regkey_machine(m0_privpol_t privpol);

HRESULT				m0_svc_modify(m0_privsvc_t privsvc);
fixpriv_status_t	m0_svc_check(m0_privsvc_t privsvc);
DWORD m0_svc_read(m0_privsvc_t *privsvc);


void m0priv_errormsg(m0_privpol_t privpol, WCHAR *function, LSTATUS rStatus, BOOL ignore_filenotfound);



DWORD __stdcall DoQuerySvc(TCHAR *svc_name);
VOID __stdcall DoUpdateSvcDesc(TCHAR *svc_name);
VOID __stdcall DoDisableSvc(TCHAR *svc_name);
VOID __stdcall DoEnableSvc(TCHAR *svc_name);
VOID __stdcall DoDeleteSvc(TCHAR *svc_name);


VOID __stdcall DoStartSvc(TCHAR *svc_name);
VOID __stdcall DoUpdateSvcDacl(TCHAR *svc_name);
VOID __stdcall DoStopSvc(TCHAR *svc_name);


HRESULT m0_special_modify(void);
HRESULT m0_special_launchprogram(LPWSTR);

void elevate(void);
void elevate_withargs(const char *as);

void trace_log(wchar_t* buf);
