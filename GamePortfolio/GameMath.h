#pragma once
#include <math.h>

class GameMath
{
    static const double PI;
    static const double TwoPI;
    static const double HalfPI;
    static const double InvPI;
    static const double Arc;
    static const double TwoArc;
    static const double SMALL_NUMBER;

public:
    template <typename T>
    static T ABS(const T N) {
        return (((N) < 0) ? (-N) : (N));
    }

    template <typename T>
    static T MIN(const T A, const T B) {
        return (((A) < (B)) ? (A) : (B));
    }

    template <typename T>
    static T MAX(const T A, const T B) {
        return (((A) < (B)) ? (B) : (A));
    }

    template <typename T>
    static T CLAMP(const T Min, const T Max, const T N) {
        return (((N) < (Min)) ? (Min) : ((N) < (Max)) ? (N) : (Max));
    }

    template <typename T>
    static T TRUNCATEINT(const T N) {
        return static_cast<int>(N);
    }

    template <typename T>
    static T ROUNDINT(const T N) {
        return (((N) < (T)0) ? TRUNCATEINT(N - 0.5f) : TRUNCATEINT(N + 0.5f));
    }

    template <typename T>
    static T FLOORINT(const T N) {
        return (((N) < (T)0) ? TRUNCATEINT(N) - 1.f : TRUNCATEINT(N));
    }

    template <typename T>
    static T CEILINT(const T N) {
        return (((N) < (T)0) ? TRUNCATEINT(N) : TRUNCATEINT(N) + 1.f);
    }

    static double CEIL(const float R) {
        return (((R) < 0) ? ((R)-((R)-((int)R))) : ((R)-((R)-((int)R))) + 1.f);
    }

    static double FLOOR(const float R) {
        return (((R) < 0) ? ((R)-((R)-((int)R))) - 1.f : ((R)-((R)-((int)R))));
    }

    static double TRUNC(const float R) {
        return (((R) > 0) ? FLOOR(R) : CEIL(R));
    }

    static double FMOD(const float N, const float OP) {
        return N - TRUNC(N / OP) * OP;
    }

    static long long int FACTORIAL(const int S, const int E) {
        if (S == E) { return S; }
        if (S > E) { return 1; }

        return FACTORIAL(S, (S + E) / 2) * FACTORIAL((S + E) / 2 + 1, E);
    }

    static long long int FACTORIAL(const int N) {
        return (N == 1 || N == 0) ? 1 : FACTORIAL(N - 1) * N;
    }

    static long long int POWER(const int B, const int E) {
        if (E == 0) {
            return 1;
        }

        if (E % 2 == 0) {
            return POWER(B * B, E / 2);
        }

        return POWER(B * B, (E - 1) / 2) * B;
    }

    static float Deg2Rad(const float Deg) {
        return Deg * PI / Arc;
    }

    static float Rad2Deg(const float Rad) {
        return Rad * Arc / PI;
    }

    static float ApproximateSqrt(const float N) {
        float x = 1.f;
        int i = ((*(int*)&N) >> 1) + ((*(int*)&x) >> 1);

        return *(float*)&i;
    }

    static float NewtonSqrt(const float N) {
        float x = 1.f;

        for (int i = 0; i < 10; i++) {
            x -= (x * x - N) / (2 * x);
        }

        return x;
    }

    static float BabylonianSqrt(const float N) {
        float x = 2.f;

        for (int i = 0; i < 10; i++) {
            x = (x + (N / x)) / 2.f;
        }

        return x;
    }

    static float Sqrt(const float N) {
        float s = 0, e = 0;

        for (s = N * 0.5f; s != e;) {
            e = s;
            s = ((N / e) + e) * 0.5f;
        }

        return s;
    }

    static float rSqrt(const float N) {
        float x = 1.f;
        int one = *(int*)&x;
        int magic = one + (one >> 1);             // 0x5F400000

        int i = magic - ((*(int*)&N) >> 1);
        float val = *(float*)&i;

        return val * (1.5f - 0.5f * N * val * val);
    }

    /* 호너 법칙, 속도 개선 후 정밀도 낮음 */
    static float sin(const float x, int n = 15, float r = 1) {
        if (n > 1) {
            float inter = 1 - ((x * x * r) / (n * (n - 1)));
            return sin(x, n - 2, inter);
        }

        return x * r;
    }

    /* 호너 법칙, 속도 개선 후 정밀도 낮음 */
    static float cos(const float x, int n = 15, int deno = 2) {
        float inter = (x * x) / (deno * (deno - 1));

        if (n > 1) {
            return 1 - inter * cos(x, n - 2, deno * 2);
        }

        return inter;
    }

    static void GetSinCos(float& sinf, float& cosf, float degree) {
        if (degree == 0.f) {
            sinf = 0.f;
            cosf = 1.f;
        }
        else if (degree == 90.f) {
            sinf = 1.f;
            cosf = 0.f;
        }
        else if (degree == 180.f) {
            sinf = 0.f;
            cosf = -1.f;
        }
        else if (degree == 270.f) {
            sinf = -1.f;
            cosf = 0.f;
        }
        else {
            GetSinCosRad(sinf, cosf, degree * PI / Arc);
        }
    }

    static void GetSinCosRad(float& sinf, float& cosf, float radian) {
        /* O(n^2)이 더 정밀함 */
        // sinf = sin(radian);
        // cosf = cos(radian);

        // 실패
        sinf = static_cast<float>(::sin(radian));
        cosf = static_cast<float>(::cos(radian));
    }
};

