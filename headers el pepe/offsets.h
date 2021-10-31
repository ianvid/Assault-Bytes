#pragma once
#include <vector>
uintptr_t modulebase1 = (uintptr_t)GetModuleHandle(L"ac_client.exe");


namespace pointers {
	//variables
	uintptr_t* localplayer = (uintptr_t*)(modulebase1 + 0x10f4f4);
	float* localxpos = (float*)(*localplayer + 0x34);
	float* localypos = (float*)(*localplayer + 0x38);
	float* localzpos = (float*)(*localplayer + 0x3C);
	int* localhealth = (int*)(*localplayer + 0xF8);
	float* localRecoilMultiplier = (float*)(modulebase1 + 0xEE444);
	float* localKickMultiplier = (float*)(modulebase1 + 0xEE3F8);
	//code caves
	int* localspeedCAVE = (int*)(modulebase1 + 0x12677);
	float* localjumpPowerCAVE = (float*)(modulebase1 + 0x1267B);
	//pointers to assembly instructions
	uintptr_t asmSpeed = (modulebase1 + 0x5BEA5);
	uintptr_t asmMinimap = (modulebase1 + 0x9FA7);
	uintptr_t asmMap = (modulebase1 + 0x9695);
	uintptr_t asmSuperjump = (modulebase1 + 0x5B318);
	uintptr_t asmMovility = (modulebase1 + 0x5B072);
	uintptr_t asmGrenades = (modulebase1 + 0x63378);

}




