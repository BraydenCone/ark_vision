#pragma once

namespace SDK
{
    namespace UnrealEngine
    {
        template<class T>
        struct TRotator
        {
            T Pitch, Yaw, Roll;

            TRotator() : Pitch((T)0), Yaw((T)0), Roll((T)0) {}
            TRotator(T pitch, T yaw, T roll) : Pitch(pitch), Yaw(yaw), Roll(roll) {}
            TRotator operator+(const TRotator& other) const { return TRotator(Pitch + other.Pitch, Yaw + other.Yaw, Roll + other.Roll); }
            TRotator operator-(const TRotator& other) const { return TRotator(Pitch - other.Pitch, Yaw - other.Yaw, Roll - other.Roll); }
            TRotator operator*(T scalar) const { return TRotator(Pitch * scalar, Yaw * scalar, Roll * scalar); }
            TRotator& operator= (const TRotator& other) { Pitch = other.Pitch; Yaw = other.Yaw; Roll = other.Roll; return *this; }
            TRotator& operator+=(const TRotator& other) { Pitch += other.Pitch; Yaw += other.Yaw; Roll += other.Roll; return *this; }
            TRotator& operator-=(const TRotator& other) { Pitch -= other.Pitch; Yaw -= other.Yaw; Roll -= other.Roll; return *this; }
            TRotator& operator*=(const T other) { Yaw *= other; Pitch *= other; Roll *= other; return *this; }

            TRotator Clamp()
            {
                if (Pitch > (T)180)
                    Pitch -= (T)360;
                else if (Pitch < (T)-180)
                    Pitch += (T)360;
                if (Yaw > (T)180)
                    Yaw -= (T)360;
                else if (Yaw < (T)-180)
                    Yaw += (T)360;
                if (Pitch < (T)-89)
                    Pitch = (T)-89;
                if (Pitch > (T)89)
                    Pitch = (T)89;
                while (Yaw < (T)-180)
                    Yaw += (T)360;
                while (Yaw > (T)180)
                    Yaw -= (T)360;
                Roll = (T)0;
                return *this;
            }
        };
    }
}
