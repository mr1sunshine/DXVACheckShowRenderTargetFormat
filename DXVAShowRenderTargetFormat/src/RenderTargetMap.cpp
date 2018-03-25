#include "RenderTargetMap.h"

#include "Utils.h"

#include <set>

#pragma comment (lib, "Dxva2.lib")

void RenderTargetMap::Create(IDirect3DDevice9 * pDD)
{
    IDirectXVideoProcessorService *service;
    auto hr = DXVA2CreateVideoService(pDD, IID_PPV_ARGS(&service));
    if (hr != S_OK)
    {
        printf("hr = 0x%08X", hr);
    }

    const std::vector<DXVA2_VideoChromaSubSampling> VideoChromaSubSamplings =
    {
        DXVA2_VideoChromaSubsampling_ProgressiveChroma,
        DXVA2_VideoChromaSubsampling_Horizontally_Cosited,
        DXVA2_VideoChromaSubsampling_Vertically_Cosited,
        DXVA2_VideoChromaSubsampling_MPEG2,
        DXVA2_VideoChromaSubsampling_MPEG1,
        DXVA2_VideoChromaSubsampling_DV_PAL,
        DXVA2_VideoChromaSubsampling_Cosited,
    };

    const std::vector<DXVA2_NominalRange> NominalRanges =
    {
        DXVA2_NominalRange_0_255,
        DXVA2_NominalRange_16_235,
        DXVA2_NominalRange_48_208
    };

    const std::vector<DXVA2_VideoLighting> VideoLightings =
    {
        DXVA2_VideoLighting_bright,
        DXVA2_VideoLighting_office,
        DXVA2_VideoLighting_dim,
        DXVA2_VideoLighting_dark
    };

    const std::vector<DXVA2_VideoPrimaries> VideoPrimaries =
    {
        DXVA2_VideoPrimaries_BT709,
        DXVA2_VideoPrimaries_BT470_2_SysM,
        DXVA2_VideoPrimaries_BT470_2_SysBG,
        DXVA2_VideoPrimaries_SMPTE170M,
        DXVA2_VideoPrimaries_SMPTE240M,
        DXVA2_VideoPrimaries_EBU3213,
        DXVA2_VideoPrimaries_SMPTE_C
    };

    const std::vector<DXVA2_VideoTransferFunction> VideoTransferFunctions =
    {
        DXVA2_VideoTransFunc_10,
        DXVA2_VideoTransFunc_18,
        DXVA2_VideoTransFunc_20,
        DXVA2_VideoTransFunc_22,
        DXVA2_VideoTransFunc_709,
        DXVA2_VideoTransFunc_240M,
        DXVA2_VideoTransFunc_sRGB,
        DXVA2_VideoTransFunc_28
    };

    const std::vector<DXVA2_SampleFormat> SampleFormats =
    {
        DXVA2_SampleProgressiveFrame,
        DXVA2_SampleFieldInterleavedEvenFirst,
        DXVA2_SampleFieldInterleavedOddFirst,
        DXVA2_SampleFieldSingleEven,
        DXVA2_SampleFieldSingleOdd,
        DXVA2_SampleSubStream
    };

    

    for (auto VideoChromaSubSampling : VideoChromaSubSamplings)
    {
        //printf("%s\n", Utils::DXVA2_VideoChromaSubSamplingToStr(VideoChromaSubSampling).c_str());
        for (auto NominalRange : NominalRanges)
        {
            //printf("%s\n", Utils::DXVA2_NominalRangeToStr(NominalRange).c_str());
            for (auto VideoLighting : VideoLightings)
            {
                //printf("%s\n", Utils::DXVA2_VideoLightingToStr(VideoLighting).c_str());
                for (auto VideoPrimarie : VideoPrimaries)
                {
                    //printf("%s\n", Utils::DXVA2_VideoPrimariesToStr(VideoPrimarie).c_str());
                    for (auto VideoTransferFunction : VideoTransferFunctions)
                    {
                        //printf("%s\n", Utils::DXVA2_VideoTransferFunctionToStr(VideoTransferFunction).c_str());
                        for (auto SampleFormat : SampleFormats)
                        {
                            //printf("%s\n", Utils::DXVA2_SampleFormatToStr(SampleFormat).c_str());
                            for (unsigned long long format = 0; format < D3DFMT_FORCE_DWORD; ++format)
                            {
                                //if (format % 1000000 == 0)
                                //    printf("%d\n", format / 1000000);

                                //printf("%s\n", Utils::D3DFORMATToStr((D3DFORMAT)format).c_str());

                                const auto res = GetRenderTargets(service, (D3DFORMAT)format, VideoChromaSubSampling, NominalRange,
                                                            VideoLighting, VideoPrimarie, VideoTransferFunction, SampleFormat);
                                if (res.empty())
                                    continue;
                                /*printf("%s: ", Utils::D3DFORMATToStr((D3DFORMAT)format).c_str());
                                for (const auto &res_format : res)
                                {
                                    printf("%s ", Utils::D3DFORMATToStr(res_format).c_str());
                                }
                                printf("\n");*/

                                auto it = m_rtm.find(res);
                                const auto combination = std::make_tuple(VideoChromaSubSampling,
                                                                         NominalRange,
                                                                         VideoLighting,
                                                                         VideoPrimarie,
                                                                         VideoTransferFunction,
                                                                         SampleFormat,
                                                                         (D3DFORMAT)format);

                                if (it != m_rtm.end())
                                {
                                    it->second.emplace_back(combination);
                                }
                                else
                                {
                                    std::vector<rtmValueType> vec = {combination};
                                    m_rtm.emplace_hint(it, res, vec);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

const RenderTargetMap::RenderTargetMapType & RenderTargetMap::GetMap() const
{
    return m_rtm;
}

void RenderTargetMap::PrintRTM(const RenderTargetMapType & rtm)
{
    for (const auto &record : rtm)
    {
        const auto &render_formats = record.first;

        for (const auto &format : render_formats)
        {
            printf("%s ", Utils::D3DFORMATToStr(format).c_str());
        }
        printf(":\n");

        const auto &combinations = record.second;


        std::set<DXVA2_VideoChromaSubSampling> VideoChromaSubSamplings;
        std::set<DXVA2_NominalRange> NominalRanges;
        std::set<DXVA2_VideoLighting> VideoLightings;
        std::set<DXVA2_VideoPrimaries> VideoPrimaries;
        std::set<DXVA2_VideoTransferFunction> VideoTransferFunctions;
        std::set<DXVA2_SampleFormat> SampleFormats;
        std::set<D3DFORMAT> D3DFORMATs;

        for (const auto &combination : combinations)
        {
            VideoChromaSubSamplings.emplace(std::get<0>(combination));
            NominalRanges.emplace(std::get<1>(combination));
            VideoLightings.emplace(std::get<2>(combination));
            VideoPrimaries.emplace(std::get<3>(combination));
            VideoTransferFunctions.emplace(std::get<4>(combination));
            SampleFormats.emplace(std::get<5>(combination));
            D3DFORMATs.emplace(std::get<6>(combination));
        }
        printf("\t[");

        for (auto record : VideoChromaSubSamplings)
            printf("%s, ", Utils::DXVA2_VideoChromaSubSamplingToStr(record).c_str());

        printf("]\n");
        printf("\t[");

        for (auto record : NominalRanges)
            printf("%s, ", Utils::DXVA2_NominalRangeToStr(record).c_str());

        printf("]\n");
        printf("\t[");

        for (auto record : VideoLightings)
            printf("%s, ", Utils::DXVA2_VideoLightingToStr(record).c_str());

        printf("]\n");
        printf("\t[");

        for (auto record : VideoPrimaries)
            printf("%s, ", Utils::DXVA2_VideoPrimariesToStr(record).c_str());

        printf("]\n");
        printf("\t[");

        for (auto record : VideoTransferFunctions)
            printf("%s, ", Utils::DXVA2_VideoTransferFunctionToStr(record).c_str());

        printf("]\n");
        printf("\t[");

        for (auto record : SampleFormats)
            printf("%s, ", Utils::DXVA2_SampleFormatToStr(record).c_str());

        printf("]\n");
        printf("\t[");

        for (auto record : D3DFORMATs)
            printf("%s, ", Utils::D3DFORMATToStr(record).c_str());

        printf("]\n");
    }
}

std::vector<D3DFORMAT> RenderTargetMap::GetRenderTargets(IDirectXVideoProcessorService * service, D3DFORMAT source_format, DXVA2_VideoChromaSubSampling VideoChromaSubSampling, DXVA2_NominalRange NominalRange, DXVA2_VideoLighting VideoLighting, DXVA2_VideoPrimaries VideoPrimaries, DXVA2_VideoTransferFunction VideoTransferFunction, DXVA2_SampleFormat SampleFormat)
{
    DXVA2_VideoDesc g_VideoDesc;
    g_VideoDesc.SampleWidth = 800;
    g_VideoDesc.SampleHeight = 600;
    g_VideoDesc.SampleFormat.VideoChromaSubsampling = VideoChromaSubSampling;
    g_VideoDesc.SampleFormat.NominalRange = NominalRange;
    g_VideoDesc.SampleFormat.VideoTransferMatrix = 0;
    g_VideoDesc.SampleFormat.VideoLighting = VideoLighting;
    g_VideoDesc.SampleFormat.VideoPrimaries = VideoPrimaries;
    g_VideoDesc.SampleFormat.VideoTransferFunction = VideoTransferFunction;
    g_VideoDesc.SampleFormat.SampleFormat = SampleFormat;
    g_VideoDesc.Format = source_format;
    g_VideoDesc.InputSampleFreq.Numerator = 25;
    g_VideoDesc.InputSampleFreq.Denominator = 1;
    g_VideoDesc.OutputFrameFreq.Numerator = 25;
    g_VideoDesc.OutputFrameFreq.Denominator = 1;

    UINT i, count;
    D3DFORMAT* formats = NULL;

    auto hr = service->GetVideoProcessorRenderTargets(DXVA2_VideoProcProgressiveDevice, &g_VideoDesc, &count, &formats);

    std::vector<D3DFORMAT> result;
    if (FAILED(hr))
        return result;

    for (i = 0; i < count; i++)
    {
        result.emplace_back(formats[i]);
    }

    CoTaskMemFree(formats);

    return result;
}