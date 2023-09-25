#include "vanTime.h"
#include "vanApplication.h"

extern van::Application application;

namespace van
{
    LARGE_INTEGER	Time::mCpuFrequency = {};
    LARGE_INTEGER   Time::mPrevFrequency = {};
    LARGE_INTEGER	Time::mCurFrequency = {};
    float			Time::mDeltaTime = 0.0f;
    float			Time::mOneSecond = 0.0f;

    void Time::Initialize()
    {
        //CPU 의 초당 반복되는 주파수를 얻어온다.
        QueryPerformanceFrequency(&mCpuFrequency);

        //프로그램을 시작했을때의 CPU 클럭 수
        QueryPerformanceCounter(&mPrevFrequency);
    }

    void Time::Update()
    {
        QueryPerformanceCounter(&mCurFrequency);

        // 매 프레임의 CPU 클럭수를 저장한다.
        float differenceInFrequancy
            = static_cast<float>((mCurFrequency.QuadPart - mPrevFrequency.QuadPart));

        // DeltaTime = 1Frame 에 걸린 시간 [sec]
        // 델타타임 = 해당 프레임의 CPU 클럭수 / CPU의 초당 클럭수
        mDeltaTime = differenceInFrequancy / static_cast<float>(mCpuFrequency.QuadPart);
        // 현재 프레임까지의 CPU 클러수를 mPrecFrequency에 저장 (다음 프레임의 클럭수를 구하는데 사용)
        mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
    }

    void Time::Render()
    {
        static int iCount = 0;
        ++iCount;

        // 1 초에 한번
        mOneSecond += mDeltaTime;
        if (1.0f < mOneSecond)
        {
            HWND hWnd = application.GetHwnd();

            wchar_t szFloat[50] = {};
            float FPS = 1.f / mDeltaTime;
            swprintf_s(szFloat, 50, L"DeltaTime : %d", iCount);
            int iLen = wcsnlen_s(szFloat, 50);
            //TextOut(_dc, 10, 10, szFloat, iLen);

            SetWindowText(hWnd, szFloat);

            // 누적시간, 카운트 초기화
            mOneSecond = 0.f;
            iCount = 0;
        }
    }
}