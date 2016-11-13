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
#include "m0gpo.h"

extern "C"
{
	extern __declspec(dllexport) DWORD fixpriv_init_services(m0_privsvc_t *pol, DWORD count);
	extern __declspec(dllexport) DWORD fixpriv_init_policies(m0_privpol_t *pol, DWORD count);
	extern __declspec(dllexport) HRESULT fixpriv_special_modify(void);
	extern __declspec(dllexport) HRESULT fixpriv_modify_regkey_user(m0_privpol_t privpol);
	extern __declspec(dllexport) HRESULT fixpriv_modify_gpo_regkey_user(m0_privpol_t privpol);
	extern __declspec(dllexport) HRESULT fixpriv_modify_gpo_regkey_machine(m0_privpol_t privpol);
	extern __declspec(dllexport) HRESULT fixpriv_svc_modify(m0_privsvc_t privsvc);
	extern __declspec(dllexport) HRESULT fixpriv_dummy(m0_privpol_t privpol);
	extern __declspec(dllexport) HRESULT fixpriv_modify_policy(m0_privpol_t privpol);
	extern __declspec(dllexport) void fixpriv_elevate();
	extern __declspec(dllexport) void fixpriv_elevate_withargs(const char *av);
	extern __declspec(dllexport) fixpriv_status_t fixpriv_check_regkey(m0_privpol_t privpol);
	extern __declspec(dllexport) fixpriv_status_t fixpriv_svc_check(m0_privsvc_t privsvc);
}
