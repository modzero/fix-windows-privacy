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
#include "Intsafe.h"
#include "Shlobj.h"
#include "Shlwapi.h"
#include "gpedit.h"

#include "m0gpo.h"

DWORD status_count = 0;

void m0priv_errormsg(m0_privpol_t privpol, WCHAR *function, LSTATUS rStatus, BOOL ignore_filenotfound)
{
	WCHAR errmsg[256];
	ZeroMemory(errmsg, sizeof(errmsg));

	if ((rStatus == ERROR_FILE_NOT_FOUND) && ignore_filenotfound)
		return;

	FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, rStatus,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), errmsg, sizeof(errmsg) / sizeof(WCHAR), NULL);

	printf("[#] [%d] %S %S failed: [%08x] %S\n", (privpol.section_key), privpol.pol_key, function, rStatus, errmsg);
	return;
}

void trace_log(wchar_t* buf) {
	HANDLE f = NULL;
	PWSTR datapath = NULL;

	return; // do not trace anything right now

	DWORD buflen = ((DWORD)wcslen(buf) * sizeof(wchar_t));
	DWORD written = 0;

	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &datapath)))
	{
		StringCchCatW(datapath, MAX_PATH, L"\\modzero\\fix-windows-privacy\\logs");
		StringCchCatW(datapath, MAX_PATH, L"\\debuglog.txt");
	}

	f = CreateFileW(datapath, FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (f == INVALID_HANDLE_VALUE)
	{
		return;
	}

	WriteFile(
		f,
		buf,
		buflen,
		&written,
		NULL);

	CloseHandle(f);
	free(datapath);

	return;
}

