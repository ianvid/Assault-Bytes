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
DWORD comehookSpeedHack = asmSpeed +0x6;
DWORD comehookSuperjump = asmSuperjump +0x6;
DWORD comehookminimap = asmMinimap + 0x6;
DWORD comehookmap = asmMap + 0x6;
DWORD comehookmovility = asmMovility + 0x6;


void __declspec(naked) hookSpeedHack() {
    __asm {
        mov eax, modulebase
        add eax, 0x12677
        mov eax, [eax]
        mov[edx + 0x80], eax
        jmp[comehookSpeedHack]
    }
}
void __declspec(naked) unhookSpeedHack() {
    __asm {
        add edx, 0x80
        mov[edx], al
        jmp[comehookSpeedHack]
    }
}
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


void finalhook(DWORD hookaddress, int lenght, void* myfunct) {
    Hook((void*)hookaddress, myfunct, lenght);
}


