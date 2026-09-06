#pragma once
#include "ImageBuffer.h" // 이미지를 처리해야 하므로 ImageBuffer를 알아야 합니다.
#include "FilterBase.h"

namespace ip {

    class BrightnessFilter : public FilterBase {
    private:
		int m_brightness; // 밝기 조절 값 (예: 0은 원본, 50은 밝기 증가, -50은 밝기 감소)
    public:

        BrightnessFilter(int brightness) {
            m_brightness = brightness;
        }

        // 핵심 기능: 이미지를 받아서 밝기를 조절하는 함수
        // 참조(&)를 사용하여 원본 이미지를 직접 수정하도록 설계해 봅니다.
        void process(ImageBuffer& image) override;
    };
}