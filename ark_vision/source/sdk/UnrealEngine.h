#pragma once

#include <string>
#include <locale>

#include <math.h>

#include "Array.h"
#include "Vector.h"
#include "Rotator.h"

namespace SDK
{
    namespace UnrealEngine
    {
        typedef TVector<float> FVector;
        typedef TVector<double> Vector;

        typedef TRotator<float> FRotator;
        typedef TRotator<double> Rotator;

        struct FString : private TArray<wchar_t>
        {
            inline FString()
            {
            };

            FString(const wchar_t* other)
            {
                Max = Count = *other ? std::wcslen(other) + 1 : 0;

                if (Count)
                {
                    Data = const_cast<wchar_t*>(other);
                }
            };

            inline bool IsValid() const
            {
                return Data != nullptr;
            }

            inline const wchar_t* c_str() const
            {
                return Data;
            }

            std::string ToString() const
            {
                auto length = std::wcslen(Data);
                std::string str(length, '\0');
                std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);
                return str;
            }
        };

        struct FNameEntryHandle
        {
            uint32_t Block = 0;
            uint32_t Offset = 0;

            FNameEntryHandle(uint32_t block, uint32_t offset) : Block(block), Offset(offset) {};
            FNameEntryHandle(uint32_t id) : Block(id >> 16), Offset(id & 65535) {};
            operator uint32_t() const { return (Block << 16 | Offset); }
        };

        struct FNameEntry
        {
            uint16_t bIsWide : 1;
            uint16_t LowercaseProbeHash : 5;
            uint16_t Len : 10;
            union
            {
                char AnsiName[1024];
                wchar_t	WideName[1024];
            };

            std::string String()
            {
                if (bIsWide) { return std::string(); }
                return { AnsiName, Len };
            }
        };

        struct FNamePool
        {
            unsigned char Lock[8];
            uint32_t CurrentBlock;
            uint32_t CurrentByteCursor;
            unsigned char* Blocks[8192];

            FNameEntry* GetEntry(FNameEntryHandle handle) { return reinterpret_cast<FNameEntry*>(Blocks[handle.Block] + 2 * static_cast<uint64_t>(handle.Offset)); }
        };

        struct FName
        {
            uint32_t Index;
            uint32_t Number;

            std::string GetName();
        };

        struct UObject
        {
            void** VFTable;
            uint32_t ObjectFlags;
            uint32_t InternalIndex;
            UObject* ClassPrivate;
            FName NamePrivate;
            UObject* OuterPrivate;

            std::string GetName()
            {
                return NamePrivate.GetName();
            }

            std::string GetFullName()
            {
                std::string Name;
                if (ClassPrivate)
                {
                    std::string Temp;
                    for (UObject* CurrentOuter = OuterPrivate; CurrentOuter; CurrentOuter = CurrentOuter->OuterPrivate)
                    {
                        Temp = CurrentOuter->GetName() + "." + Temp;
                    }

                    Name = ClassPrivate->GetName();
                    Name += " ";
                    Name += Temp;
                    Name += GetName();
                }
                return Name;
            }
        };

        struct FUObjectItem
        {
            UObject* Object;
            int Flags;
            int ClusterRootIndex;
            int SerialNumber;
        };

        struct FChunkedFixedUObjectArray
        {
        private:
            enum
            {
                NumElementsPerChunk = 64 * 1024,
            };

            FUObjectItem** Objects;
            FUObjectItem* PreAllocatedObjects;
            int MaxElements;
            int NumElements;
            int MaxChunks;
            int NumChunks;
        public:
            int Num() const { return NumElements; }
            int Capacity() const { return MaxElements; }
            bool IsValidIndex(int Index) const { return Index < NumElements && Index >= 0; }

            FUObjectItem const* GetObjectPtr(int Index) const
            {
                const int ChunkIndex = Index / NumElementsPerChunk;
                const int WithinChunkIndex = Index % NumElementsPerChunk;

                if (!IsValidIndex(Index))
                {
                    return 0;
                }

                if (ChunkIndex >= NumChunks)
                {
                    return 0;
                }

                if (Index > MaxElements)
                {
                    return 0;
                }

                FUObjectItem* Chunk = Objects[ChunkIndex];
                if (!Chunk)
                {
                    return 0;
                }

                return Chunk + WithinChunkIndex;
            }

            FUObjectItem* GetObjectPtr(int Index)
            {
                const int ChunkIndex = Index / NumElementsPerChunk;
                const int WithinChunkIndex = Index % NumElementsPerChunk;

                if (!IsValidIndex(Index))
                {
                    return 0;
                }

                if (ChunkIndex > NumChunks)
                {
                    return 0;
                }

                if (Index > MaxElements)
                {
                    return 0;
                }

                FUObjectItem* Chunk = Objects[ChunkIndex];
                if (!Chunk)
                {
                    return 0;
                }

                return Chunk + WithinChunkIndex;
            }

            FUObjectItem const& operator[](int Index) const
            {
                FUObjectItem const* ItemPtr = GetObjectPtr(Index);
                if (ItemPtr)
                {
                    return *ItemPtr;
                }
            }

            FUObjectItem& operator[](int Index)
            {
                FUObjectItem* ItemPtr = GetObjectPtr(Index);
                if (ItemPtr)
                {
                    return *ItemPtr;
                }
            }

            int64_t GetAllocatedSize() const
            {
                return MaxChunks * sizeof(FUObjectItem*) + NumChunks * NumElementsPerChunk * sizeof(FUObjectItem);
            }

            template<typename T>
            T FindUObject(const char* NameToFind)
            {
                for (int CurrentElement = 0; CurrentElement < NumElements; CurrentElement++)
                {
                    FUObjectItem* ObjectItem = GetObjectPtr(CurrentElement);
                    if (ObjectItem && ObjectItem->Object->GetFullName() == NameToFind)
                    {
                        return static_cast<T>(ObjectItem->Object);
                    }
                }

                return 0;
            }
        };

        struct FUObjectArray
        {
            typedef FChunkedFixedUObjectArray TUObjectArray;

            int    ObjFirstGCIndex;
            int    ObjLastNonGCIndex;
            int    MaxObjectsNotConsideredByGC;
            bool            OpenForDisregardForGC;
            TUObjectArray   ObjObjects;

            FUObjectItem* IndexToObject(int Index)
            {
                if (Index < ObjObjects.Num())
                {
                    return const_cast<FUObjectItem*>(&ObjObjects[Index]);
                }
                return 0;
            }
        };

        extern FUObjectArray* GUObjectArray;
        extern FNamePool* NamePoolData;
    }
}
