
/* !!! DO NOT EDIT !!! 
 * Auto-Generated source-code!
 * Edit parse-settings.py or settings-rules.txt instead
 */
 
//#include "stdafx.h"
#include <stdio.h>

#include "windows.h"
#include "Strsafe.h"
#include "gpedit.h"

#include "gpo_init_policy.h"
#include "m0gpo.h"


DWORD m0_init_policies(m0_privpol_t *policy, DWORD maxpol)
{
	DWORD count = 0;

	printf("[d] vorher (%d %p)\n", maxpol, policy);

	ZeroMemory(policy, maxpol * sizeof(m0_privpol_t));
  
	printf("[d] nacher\n");


	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\AppHost,EnableWebContentEvaluation,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AppHost");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"EnableWebContentEvaluation");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,Control Panel\International\User Profile,HttpAcceptLanguageOptOut,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"Control Panel\\International\\User Profile");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"HttpAcceptLanguageOptOut");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Internet Explorer\International,AcceptLanguage,
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Internet Explorer\\International");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"AcceptLanguage");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\Global\{E6AD100E-5F4E-44CD-BE0F-2265D88D14F5},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\Global\\{E6AD100E-5F4E-44CD-BE0F-2265D88D14F5}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\Global\{52079E78-A92B-413F-B213-E8FE35712E72},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\Global\\{52079E78-A92B-413F-B213-E8FE35712E72}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Personalization\Settings,AcceptedPrivacyPolicy,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Personalization\\Settings");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"AcceptedPrivacyPolicy");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\SettingSync\Groups\Language,Enabled,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\SettingSync\\Groups\\Language");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Enabled");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\InputPersonalization,RestrictImplicitTextCollection,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\InputPersonalization");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RestrictImplicitTextCollection");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\InputPersonalization,RestrictImplicitInkCollection,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\InputPersonalization");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RestrictImplicitInkCollection");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\InputPersonalization\TrainedDataStore,HarvestContacts,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\InputPersonalization\\TrainedDataStore");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"HarvestContacts");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\Search,CortanaMUID,MUID=bc6c9f905afb4a01a748197238147f73
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Search");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"CortanaMUID");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"MUID=bc6c9f905afb4a01a748197238147f73");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\Global\{C1D23ACC-752B-43E5-8448-8D0E519CD6D6},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\Global\\{C1D23ACC-752B-43E5-8448-8D0E519CD6D6}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\S-1-15-2-1239072475-3687740317-1842961305-3395936705-4023953123-1525404051-2779347315\{7D7E8402-7C54-4821-A34E-AEEFD62DED93},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\S-1-15-2-1239072475-3687740317-1842961305-3395936705-4023953123-1525404051-2779347315\\{7D7E8402-7C54-4821-A34E-AEEFD62DED93}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\S-1-15-2-1063257880-1914585122-1954150059-946145533-116938067-416079064-1690466945\{7D7E8402-7C54-4821-A34E-AEEFD62DED93},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\S-1-15-2-1063257880-1914585122-1954150059-946145533-116938067-416079064-1690466945\\{7D7E8402-7C54-4821-A34E-AEEFD62DED93}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\Global\{D89823BA-7180-4B81-B50C-7E471E6121A3},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\Global\\{D89823BA-7180-4B81-B50C-7E471E6121A3}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\Global\{8BC668CF-7728-45BD-93F8-CF2B3B41D7AB},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\Global\\{8BC668CF-7728-45BD-93F8-CF2B3B41D7AB}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\Global\{9231CB4C-BF57-4AF3-8C55-FDA7BFCC04C5},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\Global\\{9231CB4C-BF57-4AF3-8C55-FDA7BFCC04C5}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\Global\{992AFA70-6F47-4148-B3E9-3003349C1548},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\Global\\{992AFA70-6F47-4148-B3E9-3003349C1548}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\Global\{21157C1F-2651-4CC1-90CA-1F28B02263F6},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\Global\\{21157C1F-2651-4CC1-90CA-1F28B02263F6}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\Global\{A8804298-2D5F-42E3-9531-9C8C39EB29CE},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\Global\\{A8804298-2D5F-42E3-9531-9C8C39EB29CE}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\Global\{BFA794E4-F964-4FDB-90F6-51056BFE4B44},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\Global\\{BFA794E4-F964-4FDB-90F6-51056BFE4B44}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\Global\{E5323777-F976-4f5b-9B55-B94699C46E44},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\Global\\{E5323777-F976-4f5b-9B55-B94699C46E44}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\Global\{2EEF81BE-33FA-4800-9670-1CD474972C3F},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\Global\\{2EEF81BE-33FA-4800-9670-1CD474972C3F}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\Global\{7D7E8402-7C54-4821-A34E-AEEFD62DED93},Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\Global\\{7D7E8402-7C54-4821-A34E-AEEFD62DED93}");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeviceAccess\Global\LooselyCoupled,Value,Deny
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceAccess\\Global\\LooselyCoupled");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Value");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Deny");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Siuf\Rules,NumberOfSIUFInPeriod,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Siuf\\Rules");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"NumberOfSIUFInPeriod");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DELETE,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\Internet Settings\Connections,SavedLegacySettings,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Connections");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"SavedLegacySettings");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_DELETE;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DELETE,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\Internet Settings\Connections,DefaultConnectionSettings,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Connections");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"DefaultConnectionSettings");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_DELETE;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\Internet Settings,ProxyEnable,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"ProxyEnable");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\Internet Settings,ProxyOverride,*.local
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"ProxyOverride");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"*.local");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\Internet Settings,ProxyServer,
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"ProxyServer");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DELETE,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\Internet Settings,AutoConfigURL,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"AutoConfigURL");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_DELETE;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DELETE,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\Internet Settings,AutoDetect,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"AutoDetect");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_DELETE;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DELETE,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\Internet Settings,ProxyServer,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"ProxyServer");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_DELETE;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\AdvertisingInfo,Enabled,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Enabled");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\AdvertisingInfo,Id,Noooooo!
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Id");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"Noooooo!");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System,DisableShutdownNamedPipe,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"DisableShutdownNamedPipe");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,UseAdvancedStartup,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"UseAdvancedStartup");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,EnableBDEWithNoTPM,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"EnableBDEWithNoTPM");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,UseTPM,2
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"UseTPM");
	policy[count].pol_value_data.dwVal = 2;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,UseTPMPIN,2
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"UseTPMPIN");
	policy[count].pol_value_data.dwVal = 2;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,UseTPMKey,2
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"UseTPMKey");
	policy[count].pol_value_data.dwVal = 2;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,UseTPMKeyPIN,2
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"UseTPMKeyPIN");
	policy[count].pol_value_data.dwVal = 2;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,UseEnhancedPin,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"UseEnhancedPin");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVConfigureBDE,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVConfigureBDE");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVAllowBDE,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVAllowBDE");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVDisableBDE,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVDisableBDE");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVDenyCrossOrg,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVDenyCrossOrg");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVHardwareEncryption,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVHardwareEncryption");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVAllowSoftwareEncryptionFailover,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVAllowSoftwareEncryptionFailover");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVRestrictHardwareEncryptionAlgorithms,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVRestrictHardwareEncryptionAlgorithms");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVPassphrase,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVPassphrase");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVEnforcePassphrase,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVEnforcePassphrase");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVPassphraseComplexity,2
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVPassphraseComplexity");
	policy[count].pol_value_data.dwVal = 2;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVPassphraseLength,8
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVPassphraseLength");
	policy[count].pol_value_data.dwVal = 8;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVRecovery,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVRecovery");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVManageDRA,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVManageDRA");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVRecoveryPassword,2
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVRecoveryPassword");
	policy[count].pol_value_data.dwVal = 2;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVRecoveryKey,2
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVRecoveryKey");
	policy[count].pol_value_data.dwVal = 2;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVHideRecoveryPage,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVHideRecoveryPage");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVActiveDirectoryBackup,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVActiveDirectoryBackup");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVActiveDirectoryInfoToStore,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVActiveDirectoryInfoToStore");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVRequireActiveDirectoryBackup,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVRequireActiveDirectoryBackup");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\PassportForWork\PINComplexity,Digits,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\PassportForWork\\PINComplexity");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Digits");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\PassportForWork\PINComplexity,LowercaseLetters,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\PassportForWork\\PINComplexity");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"LowercaseLetters");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\PassportForWork\PINComplexity,SpecialCharacters,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\PassportForWork\\PINComplexity");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"SpecialCharacters");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\PassportForWork\PINComplexity,UppercaseLetters,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\PassportForWork\\PINComplexity");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"UppercaseLetters");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\HotspotAuthentication,Enabled,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\HotspotAuthentication");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Enabled");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\OneDrive,DisableLibrariesDefaultSaveToOneDrive,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\OneDrive");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"DisableLibrariesDefaultSaveToOneDrive");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\OneDrive,DisableFileSyncNGSC,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\OneDrive");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"DisableFileSyncNGSC");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\OneDrive,DisableFileSync,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\OneDrive");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"DisableFileSync");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\Windows Search,AllowCortana,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"AllowCortana");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\Windows Search,AllowCortanaAboveLock,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"AllowCortanaAboveLock");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\Windows Search,AllowIndexingEncryptedStoresOrItems,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"AllowIndexingEncryptedStoresOrItems");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\Windows Search,AllowSearchToUseLocation,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"AllowSearchToUseLocation");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\Windows Search,ConnectedSearchUseWeb,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"ConnectedSearchUseWeb");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\Windows Search,PreventIndexingEmailAttachments,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"PreventIndexingEmailAttachments");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\Windows Search,PreventIndexingOfflineFiles,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"PreventIndexingOfflineFiles");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\Windows Search,PreventIndexingOutlook,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"PreventIndexingOutlook");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\Windows Search,PreventIndexingPublicFolders,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"PreventIndexingPublicFolders");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\WinRM\Service\WinRS,AllowRemoteShellAccess,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\WinRM\\Service\\WinRS");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"AllowRemoteShellAccess");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,System\CurrentControlSet\Policies\Microsoft\FVE,RDVDenyWriteAccess,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"System\\CurrentControlSet\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVDenyWriteAccess");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_SZ,GPOM,SOFTWARE\Policies\Microsoft\FVE,RDVAllowedHardwareEncryptionAlgorithms,2.16.840.1.101.3.4.1.2;2.16.840.1.101.3.4.1.42
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\FVE");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"RDVAllowedHardwareEncryptionAlgorithms");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"2.16.840.1.101.3.4.1.2;2.16.840.1.101.3.4.1.42");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,SOFTWARE\Policies\Microsoft\Windows\AppPrivacy,LetAppsAccessCallHistory,2
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\AppPrivacy");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"LetAppsAccessCallHistory");
	policy[count].pol_value_data.dwVal = 2;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DISABLE,GPOM,SOFTWARE\Policies\Microsoft\Windows\DataCollection,AllowTelemetry,
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"AllowTelemetry");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_DISABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DELETE,GPOM,SOFTWARE\Policies\Microsoft\PassportForWork\PINComplexity,History,
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\PassportForWork\\PINComplexity");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"History");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_DELETE;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,GPOM,System\CurrentControlSet\Policies,NtfsEncryptPagingFile,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"System\\CurrentControlSet\\Policies");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"NtfsEncryptPagingFile");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_GPOM;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Input\TIPC,Enabled,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Input\\TIPC");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Enabled");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKLM,SOFTWARE\Microsoft\Windows\CurrentVersion\SmartGlass,UserAuthPolicy,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\SmartGlass");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"UserAuthPolicy");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKLM;
	count++;

	//
	// REG_DWORD,HKLM,SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\DataCollection,AllowTelemetry,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\DataCollection");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"AllowTelemetry");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKLM;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Siuf\Rules,NumberOfSIUFInPeriod,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Siuf\\Rules");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"NumberOfSIUFInPeriod");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Windows\CurrentVersion\DeliveryOptimization,SystemSettingsDownloadMode,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeliveryOptimization");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"SystemSettingsDownloadMode");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Policies\Microsoft\MicrosoftEdge\Main,DoNotTrack,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\MicrosoftEdge\\Main");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"DoNotTrack");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Policies\Microsoft\MicrosoftEdge\PhishingFilter,EnabledV9,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\MicrosoftEdge\\PhishingFilter");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"EnabledV9");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Policies\Microsoft\MicrosoftEdge\Privacy,ClearBrowsingHistoryOnExit,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\MicrosoftEdge\\Privacy");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"ClearBrowsingHistoryOnExit");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Policies\Microsoft\MicrosoftEdge\Main,Use FormSuggest,no
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Policies\\Microsoft\\MicrosoftEdge\\Main");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Use FormSuggest");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"no");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Internet Explorer\Geolocation,BlockAllWebsites,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Internet Explorer\\Geolocation");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"BlockAllWebsites");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Internet Explorer\Main,Use FormSuggest,no
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Internet Explorer\\Main");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Use FormSuggest");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"no");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_SZ,HKCU,SOFTWARE\Microsoft\Internet Explorer\Main\,ormSuggest Passwords,no
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Internet Explorer\\Main\\");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"ormSuggest Passwords");
	StringCbCopy(policy[count].pol_value_data.wcsVal,  sizeof(policy[0].pol_value_data.wcsVal),  L"no");
	policy[count].pol_datatype = POL_WSTRING;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Internet Explorer\DomainSuggestion,Enabled,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Internet Explorer\\DomainSuggestion");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Enabled");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Internet Explorer\Main\WindowsSearch,EnabledScopes,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Internet Explorer\\Main\\WindowsSearch");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"EnabledScopes");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Internet Explorer\Main\WindowsSearch,AutoCompleteGroups,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Internet Explorer\\Main\\WindowsSearch");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"AutoCompleteGroups");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Internet Explorer\Feed Discovery,Sound,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Internet Explorer\\Feed Discovery");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"Sound");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Internet Explorer\Feeds,TurnOffOPV,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Internet Explorer\\Feeds");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"TurnOffOPV");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Feeds,SyncStatus,0
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Feeds");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"SyncStatus");
	policy[count].pol_value_data.dwVal = 0;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;

	//
	// REG_DWORD,HKCU,SOFTWARE\Microsoft\Internet Explorer\Privacy,ClearBrowsingHistoryOnExit,1
	//

	StringCbCopy(policy[count].pol_key,            sizeof(policy[0].pol_key),            L"SOFTWARE\\Microsoft\\Internet Explorer\\Privacy");
	StringCbCopy(policy[count].pol_value_name,     sizeof(policy[0].pol_value_name),     L"ClearBrowsingHistoryOnExit");
	policy[count].pol_value_data.dwVal = 1;
	policy[count].pol_datatype = POL_DWORD;
	policy[count].pol_mode = POL_ENABLED;
	policy[count].section_key = WS_KEY_HKCU;
	count++;
	

	return count;
}	

	
