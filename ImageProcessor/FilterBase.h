#pragma once
#include "ImageBuffer.h"

namespace ip {
	class FilterBase {
	public:
		virtual ~FilterBase() = default;
		virtual void process(ImageBuffer& image) = 0;
	};
}