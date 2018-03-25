#pragma once

#include <windows.h>
#include <d3d9types.h>

#include <dxva2api.h>

#include <string>

namespace Utils
{
    std::string D3DFORMATToStr(D3DFORMAT format);

    std::string DXVA2_VideoChromaSubSamplingToStr(DXVA2_VideoChromaSubSampling VideoChromaSubSampling);

    std::string DXVA2_NominalRangeToStr(DXVA2_NominalRange NominalRange);

    std::string DXVA2_VideoLightingToStr(DXVA2_VideoLighting VideoLighting);

    std::string DXVA2_VideoPrimariesToStr(DXVA2_VideoPrimaries VideoPrimaries);

    std::string DXVA2_VideoTransferFunctionToStr(DXVA2_VideoTransferFunction VideoTransferFunction);

    std::string DXVA2_SampleFormatToStr(DXVA2_SampleFormat SampleFormat);
};
