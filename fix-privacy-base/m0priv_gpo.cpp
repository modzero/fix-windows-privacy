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


#include "windows.h"
#include "Strsafe.h"
#include "gpedit.h"

#include "m0gpo.h"

extern DWORD status_count;

HRESULT modify_gpo_regkey_machine(m0_privpol_t privpol)
{
	HRESULT hr = S_OK;
	size_t len = 0;
	IGroupPolicyObject* pLGPO = NULL;
	HKEY machine_key, setting_key = 0;
	LSTATUS rStatus;
	DWORD dwType = REG_DWORD;
	DWORD cbType = sizeof(DWORD);
	BOOL bCreate = FALSE;
	WCHAR errmsg[256];

	GUID ext_guid = REGISTRY_EXTENSION_GUID;

	// {6CD8ACD8-88FA-4726-9BBB-FDBAC39F9FEE}
	GUID snap_guid =
	{ 0x6cd8acd8, 0x88fa, 0x4726,{ 0x9b, 0xbb, 0xfd, 0xba, 0xc3, 0x9f, 0x9f, 0xee } };

	ZeroMemory(errmsg, sizeof(errmsg));

	// Create an instance of the IGroupPolicyObject class
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED); // COINIT_APARTMENTTHREADED
	if (hr != S_OK) { 
		if(hr != 1) // OK, when called from managed code/thread
			m0priv_errormsg(privpol, L"CoInitializeEx", hr, FALSE);
	}


	hr = CoCreateInstance(CLSID_GroupPolicyObject, NULL,
		CLSCTX_INPROC_SERVER, IID_IGroupPolicyObject,
		(LPVOID*)&pLGPO);

	if (SUCCEEDED(hr))
	{
		DWORD tmp = 0;
		BOOL op_add = TRUE;

		WCHAR full_path[sizeof(m0_privpol_t) / sizeof(WCHAR)];
		WCHAR full_path_del[sizeof(m0_privpol_t) / sizeof(WCHAR)];
		WCHAR value_name_del[sizeof(m0_privpol_t) / sizeof(WCHAR)];

		ZeroMemory(full_path, sizeof(full_path));
		ZeroMemory(full_path_del, sizeof(full_path_del));
		ZeroMemory(value_name_del, sizeof(full_path_del));

		StringCbPrintf(full_path, sizeof(full_path), L"%s\\%s", privpol.pol_key, privpol.pol_value_name);
		StringCbPrintf(full_path_del, sizeof(full_path_del), L"%s\\**del.%s", privpol.pol_key, privpol.pol_value_name);
		StringCbPrintf(value_name_del, sizeof(value_name_del), L"**del.%s", privpol.pol_value_name);


		// We need the machine LGPO 
		hr = pLGPO->OpenLocalMachineGPO(GPO_OPEN_LOAD_REGISTRY);
		if (hr != S_OK) {
			m0priv_errormsg(privpol, L"OpenLocalMachineGPO", hr, FALSE);
		}

		hr = pLGPO->GetRegistryKey(GPO_SECTION_MACHINE, &machine_key);
		if (hr != S_OK) {
			m0priv_errormsg(privpol, L"GetRegistryKey", hr, FALSE);
		}

		switch (privpol.pol_mode)
		{
		case POL_NOTCONFIGURED:
		
			op_add = FALSE;

			//
			// We do not want to configure the GPO, but we don’t want to
			// affect other GPOs on the same key,
			// so just delete values associated with this
			// particular GPO setting.
			//

			rStatus = RegDeleteValue(machine_key, full_path);

			if (rStatus != ERROR_SUCCESS)
				m0priv_errormsg(privpol, L"RegDeleteValue", rStatus, FALSE);

			rStatus = RegDeleteValue(machine_key, full_path_del);

			if (rStatus != ERROR_SUCCESS)
				m0priv_errormsg(privpol, L"RegDeleteValue", rStatus, FALSE);

			break;

		case POL_ENABLED:

			// To enable the policy, the <value_name> value must
			// exist and the **del.<value_name> value must not.
			//
			// value_data:
			//
			// Check to see if the key for this policy exists. 
			// If if it does, retrieve a handle
			// If not, create it.

			rStatus = RegOpenKeyEx(machine_key, privpol.pol_key, 0, KEY_WRITE | KEY_WOW64_64KEY, &setting_key);

			if (rStatus != ERROR_SUCCESS)
			{

				m0priv_errormsg(privpol, L"RegOpenKeyEx", rStatus, TRUE);

				rStatus = RegCreateKeyEx(machine_key, privpol.pol_key,
					0, NULL, 0, KEY_SET_VALUE | KEY_QUERY_VALUE, NULL, &setting_key, NULL);

				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegCreateKeyEx", rStatus, FALSE);

			}

			switch (privpol.pol_datatype) {

			case	POL_DWORD:

				tmp = wcstol(privpol.pol_value_data, '\0', 10);
				rStatus = RegSetKeyValue(setting_key, NULL, privpol.pol_value_name, REG_DWORD, (BYTE *)(&tmp), sizeof(DWORD));

				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegSetKeyValue", rStatus, FALSE);

				break;

			case POL_WSTRING:

				StringCbLength(privpol.pol_value_data, sizeof(privpol.pol_value_data), &len);
				len += sizeof(WCHAR); // plus null bytes

				rStatus = RegSetKeyValue(setting_key, NULL, privpol.pol_value_name, REG_SZ, (BYTE *)privpol.pol_value_data, (DWORD)len);

				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegSetKeyValue", rStatus, FALSE);

				break;

			default:
				break;
			}

			// del delkey

			// Remove the not configured value indicator from the hive.
			// It may not exist, so the RegDeleteValue may return
			// and error, this can be ignored.
			//

			rStatus = RegDeleteValue(machine_key, full_path_del);

			if (rStatus != ERROR_SUCCESS)
				m0priv_errormsg(privpol, L"RegDeleteValue", rStatus, TRUE);

			rStatus = RegCloseKey(setting_key);

			if (rStatus != ERROR_SUCCESS)
				m0priv_errormsg(privpol, L"RegCloseKey", rStatus, FALSE);

			break;

		case POL_DISABLED:
		case POL_DELETE:

			//
			// Disable the policy.
			// must remove the <name> value and add the
			//  **del.<name> value.
			//
			// Same stesp as before, check to see if the key for this
			// policy exists,
			// if not, create it.
			//

			rStatus = RegOpenKeyEx(machine_key, privpol.pol_key, 0, KEY_WRITE | KEY_WOW64_64KEY, &setting_key);

			if (rStatus != ERROR_SUCCESS)
			{


				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegOpenKeyEx", rStatus, TRUE);

				rStatus = RegCreateKeyEx(machine_key, privpol.pol_key, 0, NULL, 0, KEY_SET_VALUE | KEY_QUERY_VALUE, NULL, &setting_key, NULL);

				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegCreateKeyEx", rStatus, FALSE);

				bCreate = TRUE;
			}


			//
			// If we did not create the key, then our value
			//  *may* exist.
			// try to read it.  If we succeed, write that value back
			//  to **del.<name>
			// if not, then set **del.<name> to 0
			//

			switch (privpol.pol_datatype) {

			case	POL_DWORD:

				dwType = REG_DWORD;
				cbType = sizeof(DWORD);

				rStatus = RegGetValue(machine_key, privpol.pol_key, privpol.pol_value_name, RRF_RT_ANY, &dwType, (BYTE *)(&tmp), &cbType);
				_itow_s(tmp, privpol.pol_value_data, sizeof(privpol.pol_value_data)/sizeof(WCHAR), 10);

				if (rStatus != ERROR_SUCCESS) {
					m0priv_errormsg(privpol, L"RegGetValue", rStatus, TRUE);
					tmp = 0;
					_itow_s(tmp, privpol.pol_value_data, sizeof(privpol.pol_value_data) / sizeof(WCHAR), 10);
				}
				else {
					rStatus = RegDeleteValue(setting_key, privpol.pol_value_name);

					if (rStatus != ERROR_SUCCESS)
						m0priv_errormsg(privpol, L"RegDeleteValue", rStatus, TRUE);

				}

				if (bCreate) {}
					tmp = 0;

				rStatus = RegSetValueEx(setting_key, value_name_del, NULL, REG_DWORD, (BYTE *)(&tmp), sizeof(DWORD));

				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegSetValueEx", rStatus, FALSE);

				break;

			case POL_WSTRING:

				dwType = REG_SZ;
				cbType = sizeof(privpol.pol_value_data);

				ZeroMemory(privpol.pol_value_data, sizeof(privpol.pol_value_data));

				rStatus = RegGetValue(machine_key, privpol.pol_key, privpol.pol_value_name, RRF_RT_ANY, &dwType, (BYTE *)(&privpol.pol_value_data), &cbType);

				if (rStatus != ERROR_SUCCESS) {
					m0priv_errormsg(privpol, L"RegGetValue", rStatus, TRUE);
					privpol.pol_value_data[0] = 0;
				}
				else {
					rStatus = RegDeleteValue(setting_key, privpol.pol_value_name);

					if (rStatus != ERROR_SUCCESS)
						m0priv_errormsg(privpol, L"RegDeleteValue", rStatus, TRUE);
				}

				if (bCreate) {
					ZeroMemory(privpol.pol_value_data, sizeof(privpol.pol_value_data));
					cbType = sizeof(WCHAR);
				}

				rStatus = RegSetValueEx(setting_key, value_name_del, NULL, REG_SZ, (BYTE *)(&privpol.pol_value_data), cbType);

				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegSetValueEx", rStatus, FALSE);

				break;

			default:
				break;
			}

			rStatus = RegCloseKey(setting_key);

			if (rStatus != ERROR_SUCCESS)
				m0priv_errormsg(privpol, L"RegCloseKey", rStatus, FALSE);

			break;

		default:
			break;
		}

		// Apply policy and free resources
		rStatus = RegCloseKey(machine_key);

		if (rStatus != ERROR_SUCCESS)
			m0priv_errormsg(privpol, L"RegCloseKey", rStatus, FALSE);

		DWORD ecnt = 0;

		do {
			hr = pLGPO->Save(TRUE, op_add, &ext_guid, &snap_guid);
			if( hr != S_OK) Sleep(500);
		} while ((hr != S_OK) && (ecnt < 6));

		if (hr != S_OK) {
			m0priv_errormsg(privpol, L"pLGPO->Save", hr, FALSE);
		}

		hr = pLGPO->Release();
		if (hr != S_OK) {
			m0priv_errormsg(privpol, L"pLGPO->Release", hr, FALSE);
		}
	}
	else {
		m0priv_errormsg(privpol, L"CoCreateInstance", hr, FALSE);
	}

	CoUninitialize();
	return hr;

}


HRESULT modify_gpo_regkey_user(m0_privpol_t privpol)
{
	HRESULT hr = S_OK;
	size_t len = 0;
	IGroupPolicyObject* pLGPO = NULL;
	HKEY machine_key, setting_key = 0;
	LSTATUS rStatus;
	DWORD dwType = REG_DWORD;
	DWORD cbType = sizeof(DWORD);
	BOOL bCreate = FALSE;
	WCHAR errmsg[256];
	DWORD tmp = 0;

	GUID ext_guid = REGISTRY_EXTENSION_GUID;

	// {6CD8ACD8-88FA-4726-9BBB-FDBAC39F9FEE}
	GUID snap_guid =
	{ 0x6cd8acd8, 0x88fa, 0x4726,{ 0x9b, 0xbb, 0xfd, 0xba, 0xc3, 0x9f, 0x9f, 0xee } };

	ZeroMemory(errmsg, sizeof(errmsg));

	// Create an instance of the IGroupPolicyObject class
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	hr = CoCreateInstance(CLSID_GroupPolicyObject, NULL,
		CLSCTX_INPROC_SERVER, IID_IGroupPolicyObject,
		(LPVOID*)&pLGPO);

	if (SUCCEEDED(hr))
	{
		BOOL op_add = TRUE;

		WCHAR full_path[sizeof(m0_privpol_t) / sizeof(WCHAR)];
		WCHAR full_path_del[sizeof(m0_privpol_t) / sizeof(WCHAR)];
		WCHAR value_name_del[sizeof(m0_privpol_t) / sizeof(WCHAR)];

		ZeroMemory(full_path, sizeof(full_path));
		ZeroMemory(full_path_del, sizeof(full_path_del));
		ZeroMemory(value_name_del, sizeof(full_path_del));

		StringCbPrintf(full_path, sizeof(full_path), L"%s\\%s", privpol.pol_key, privpol.pol_value_name);
		StringCbPrintf(full_path_del, sizeof(full_path_del), L"%s\\**del.%s", privpol.pol_key, privpol.pol_value_name);
		StringCbPrintf(value_name_del, sizeof(value_name_del), L"**del.%s", privpol.pol_value_name);

		// We need the machine LGPO 
		pLGPO->OpenLocalMachineGPO(GPO_OPEN_LOAD_REGISTRY);
		pLGPO->GetRegistryKey(GPO_SECTION_USER, &machine_key);

		switch (privpol.pol_mode)
		{
		case POL_NOTCONFIGURED:
		
			op_add = FALSE;

			//
			// We do not want to configure the GPO, but we don’t want to
			// affect other GPOs on the same key,
			// so just delete values associated with this
			// particular GPO setting.
			//

			rStatus = RegDeleteValue(machine_key, full_path);

			if (rStatus != ERROR_SUCCESS)
				m0priv_errormsg(privpol, L"RegDeleteValue", rStatus, TRUE);


			rStatus = RegDeleteValue(machine_key, full_path_del);
			if (rStatus != ERROR_SUCCESS)
				m0priv_errormsg(privpol, L"RegDeleteValue", rStatus, TRUE);

			break;

		case POL_ENABLED:

			// To enable the policy, the <value_name> value must
			// exist and the **del.<value_name> value must not.
			//
			// value_data:
			//
			// Check to see if the key for this policy exists. 
			// If if it does, retrieve a handle
			// If not, create it.

			rStatus = RegOpenKeyEx(machine_key, privpol.pol_key, 0, KEY_WRITE | KEY_WOW64_64KEY, &setting_key);

			if (rStatus != ERROR_SUCCESS)
			{
				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegOpenKeyEx", rStatus, TRUE);

				rStatus = RegCreateKeyEx(machine_key, privpol.pol_key,
					0, NULL, 0, KEY_SET_VALUE | KEY_QUERY_VALUE, NULL, &setting_key, NULL);

				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegCreateKeyEx", rStatus, FALSE);

			}

			switch (privpol.pol_datatype) {

			case	POL_DWORD:
				tmp = wcstol(privpol.pol_value_data, '\0', 10);
				rStatus = RegSetKeyValue(setting_key, NULL, privpol.pol_value_name, REG_DWORD, &tmp, sizeof(DWORD));

				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegSetValueEx", rStatus, FALSE);

				break;

			case POL_WSTRING:

				StringCbLength(privpol.pol_value_data, sizeof(privpol.pol_value_data), &len);
				len += sizeof(WCHAR); // plus null bytes

				rStatus = RegSetKeyValue(setting_key, NULL, privpol.pol_value_name, REG_SZ, (BYTE *)privpol.pol_value_data, (DWORD)len);

				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegSetValueEx", rStatus, FALSE);

				break;

			default:
				break;
			}

			// del delkey

			// Remove the not configured value indicator from the hive.
			// It may not exist, so the RegDeleteValue may return
			// and error, this can be ignored.
			//

			rStatus = RegDeleteValue(machine_key, full_path_del);

			if (rStatus != ERROR_SUCCESS)
				m0priv_errormsg(privpol, L"RegDeleteValue", rStatus, TRUE);

			rStatus = RegCloseKey(setting_key);

			if (rStatus != ERROR_SUCCESS)
				m0priv_errormsg(privpol, L"RegCloseKey", rStatus, FALSE);

			break;

		case POL_DISABLED:
		case POL_DELETE:
			//
			// Disable the policy.
			// must remove the <name> value and add the
			//  **del.<name> value.
			//
			// Same stesp as before, check to see if the key for this
			// policy exists,
			// if not, create it.
			//
			rStatus = RegOpenKeyEx(machine_key, privpol.pol_key, 0, KEY_WRITE | KEY_WOW64_64KEY, &setting_key);

			if (rStatus != ERROR_SUCCESS)
			{
				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegOpenKeyEx", rStatus, TRUE);

				rStatus = RegCreateKeyEx(machine_key, privpol.pol_key, 0, NULL, 0, KEY_SET_VALUE | KEY_QUERY_VALUE, NULL, &setting_key, NULL);

				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegCreateKeyEx", rStatus, FALSE);

				bCreate = TRUE;
			}


			//
			// If we did not create the key, then our value
			//  *may* exist.
			// try to read it.  If we succeed, write that value back
			//  to **del.<name>
			// if not, then set **del.<name> to 0
			//

			switch (privpol.pol_datatype) {

			case	POL_DWORD:

				dwType = REG_DWORD;
				cbType = sizeof(DWORD);

				rStatus = RegGetValue(machine_key, privpol.pol_key, privpol.pol_value_name, RRF_RT_ANY, &dwType, (BYTE *)(&tmp), &cbType);
				_itow_s(tmp, privpol.pol_value_data, sizeof(privpol.pol_value_data) / sizeof(WCHAR), 10);

				if (rStatus != ERROR_SUCCESS) {
					m0priv_errormsg(privpol, L"RegGetValue", rStatus, TRUE);
					tmp = 0;
				}
				else {
					rStatus = RegDeleteValue(setting_key, privpol.pol_value_name);
					if (rStatus != ERROR_SUCCESS)
						m0priv_errormsg(privpol, L"RegDeleteValue", rStatus, TRUE);

				}

				if (bCreate)
					tmp = 0;

				rStatus = RegSetValueEx(setting_key, value_name_del, NULL, REG_DWORD, (BYTE *)(&tmp), sizeof(DWORD));

				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegSetValueEx", rStatus, FALSE);

				break;

			case POL_WSTRING:

				dwType = REG_SZ;
				cbType = sizeof(privpol.pol_value_data);

				ZeroMemory(privpol.pol_value_data, sizeof(privpol.pol_value_data));

				rStatus = RegGetValue(machine_key, privpol.pol_key, privpol.pol_value_name, RRF_RT_ANY, &dwType, (BYTE *)(&privpol.pol_value_data), &cbType);

				if (rStatus != ERROR_SUCCESS) {
					m0priv_errormsg(privpol, L"RegGetValue", rStatus, TRUE);
					ZeroMemory(privpol.pol_value_data, sizeof(privpol.pol_value_data));
					cbType = sizeof(WCHAR);
				}
				else {
					rStatus = RegDeleteValue(setting_key, privpol.pol_value_name);
					if (rStatus != ERROR_SUCCESS)
						m0priv_errormsg(privpol, L"RegDeleteValue", rStatus, TRUE);
				}

				if (bCreate) {
					ZeroMemory(privpol.pol_value_data, sizeof(privpol.pol_value_data));
					cbType = sizeof(WCHAR);
				}

				rStatus = RegSetValueEx(setting_key, value_name_del, NULL, REG_SZ, (BYTE *)(&privpol.pol_value_data), cbType);

				if (rStatus != ERROR_SUCCESS)
					m0priv_errormsg(privpol, L"RegSetValueEx", rStatus, FALSE);

				break;

			default:
				break;
			}

			rStatus = RegCloseKey(setting_key);

			if (rStatus != ERROR_SUCCESS)
				m0priv_errormsg(privpol, L"RegCloseKey", rStatus, FALSE);

			break;

		default:

			break;

		}

		// Apply policy and free resources
		rStatus = RegCloseKey(machine_key);
		if (rStatus != ERROR_SUCCESS)
			m0priv_errormsg(privpol, L"RegCloseKey", rStatus, FALSE);

		DWORD ecnt = 0;

		do {
			hr = pLGPO->Save(FALSE, op_add, &ext_guid, &snap_guid);
			if (hr != S_OK) Sleep(500);
		} while ((hr != S_OK) && (ecnt < 6));

		if (hr != S_OK) {
			m0priv_errormsg(privpol, L"pLGPO->Save", hr, FALSE);
		}

		hr = pLGPO->Release();
		if (hr != S_OK) {
			m0priv_errormsg(privpol, L"pLGPO->Release", hr, FALSE);
		}
	}
	else {
		printf("[#] GPOU CoCreateInstance failed\n");
		m0priv_errormsg(privpol, L"CoCreateInstance", hr, FALSE);
	}

	CoUninitialize();
	return hr;
}


