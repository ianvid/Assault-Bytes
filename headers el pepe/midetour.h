#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include "offsets.h"
DWORD modulebase= (DWORD)GetModuleHandle(L"ac_client.exe");
using namespace pointers;

bool Hook(void* toHook, void* myfunct, int len) {
    DWORD curProtection;
    VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);
    memset(toHook, 0x90, len);
    DWORD relativeAddress = ((DWORD)myfunct - (DWORD)toHook) - 5;
    *(BYTE*)toHook = 0xE9; 
    *(DWORD*)((DWORD)toHook + 1) = relativeAddress;
    DWORD temp;
    VirtualProtect(toHook, len, curProtection, &temp);
    return true;
}

//assembler-----------------------------------------------------------------------

//estos son los comebacks (jump back)
DWORD comehookSuperjump = asmSuperjump +0x6;
DWORD comehookminimap = asmMinimap + 0x6;
DWORD comehookminimapFFA = asmMinimapFFA + 0x6;
DWORD comehookminimapFFA2 = asmMinimapFFA2 + 0x6;
DWORD comehookmap = asmMap + 0x6;
DWORD comehookmapFFA = asmMapFFA + 0x5;
DWORD comehookmapFFA2 = asmMapFFA2 + 0x5;
DWORD comehookmovility = asmMovility + 0x6;
DWORD comehookgrenades = asmGrenades + 0x5;
DWORD comehookRapidfire = asmRapidfire + 0x5;
DWORD comehookTriggerbot = asmTriggerbot + 0x6;

void __declspec(naked) hookminimap() { //minimap
    __asm {
        mov eax, 0x10f4f4
        add eax, modulebase
        mov eax, [eax]
        add eax, 0x32C
        mov eax, [eax]
        jmp[comehookminimap]
    }
}
void __declspec(naked) unhookminimap() { //minimap
    __asm {
        mov eax, [edi + 0x32C]
        jmp[comehookminimap]
    }
}
void __declspec(naked) hookminimapFFA() { //minimap
    __asm {
        mov ebx,0x7
        jmp[comehookminimapFFA]
    }
}
void __declspec(naked) unhookminimapFFA() { //minimap
    __asm {
        PUSH eax
        mov eax, modulebase
        mov ebx, [eax + 0x10F49C]
        POP eax
        jmp[comehookminimapFFA]
    }
}
void __declspec(naked) hookminimapFFA2() { //minimap
    __asm {
        mov ebx,0x7
        jmp[comehookminimapFFA2]
    }
}
void __declspec(naked) unhookminimapFFA2() { //minimap
    __asm {
        PUSH eax
        mov eax, modulebase
        mov ebx, [eax + 0x10F49C]
        POP eax
        jmp[comehookminimapFFA2]
    }
}
void __declspec(naked) hookmap() { //big map
    __asm {
        mov ecx, 0x10f4f4
        add ecx, modulebase
        mov ecx, [ecx]
        add ecx, 0x32C
        mov ecx, [ecx]
        jmp[comehookmap]
    }
}
void __declspec(naked) unhookmap() { //big map
    __asm {
        mov ecx, [esi + 0x32C]
        jmp[comehookmap]
    }
}
void __declspec(naked) hookmapFFA() { //big map
    __asm {
        mov eax, 7
        jmp[comehookmapFFA]
    }
}
void __declspec(naked) unhookmapFFA() { //big map
    __asm {
        PUSH ebx
        mov ebx, modulebase
        mov eax, [ebx + 0x10F49C]
        POP ebx
        jmp[comehookmapFFA]
    }
}
void __declspec(naked) hookmapFFA2() { //big map
    __asm {
        mov eax, 7
        jmp[comehookmapFFA2]
    }
}
void __declspec(naked) unhookmapFFA2() { //big map
    __asm {
        PUSH ebx
        mov ebx, modulebase
        mov eax, [ebx + 0x10F49C]
        POP ebx
        jmp[comehookmapFFA2]
    }
}
void __declspec(naked) hookSuperjump() {
    __asm {
        mov eax, modulebase
        add eax, 0x1267B
        fld dword ptr[eax]
        jmp[comehookSuperjump]
    }
}
void __declspec(naked) hookmovility() {
    __asm {
        fld1
        jmp[comehookmovility]
    }
}
void __declspec(naked) unhookmovility() {
    __asm {
        mov edi, modulebase
        add edi, 0xEE268
        fld dword ptr[edi]
        mov edi, 0
        jmp[comehookmovility]
    }
}
void __declspec(naked) hookGrenades() {
    __asm {
        jmp[comehookgrenades]
    }
}
void __declspec(naked) unhookGrenades() {
    __asm {
        dec[eax]
        mov eax, [esi + 0x0C]
        jmp[comehookgrenades]
    }
}
void __declspec(naked) hookRapidfire() {
    __asm {
        mov esi, [esi + 0x14]
        jmp[comehookRapidfire]
    }
}
void __declspec(naked) unhookRapidfire() {
    __asm {
        mov [edx],ecx
        mov esi, [esi + 0x14]
        jmp[comehookRapidfire]
    }
}

/*void __declspec(naked) hooktriggerbot() {
    __asm {
        mov ebx, 0xE2A634
        mov[ebx], 0x1
        mov[ebx], 0x0


        mov ebx, modulebase
        add ebx, 0x10F4F4
        mov ebx, [ebx]
        cmp eax, [ebx + 0x000032C]
        jmp[comehookTriggerbot]
    }
}*/


void finalhook(DWORD hookaddress, int lenght, void* myfunct) {
    Hook((void*)hookaddress, myfunct, lenght);
}


