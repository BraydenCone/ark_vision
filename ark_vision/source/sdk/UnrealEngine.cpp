#include "UnrealEngine.h"

SDK::UnrealEngine::FUObjectArray* SDK::UnrealEngine::GUObjectArray = nullptr;
SDK::UnrealEngine::FNamePool* SDK::UnrealEngine::NamePoolData = nullptr;

std::string SDK::UnrealEngine::FName::GetName()
{
	auto entry = NamePoolData->GetEntry(Index);
	auto name = entry->String();
	if (Number > 0)
	{
		name += '_' + std::to_string(Number);
	}
	auto pos = name.rfind('/');
	if (pos != std::string::npos)
	{
		name = name.substr(pos + 1);
	}
	return name;
}
