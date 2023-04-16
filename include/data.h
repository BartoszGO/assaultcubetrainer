#pragma once
#include <Windows.h>
namespace offsets
{
    constexpr uintptr_t  health = 0xEC;
    constexpr uintptr_t  pitch = 0x34;
    constexpr uintptr_t  yaw = 0x38;
    constexpr uintptr_t  pos = 0x28;
    constexpr uintptr_t name = 0x205;
}

namespace addreses 
{

    constexpr uintptr_t playerBasePtrAddr = 0x17E0A8;
    constexpr uintptr_t entityListPtrAddr = 0x18AC04;
    constexpr uintptr_t numPlayersAddr = 0x18AC0C;
}