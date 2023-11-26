#include "SDK.h"

void SDK::Initialize(uintptr_t objects, uintptr_t names, uintptr_t world)
{
	SDK::UnrealEngine::GUObjectArray = (SDK::UnrealEngine::FUObjectArray*)objects;
	SDK::UnrealEngine::NamePoolData = (SDK::UnrealEngine::FNamePool*)names;
	SDK::Game::GWorld = (SDK::Game::UWorldProxy*)world;
}
