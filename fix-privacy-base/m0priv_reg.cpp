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
#include "Strsafe.h"
#include "gpedit.h"

#include "m0gpo.h"

extern DWORD status_count;

fixpriv_status_t check_regkey(m0_privpol_t privpol) 
{
	fixpriv_status_t ret = FIXPRIV_RED;
	DWORD dwType = 0;
	DWORD cbType = sizeof(DWORD);
	DWORD dwResult = 0;
	HRESULT rStatus = S_FALSE;
	WCHAR tmpbuf[64] = { 0 };
	DWORD tmpdw = 0;

	HKEY root_key = HKEY_CURRENT_USER, setting_key = 0;

	switch (privpol.section_key) {
	case WS_KEY_HKCU:
		root_key = HKEY_CURRENT_USER;
		break;
	case WS_KEY_HKLM:
		root_key = HKEY_LOCAL_MACHINE;
		break;
	case WS_KEY_GPOM:
		root_key = HKEY_LOCAL_MACHINE;
		break;
	case WS_KEY_GPOU:
		root_key = HKEY_CURRENT_USER;
		break;
	default:
		printf("[u] privpol.section_key\n");
		return FIXPRIV_NEUTRAL;
	}

	// modes auch checken: POL_ENABLED, POL_DELETE, POL_NOTCONFIGURED

	rStatus = RegOpenKeyEx(root_key, privpol.pol_key, 0, KEY_READ, &setting_key);

	if (rStatus != ERROR_SUCCESS)
	{
		if (privpol.pol_mode != POL_ENABLED)
			ret = FIXPRIV_YELLOW;
		else
			ret = FIXPRIV_GREEN;

		if (rStatus == ERROR_FILE_NOT_FOUND && (privpol.pol_mode == POL_DELETE || privpol.pol_mode == POL_DISABLED))
			ret = FIXPRIV_GREEN;

		return ret;
	}

	switch (privpol.pol_datatype) {

	case	POL_DWORD:
		dwType = REG_DWORD;
		cbType = sizeof(DWORD);

		rStatus = RegGetValue(
				root_key, 
				privpol.pol_key, 
				privpol.pol_value_name, 
				RRF_RT_ANY, 
				&dwType, 
				(&dwResult), 
				&cbType);

		tmpdw = wcstol(privpol.pol_value_data, '\0', 10);

		if (rStatus != ERROR_SUCCESS) {
			m0priv_errormsg(privpol, L"RegGetValue", rStatus, TRUE);
			ret = FIXPRIV_YELLOW;

			if (rStatus == ERROR_FILE_NOT_FOUND && (privpol.pol_mode == POL_DELETE || privpol.pol_mode == POL_DISABLED))
				ret = FIXPRIV_GREEN;

			break;
		}

		if (dwResult == tmpdw)
			ret = FIXPRIV_GREEN;
		else 
			ret = FIXPRIV_RED;

		break;
	case POL_WSTRING:

		dwType = REG_SZ;
		cbType = sizeof(tmpbuf);

		rStatus = RegGetValue(root_key, privpol.pol_key, privpol.pol_value_name, RRF_RT_ANY, &dwType, (&tmpbuf), &cbType);
		
		if (rStatus != ERROR_SUCCESS) {
			m0priv_errormsg(privpol, L"RegGetValue", rStatus, TRUE);
			ret = FIXPRIV_YELLOW;

			if (rStatus == ERROR_FILE_NOT_FOUND && (privpol.pol_mode == POL_DELETE || privpol.pol_mode == POL_DISABLED))
				ret = FIXPRIV_GREEN;

			break;
		}

		if (!lstrcmpW(privpol.pol_value_data, tmpbuf))
			ret = FIXPRIV_GREEN;
		else
			ret = FIXPRIV_RED;

		break;
	default:
		ret = FIXPRIV_NEUTRAL;
		break;

	}
	return ret;
}

HRESULT modify_regkey_user(m0_privpol_t privpol)
{
	HRESULT hr = S_OK;
	DWORD tmp = 0;

	//printf("[%04d] Processing %s\\%S\\%S = %S\n", 
	//	status_count++, (privpol.section_key == WS_KEY_HKCU ? "HKCU" : "HKLM"),
	//	privpol.pol_key, privpol.pol_value_name, privpol.pol_value_data);

	HKEY hSectionKey = 0;
	HKEY hSettingKey = 0;
	LSTATUS rStatus = 0;
	hr = 0;

	WCHAR full_path[sizeof(m0_privpol_t) / sizeof(WCHAR)];
	WCHAR full_path_del[sizeof(m0_privpol_t) / sizeof(WCHAR)];
	WCHAR value_name_del[sizeof(m0_privpol_t) / sizeof(WCHAR)];

	switch (privpol.section_key) {
	case WS_KEY_HKCU:
		hSectionKey = HKEY_CURRENT_USER;
		break;
	case WS_KEY_HKLM:
		hSectionKey = HKEY_LOCAL_MACHINE;
		break;
	default:
		printf("[u] privpol.section_key\n");
		break;
	}

	ZeroMemory(full_path, sizeof(full_path));
	ZeroMemory(full_path_del, sizeof(full_path_del));
	ZeroMemory(value_name_del, sizeof(full_path_del));

	StringCbPrintf(full_path, sizeof(full_path), L"%s\\%s", privpol.pol_key, privpol.pol_value_name);
	StringCbPrintf(full_path_del, sizeof(full_path_del), L"%s\\**del.%s", privpol.pol_key, privpol.pol_value_name);
	StringCbPrintf(value_name_del, sizeof(value_name_del), L"**del.%s", privpol.pol_value_name);

	switch (privpol.pol_mode)
	{
	case POL_NOTCONFIGURED:
	case POL_DELETE:
	case POL_DISABLED:

		rStatus = RegDeleteValue(hSectionKey,
			full_path
		);

		if (rStatus != ERROR_SUCCESS)
			m0priv_errormsg(privpol, L"RegDeleteValue", rStatus, TRUE);


		rStatus = RegDeleteValue(hSectionKey,
			full_path_del
		);

		if (rStatus != ERROR_SUCCESS)
			m0priv_errormsg(privpol, L"RegDeleteValue", rStatus, TRUE);

		break;

	case POL_ENABLED:
	{
		size_t len = 0;

		rStatus = RegOpenKeyEx(hSectionKey, privpol.pol_key, 0, KEY_WRITE | KEY_WOW64_64KEY, &hSettingKey);

		if (rStatus != ERROR_SUCCESS)
		{
			m0priv_errormsg(privpol, L"RegOpenKeyEx", rStatus, TRUE);

			rStatus = RegCreateKeyEx(
				hSectionKey,
				privpol.pol_key,
				0,
				NULL,
				REG_OPTION_NON_VOLATILE,
				KEY_WRITE | KEY_WOW64_64KEY,
				NULL,
				&hSettingKey,
				NULL);

			if (rStatus != ERROR_SUCCESS)
				m0priv_errormsg(privpol, L"RegCreateKeyEx", rStatus, TRUE);
		}

		switch (privpol.pol_datatype) {
			
		case	POL_DWORD:

			tmp = wcstol(privpol.pol_value_data, '\0', 10);
			rStatus = RegSetValueEx(hSettingKey, privpol.pol_value_name,
				NULL, REG_DWORD, (BYTE *)(&tmp), 
				sizeof(DWORD));

			if (rStatus != ERROR_SUCCESS)
				m0priv_errormsg(privpol, L"RegSetValueEx", rStatus, FALSE);

			break;

		case POL_WSTRING:

			StringCbLength(privpol.pol_value_data/*.wcsVal*/, sizeof(privpol.pol_value_data/*.wcsVal*/), &len);

			len += sizeof(WCHAR); // plus null bytes

			rStatus = RegSetValueEx(hSettingKey, privpol.pol_value_name,
				NULL, REG_SZ, (BYTE *)privpol.pol_value_data/*.wcsVal*/, (DWORD)len);

			if (rStatus != ERROR_SUCCESS)
				m0priv_errormsg(privpol, L"RegSetValueEx", rStatus, FALSE);

			break;

		default:
			printf("[u] privpol.pol_mode\n");
			break;
		}

		rStatus = RegCloseKey(hSettingKey);

		if (rStatus != ERROR_SUCCESS)
			m0priv_errormsg(privpol, L"RegSetValueEx", rStatus, FALSE);

		break;
		} // last case
	} // switch

	rStatus = RegCloseKey(hSectionKey);
	return hr;
}

