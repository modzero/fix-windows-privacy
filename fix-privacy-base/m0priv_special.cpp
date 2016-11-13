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


extern DWORD status_count;

HRESULT m0_special_modify(void) {
	HRESULT hr = S_OK;

	// 1.) Disable Windows Defender SubmitSamplesConsent (=0)
	// call  "C:\Windows\system32\SystemSettingsAdminFlows.exe" Defender SubmitSamplesConsent 0

	printf("[%04d] Processing SPECIAL/Defender\n", status_count++);
	hr = m0_special_launchprogram(_wcsdup(L"C:\\Windows\\system32\\SystemSettingsAdminFlows.exe Defender SubmitSamplesConsent 0"));
	
	// 2.) Disable Windows Defender SpyNetReporting (=0)
	// call  "C:\Windows\system32\SystemSettingsAdminFlows.exe" Defender SpyNetReporting 0

	printf("[%04d] Processing SPECIAL/Defender\n", status_count++);
	hr = m0_special_launchprogram(_wcsdup(L"C:\\Windows\\system32\\SystemSettingsAdminFlows.exe Defender SpyNetReporting 0"));

	// 3. let apps on my other devices open apps [...]
	// call "C:\Windows\system32\SystemSettingsAdminFlows.exe" DisableCDPUserAuthPolicy

	printf("[%04d] Processing SPECIAL/CDP User Auth Policy\n", status_count++);
	hr = m0_special_launchprogram(_wcsdup(L"C:\\Windows\\system32\\SystemSettingsAdminFlows.exe DisableCDPUserAuthPolicy"));

	return hr;
}



HRESULT m0_special_launchprogram(wchar_t *cmdline) {
	HRESULT hr = S_OK;
	BOOL cp = FALSE;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	wchar_t exename[] = L"c:\\Windows\\system32\\SystemSettingsAdminFlows.exe";

	//printf("[+] Executing cmdline %S\n", cmdline);

	cp = CreateProcessW(
		NULL,
		cmdline,
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi);           // Pointer to PROCESS_INFORMATION structure
		
	if (!cp)
	{
		hr = GetLastError();
		printf("[#] CreateProcess failed (%d).\n", hr);
		return hr;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return hr;
}