#include "Utils.h"

#define CASE_TO_STR(x) case x: { ret = #x; break; }

std::string Utils::D3DFORMATToStr(D3DFORMAT format)
{
    std::string ret = "unknown";

    switch (format)
    {
        CASE_TO_STR(D3DFMT_UNKNOWN);

        CASE_TO_STR(D3DFMT_R8G8B8);
        CASE_TO_STR(D3DFMT_A8R8G8B8);
        CASE_TO_STR(D3DFMT_X8R8G8B8);
        CASE_TO_STR(D3DFMT_R5G6B5);
        CASE_TO_STR(D3DFMT_X1R5G5B5);
        CASE_TO_STR(D3DFMT_A1R5G5B5);
        CASE_TO_STR(D3DFMT_A4R4G4B4);
        CASE_TO_STR(D3DFMT_R3G3B2);
        CASE_TO_STR(D3DFMT_A8);
        CASE_TO_STR(D3DFMT_A8R3G3B2);
        CASE_TO_STR(D3DFMT_X4R4G4B4);
        CASE_TO_STR(D3DFMT_A2B10G10R10);
        CASE_TO_STR(D3DFMT_A8B8G8R8);
        CASE_TO_STR(D3DFMT_X8B8G8R8);
        CASE_TO_STR(D3DFMT_G16R16);
        CASE_TO_STR(D3DFMT_A2R10G10B10);
        CASE_TO_STR(D3DFMT_A16B16G16R16);

        CASE_TO_STR(D3DFMT_A8P8);
        CASE_TO_STR(D3DFMT_P8);

        CASE_TO_STR(D3DFMT_L8);
        CASE_TO_STR(D3DFMT_A8L8);
        CASE_TO_STR(D3DFMT_A4L4);

        CASE_TO_STR(D3DFMT_V8U8);
        CASE_TO_STR(D3DFMT_L6V5U5);
        CASE_TO_STR(D3DFMT_X8L8V8U8);
        CASE_TO_STR(D3DFMT_Q8W8V8U8);
        CASE_TO_STR(D3DFMT_V16U16);
        CASE_TO_STR(D3DFMT_A2W10V10U10);

        CASE_TO_STR(D3DFMT_UYVY);
        CASE_TO_STR(D3DFMT_R8G8_B8G8);
        CASE_TO_STR(D3DFMT_YUY2);
        CASE_TO_STR(D3DFMT_G8R8_G8B8);
        CASE_TO_STR(D3DFMT_DXT1);
        CASE_TO_STR(D3DFMT_DXT2);
        CASE_TO_STR(D3DFMT_DXT3);
        CASE_TO_STR(D3DFMT_DXT4);
        CASE_TO_STR(D3DFMT_DXT5);

        CASE_TO_STR(D3DFMT_D16_LOCKABLE);
        CASE_TO_STR(D3DFMT_D32);
        CASE_TO_STR(D3DFMT_D15S1);
        CASE_TO_STR(D3DFMT_D24S8);
        CASE_TO_STR(D3DFMT_D24X8);
        CASE_TO_STR(D3DFMT_D24X4S4);
        CASE_TO_STR(D3DFMT_D16);

        CASE_TO_STR(D3DFMT_D32F_LOCKABLE);
        CASE_TO_STR(D3DFMT_D24FS8);
#if !defined(D3D_DISABLE_9EX)
        CASE_TO_STR(D3DFMT_D32_LOCKABLE);
        CASE_TO_STR(D3DFMT_S8_LOCKABLE);
#endif
        CASE_TO_STR(D3DFMT_L16);

        CASE_TO_STR(D3DFMT_VERTEXDATA);
        CASE_TO_STR(D3DFMT_INDEX16);
        CASE_TO_STR(D3DFMT_INDEX32);

        CASE_TO_STR(D3DFMT_Q16W16V16U16);

        CASE_TO_STR(D3DFMT_MULTI2_ARGB8);
        CASE_TO_STR(D3DFMT_R16F);
        CASE_TO_STR(D3DFMT_G16R16F);
        CASE_TO_STR(D3DFMT_A16B16G16R16F);

        CASE_TO_STR(D3DFMT_R32F);
        CASE_TO_STR(D3DFMT_G32R32F);
        CASE_TO_STR(D3DFMT_A32B32G32R32F);

        CASE_TO_STR(D3DFMT_CxV8U8);

#if !defined(D3D_DISABLE_9EX)
        CASE_TO_STR(D3DFMT_A1);
        CASE_TO_STR(D3DFMT_A2B10G10R10_XR_BIAS);
        CASE_TO_STR(D3DFMT_BINARYBUFFER);
#endif
        CASE_TO_STR(D3DFMT_FORCE_DWORD);

        default:
        {
            char data[5] = {0};
            data[0] = format & 0xFF;
            data[1] = (format >> 8) & 0xFF;
            data[2] = (format >> 16) & 0xFF;
            data[3] = (format >> 24) & 0xFF;
            bool printable = true;
            for (auto i = 0; i < 4; ++i)
            {
                if (!isascii(data[i]))
                {
                    printable = false;
                    break;
                }
            }
            if (printable)
                ret = std::string(data);
            else
                ret = std::to_string(format);
            break;
        }
    }

    return ret;
}

std::string Utils::DXVA2_VideoChromaSubSamplingToStr(DXVA2_VideoChromaSubSampling VideoChromaSubSampling)
{
    std::string ret = "unknown";
    switch (VideoChromaSubSampling)
    {
        CASE_TO_STR(DXVA2_VideoChromaSubsamplingMask);
        CASE_TO_STR(DXVA2_VideoChromaSubsampling_Unknown);
        CASE_TO_STR(DXVA2_VideoChromaSubsampling_ProgressiveChroma);
        CASE_TO_STR(DXVA2_VideoChromaSubsampling_Horizontally_Cosited);
        CASE_TO_STR(DXVA2_VideoChromaSubsampling_Vertically_Cosited);
        //CASE_TO_STR(DXVA2_VideoChromaSubsampling_Vertically_AlignedChromaPlanes);
        CASE_TO_STR(DXVA2_VideoChromaSubsampling_MPEG2);
        CASE_TO_STR(DXVA2_VideoChromaSubsampling_MPEG1);
        CASE_TO_STR(DXVA2_VideoChromaSubsampling_DV_PAL);
        CASE_TO_STR(DXVA2_VideoChromaSubsampling_Cosited);
    }
    return ret;
}

std::string Utils::DXVA2_NominalRangeToStr(DXVA2_NominalRange NominalRange)
{
    std::string ret = "unknown";

    switch (NominalRange)
    {
        CASE_TO_STR(DXVA2_NominalRangeMask);
        CASE_TO_STR(DXVA2_NominalRange_Unknown);
        //CASE_TO_STR(DXVA2_NominalRange_Normal);
        //CASE_TO_STR(DXVA2_NominalRange_Wide);
        CASE_TO_STR(DXVA2_NominalRange_0_255);
        CASE_TO_STR(DXVA2_NominalRange_16_235);
        CASE_TO_STR(DXVA2_NominalRange_48_208);
    }
    return ret;
}

std::string Utils::DXVA2_VideoLightingToStr(DXVA2_VideoLighting VideoLighting)
{
    std::string ret = "unknown";

    switch (VideoLighting)
    {
        CASE_TO_STR(DXVA2_VideoLightingMask);
        CASE_TO_STR(DXVA2_VideoLighting_Unknown);
        CASE_TO_STR(DXVA2_VideoLighting_bright);
        CASE_TO_STR(DXVA2_VideoLighting_office);
        CASE_TO_STR(DXVA2_VideoLighting_dim);
        CASE_TO_STR(DXVA2_VideoLighting_dark);
    }

    return ret;
}

std::string Utils::DXVA2_VideoPrimariesToStr(DXVA2_VideoPrimaries VideoPrimaries)
{
    std::string ret = "unknown";

    switch (VideoPrimaries)
    {
        CASE_TO_STR(DXVA2_VideoPrimariesMask);
        CASE_TO_STR(DXVA2_VideoPrimaries_Unknown);
        CASE_TO_STR(DXVA2_VideoPrimaries_reserved);
        CASE_TO_STR(DXVA2_VideoPrimaries_BT709);
        CASE_TO_STR(DXVA2_VideoPrimaries_BT470_2_SysM);
        CASE_TO_STR(DXVA2_VideoPrimaries_BT470_2_SysBG);
        CASE_TO_STR(DXVA2_VideoPrimaries_SMPTE170M);
        CASE_TO_STR(DXVA2_VideoPrimaries_SMPTE240M);
        CASE_TO_STR(DXVA2_VideoPrimaries_EBU3213);
        CASE_TO_STR(DXVA2_VideoPrimaries_SMPTE_C);
    }

    return ret;
}

std::string Utils::DXVA2_VideoTransferFunctionToStr(DXVA2_VideoTransferFunction VideoTransferFunction)
{
    std::string ret = "unknown";

    switch (VideoTransferFunction)
    {
        CASE_TO_STR(DXVA2_VideoTransFuncMask);
        CASE_TO_STR(DXVA2_VideoTransFunc_Unknown);
        CASE_TO_STR(DXVA2_VideoTransFunc_10);
        CASE_TO_STR(DXVA2_VideoTransFunc_18);
        CASE_TO_STR(DXVA2_VideoTransFunc_20);
        CASE_TO_STR(DXVA2_VideoTransFunc_22);
        CASE_TO_STR(DXVA2_VideoTransFunc_709);
        CASE_TO_STR(DXVA2_VideoTransFunc_240M);
        CASE_TO_STR(DXVA2_VideoTransFunc_sRGB);
        CASE_TO_STR(DXVA2_VideoTransFunc_28);
    }

    return ret;
}

std::string Utils::DXVA2_SampleFormatToStr(DXVA2_SampleFormat SampleFormat)
{
    std::string ret = "unknown";

    switch (SampleFormat)
    {
        CASE_TO_STR(DXVA2_SampleFormatMask);
        CASE_TO_STR(DXVA2_SampleUnknown);
        CASE_TO_STR(DXVA2_SampleProgressiveFrame);
        CASE_TO_STR(DXVA2_SampleFieldInterleavedEvenFirst);
        CASE_TO_STR(DXVA2_SampleFieldInterleavedOddFirst);
        CASE_TO_STR(DXVA2_SampleFieldSingleEven);
        CASE_TO_STR(DXVA2_SampleFieldSingleOdd);
        CASE_TO_STR(DXVA2_SampleSubStream);
    }

    return ret;
}
