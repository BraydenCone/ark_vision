#pragma once

namespace SDK
{
	namespace UnrealEngine
	{
        template<class T>
        struct TVector
        {
            T X, Y, Z;

            TVector() : X((T)0), Y((T)0), Z((T)0) {}
            TVector(T x, T y, T z) : X(x), Y(y), Z(z) {}
            TVector(T InF) : X(InF), Y(InF), Z(InF) {}
            T Size() const { return (T)sqrt(X * X + Y * Y + Z * Z); }
            T Sum() const { return X + Y + Z; }
            T Size2D() const { return (T)sqrt(X * X + Y * Y); }
            T SizeSquared() const { return X * X + Y * Y + Z * Z; }
            T DistTo(const TVector& V) const { return (*this - V).Size(); }
            TVector unit() const { T mult = (1.f / Size()); return TVector(X * mult, Y * mult, Z * mult); }

            TVector operator+(const TVector& other) const { return TVector(X + other.X, Y + other.Y, Z + other.Z); }
            TVector operator-(const TVector& other) const { return TVector(X - other.X, Y - other.Y, Z - other.Z); }
            TVector operator*(const TVector& V) const { return TVector(X * V.X, Y * V.Y, Z * V.Z); }
            TVector operator/(const TVector& V) const { return TVector(X / V.X, Y / V.Y, Z / V.Z); }
            bool operator==(const TVector& V) const { return X == V.X && Y == V.Y && Z == V.Z; }
            bool operator!=(const TVector& V) const { return X != V.X || Y != V.Y || Z != V.Z; }
            TVector operator-() const { return TVector(-X, -Y, -Z); }
            TVector operator+(T Bias) const { return TVector(X + Bias, Y + Bias, Z + Bias); }
            TVector operator-(T Bias) const { return TVector(X - Bias, Y - Bias, Z - Bias); }
            TVector operator*(T Scale) const { return TVector(X * Scale, Y * Scale, Z * Scale); } const
                TVector operator/(T Scale) const { const T RScale = 1.f / Scale; return TVector(X * RScale, Y * RScale, Z * RScale); }
            TVector operator=(const TVector& V) { X = V.X; Y = V.Y; Z = V.Z; return *this; }
            TVector operator+=(const TVector& V) { X += V.X; Y += V.Y; Z += V.Z; return *this; }
            TVector operator-=(const TVector& V) { X -= V.X; Y -= V.Y; Z -= V.Z; return *this; }
            TVector operator*=(const TVector& V) { X *= V.X; Y *= V.Y; Z *= V.Z; return *this; }
            TVector operator/=(const TVector& V) { X /= V.X; Y /= V.Y; Z /= V.Z; return *this; }
            TVector operator*=(T Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }
            TVector operator/=(T V) { const T RV = 1.f / V; X *= RV; Y *= RV; Z *= RV; return *this; }
            T operator|(const TVector& V) const { return X * V.X + Y * V.Y + Z * V.Z; }
            TVector operator^(const TVector& V) const { return TVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X); }
        };
	}
}
