#pragma once

#include "UnrealEngine.h"

namespace SDK
{
	namespace Game
	{
		struct USceneComponent
		{
			unsigned char                              padding_0[0x140];
			SDK::UnrealEngine::Vector                  RelativeLocation;
			SDK::UnrealEngine::Rotator                 RelativeRotation;
			SDK::UnrealEngine::Vector                  RelativeScale3D;
			SDK::UnrealEngine::Vector                  ComponentVelocity;
		};

		struct AActor
		{
			unsigned char                              padding_0[0x3B0];
			USceneComponent*                           RootComponent;
		};

		struct ULevel
		{
			unsigned char                              padding_0[0x98];
			SDK::UnrealEngine::TArray<AActor*>         Actors;
		};

		struct ULocalPlayer
		{
			unsigned char                              padding_0[0x30];
			void*                                      PlayerController;

			unsigned char                              padding_1[0x80 - 0x30 - sizeof(PlayerController)];
			void*                                      ViewportClient;
		};

		struct UGameInstance
		{
			unsigned char                              padding_0[0x38];
			SDK::UnrealEngine::TArray<ULocalPlayer*>   LocalPlayers;
		};

		struct UWorld
		{
			unsigned char                              padding_0[0x1D0];
			ULevel*                                    PersistentLevel;

			unsigned char                              padding_1[0x2F8 - 0x1D0 - sizeof(PersistentLevel)];
			void* GameState;

			unsigned char                              padding_2[0x310 - 0x2F8 - sizeof(GameState)];
			SDK::UnrealEngine::TArray<ULevel*>         Levels;

			unsigned char                              padding_3[0x358 - 0x310 - sizeof(Levels)];
			UGameInstance*                             OwningGameInstance;
		};

		struct UWorldProxy
		{
			UWorld*                                    World;
		};

		extern UWorldProxy* GWorld;
	}
}
