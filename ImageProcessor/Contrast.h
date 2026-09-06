#pragma once
#include "ImageBuffer.h" // 이미지를 처리해야 하므로 ImageBuffer를 알아야 합니다.
#include "FilterBase.h"

namespace ip {

    class ContrastFilter : public FilterBase {
    private:
		float m_contrast; // 대비 조절 값 (예: 1.0은 원본, 1.5는 50% 증가, 0.5는 50% 감소)
    public:

        ContrastFilter(float contrast) {
            m_contrast = contrast;
        }

        // 핵심 기능: 이미지를 받아서 대비를 조절하는 함수
        // 참조(&)를 사용하여 원본 이미지를 직접 수정하도록 설계해 봅니다.
        void process(ImageBuffer& image) override;
    };
}