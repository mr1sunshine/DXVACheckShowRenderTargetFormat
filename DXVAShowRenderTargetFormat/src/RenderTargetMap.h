#pragma once

#include <d3d9.h>
#include <initguid.h>
#include <Dxva2api.h>

#include <vector>
#include <map>
#include <tuple>

class RenderTargetMap
{
public:

    typedef std::tuple<DXVA2_VideoChromaSubSampling,
        DXVA2_NominalRange,
        DXVA2_VideoLighting,
        DXVA2_VideoPrimaries,
        DXVA2_VideoTransferFunction,
        DXVA2_SampleFormat,
        D3DFORMAT> rtmValueType;
    typedef std::map< std::vector<D3DFORMAT>, std::vector< rtmValueType > > RenderTargetMapType;

    RenderTargetMap() = default;
    ~RenderTargetMap() = default;

    RenderTargetMap(const RenderTargetMap&) = delete;
    RenderTargetMap& operator=(const RenderTargetMap &) = delete;

    void Create(IDirect3DDevice9* pDD);

    const RenderTargetMapType& GetMap() const;

    static void PrintRTM(const RenderTargetMapType& rtm);

private:

    std::vector<D3DFORMAT> GetRenderTargets(IDirectXVideoProcessorService *service, D3DFORMAT source_format, DXVA2_VideoChromaSubSampling VideoChromaSubSampling,
                                            DXVA2_NominalRange NominalRange, DXVA2_VideoLighting VideoLighting, DXVA2_VideoPrimaries VideoPrimaries,
                                            DXVA2_VideoTransferFunction VideoTransferFunction, DXVA2_SampleFormat SampleFormat);

    RenderTargetMapType m_rtm;
};
