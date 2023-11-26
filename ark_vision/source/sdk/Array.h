#pragma once

namespace SDK
{
	namespace UnrealEngine
	{
        template<class T>
        struct TArray
        {
            friend class FString;
        public:
            TArray()
            {
                Data = 0;
                Count = 0;
                Max = 0;
            }

            inline int Num() const
            {
                return Count;
            };

            inline T& operator[](int i)
            {
                return Data[i];
            };

            inline bool IsValidIndex(int i) const
            {
                return i < Count;
            }

        private:
            T* Data;
            int Count;
            int Max;
        };
	}
}
