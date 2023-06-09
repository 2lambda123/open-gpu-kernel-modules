/*
 * SPDX-FileCopyrightText: Copyright (c) 2017-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "nvidia-3d-turing.h"
#include "nvidia-3d-hopper.h"
#include "nvidia-3d.h"

#include <class/clcb97.h>
#include <class/clcb97tex.h>
#include <class/cla06fsubch.h>

void _nv3dInitChannelHopper(Nv3dChannelRec *p3dChannel)
{
    NvPushChannelPtr p = p3dChannel->pPushChannel;

    _nv3dInitChannelTuring(p3dChannel);

    // Select texture header major version 1 for the new Hopper format.
    nvPushImmedVal(p, NVA06F_SUBCHANNEL_3D, NVCB97_SET_TEXTURE_HEADER_VERSION, 1);
}

void _nv3dAssignNv3dTextureHopper(
    Nv3dRenderTexInfo info,
    Nv3dTexture *tex)
{
    nvAssert(!info.error);

    switch (info.sizes) {
    case NV3D_TEXHEAD_A8B8G8R8:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _COMPONENTS,
                           _SIZES_A8B8G8R8, tex->head);
        break;
    case NV3D_TEXHEAD_A2B10G10R10:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _COMPONENTS,
                           _SIZES_A2B10G10R10, tex->head);
        break;
    case NV3D_TEXHEAD_B5G6R5:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _COMPONENTS,
                           _SIZES_B5G6R5, tex->head);
        break;
    case NV3D_TEXHEAD_A1B5G5R5:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _COMPONENTS,
                           _SIZES_A1B5G5R5, tex->head);
        break;
    case NV3D_TEXHEAD_R8:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _COMPONENTS,
                           _SIZES_R8, tex->head);
        break;
    case NV3D_TEXHEAD_R32:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _COMPONENTS,
                           _SIZES_R32, tex->head);
        break;
    case NV3D_TEXHEAD_R16:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _COMPONENTS,
                           _SIZES_R16, tex->head);
        break;
    case NV3D_TEXHEAD_G8R8:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _COMPONENTS,
                           _SIZES_G8R8, tex->head);
        break;
    case NV3D_TEXHEAD_R16G16B16A16:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _COMPONENTS,
                           _SIZES_R16_G16_B16_A16, tex->head);
        break;
    case NV3D_TEXHEAD_R32G32B32A32:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _COMPONENTS,
                           _SIZES_R32_G32_B32_A32, tex->head);
        break;
    case NV3D_TEXHEAD_Y8_VIDEO:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _COMPONENTS,
                           _SIZES_Y8_VIDEO, tex->head);
       break;
    default:
        nvAssert(!"Unrecognized component sizes");
    }

    switch (info.dataType) {
    case NV3D_TEXHEAD_NUM_UNORM:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _DATA_TYPE,
                           _TEX_DATA_TYPE_UNORM, tex->head);
        break;
    case NV3D_TEXHEAD_NUM_UINT:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _DATA_TYPE,
                           _TEX_DATA_TYPE_UINT, tex->head);
        break;
    case NV3D_TEXHEAD_NUM_FLOAT:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _DATA_TYPE,
                           _TEX_DATA_TYPE_FLOAT, tex->head);
        break;
   case NV3D_TEXHEAD_NUM_SNORM:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _DATA_TYPE,
                           _TEX_DATA_TYPE_FLOAT, tex->head);
        break;
   case NV3D_TEXHEAD_NUM_SINT:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _DATA_TYPE,
                           _TEX_DATA_TYPE_SINT, tex->head);
        break;
    }

    switch (info.source.x) {
    case NV3D_TEXHEAD_IN_A:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _X_SOURCE,
                           _IN_A, tex->head);
        break;
    case NV3D_TEXHEAD_IN_R:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _X_SOURCE,
                           _IN_R, tex->head);
        break;
    case NV3D_TEXHEAD_IN_G:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _X_SOURCE,
                           _IN_G, tex->head);
        break;
    case NV3D_TEXHEAD_IN_B:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _X_SOURCE,
                           _IN_B, tex->head);
        break;
    case NV3D_TEXHEAD_IN_ZERO:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _X_SOURCE,
                           _IN_ZERO, tex->head);
        break;
    case NV3D_TEXHEAD_IN_ONE_FLOAT:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _X_SOURCE,
                           _IN_ONE_FLOAT, tex->head);
        break;
    }

    switch (info.source.y) {
    case NV3D_TEXHEAD_IN_A:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _Y_SOURCE,
                           _IN_A, tex->head);
        break;
    case NV3D_TEXHEAD_IN_R:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _Y_SOURCE,
                           _IN_R, tex->head);
        break;
    case NV3D_TEXHEAD_IN_G:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _Y_SOURCE,
                           _IN_G, tex->head);
        break;
    case NV3D_TEXHEAD_IN_B:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _Y_SOURCE,
                           _IN_B, tex->head);
        break;
    case NV3D_TEXHEAD_IN_ZERO:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _Y_SOURCE,
                           _IN_ZERO, tex->head);
        break;
    case NV3D_TEXHEAD_IN_ONE_FLOAT:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _Y_SOURCE,
                           _IN_ONE_FLOAT, tex->head);
        break;
    }

    switch (info.source.z) {
    case NV3D_TEXHEAD_IN_A:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _Z_SOURCE,
                           _IN_A, tex->head);
        break;
    case NV3D_TEXHEAD_IN_R:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _Z_SOURCE,
                           _IN_R, tex->head);
        break;
    case NV3D_TEXHEAD_IN_G:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _Z_SOURCE,
                           _IN_G, tex->head);
        break;
    case NV3D_TEXHEAD_IN_B:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _Z_SOURCE,
                           _IN_B, tex->head);
        break;
    case NV3D_TEXHEAD_IN_ZERO:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _Z_SOURCE,
                           _IN_ZERO, tex->head);
        break;
    case NV3D_TEXHEAD_IN_ONE_FLOAT:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _Z_SOURCE,
                           _IN_ONE_FLOAT, tex->head);
        break;
    }

    switch (info.source.w) {
    case NV3D_TEXHEAD_IN_A:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _W_SOURCE,
                           _IN_A, tex->head);
        break;
    case NV3D_TEXHEAD_IN_R:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _W_SOURCE,
                           _IN_R, tex->head);
        break;
    case NV3D_TEXHEAD_IN_G:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _W_SOURCE,
                           _IN_G, tex->head);
        break;
    case NV3D_TEXHEAD_IN_B:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _W_SOURCE,
                           _IN_B, tex->head);
        break;
    case NV3D_TEXHEAD_IN_ZERO:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _W_SOURCE,
                           _IN_ZERO, tex->head);
        break;
    case NV3D_TEXHEAD_IN_ONE_FLOAT:
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _W_SOURCE,
                           _IN_ONE_FLOAT, tex->head);
        break;
    }

    // Default to edge clamping.  Our GPU seems to support wrapping
    // even with non-normalized coordinates.
    tex->samp[0] =
        NV3D_C(CB97, TEXSAMP0, ADDRESS_U, CLAMP_TO_EDGE) |
        NV3D_C(CB97, TEXSAMP0, ADDRESS_V, CLAMP_TO_EDGE) |
        NV3D_C(CB97, TEXSAMP0, ADDRESS_P, CLAMP_TO_EDGE);

    if (info.texType == NV3D_TEX_TYPE_ONE_D_BUFFER) {
        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_1DRT, _ADDRESS_BITS31TO0,
                           NvU64_LO32(info.offset), tex->head);

        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_1DRT, _HEADER_VERSION,
                           _SELECT_ONE_D_RAW_TYPED, tex->head);
        FLD_SET_DRF_NUM_MW(CB97_, TEXHEAD_V2_1DRT, _ADDRESS_BITS63TO32,
                           NvU64_HI32(info.offset), tex->head);

        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_1DRT, _WIDTH_MINUS_ONE,
                           info.width - 1, tex->head);
    } else if (info.texType == NV3D_TEX_TYPE_TWO_D_PITCH) {
        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_PITCH, _ADDRESS_BITS31TO5,
                           info.offset >> 5, tex->head);

        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_PITCH, _HEADER_VERSION,
                           _SELECT_PITCH_V2, tex->head);
        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_PITCH, _ADDRESS_BITS56TO32,
                           NvU64_HI32(info.offset), tex->head);

        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_PITCH, _PITCH_BITS21TO5,
                           NvU32_LO16(info.pitch >> 5), tex->head);

        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_PITCH, _TEXTURE_TYPE,
                           _TWO_D_NO_MIPMAP, tex->head);
        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_PITCH, _WIDTH_MINUS_ONE,
                           info.width - 1, tex->head);
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_PITCH, _BORDER_SOURCE,
                           _BORDER_COLOR, tex->head);

        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_PITCH, _HEIGHT_MINUS_ONE,
                           info.height - 1, tex->head);
        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_PITCH, _NORMALIZED_COORDS,
                           info.normalizedCoords, tex->head);
    } else {
        if (info.texType == NV3D_TEX_TYPE_ONE_D) {
            FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _TEXTURE_TYPE,
                               _ONE_D, tex->head);
        } else if (info.texType == NV3D_TEX_TYPE_TWO_D_BLOCKLINEAR) {
            FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _TEXTURE_TYPE,
                               _TWO_D_NO_MIPMAP, tex->head);
        }
        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_BL, _ADDRESS_BITS31TO9,
                           info.offset >> 9, tex->head);

        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _HEADER_VERSION,
                           _SELECT_BLOCKLINEAR_V2, tex->head);
        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_BL, _ADDRESS_BITS56TO32,
                           NvU64_HI32(info.offset), tex->head);

        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_BL, _GOBS_PER_BLOCK_WIDTH,
                           info.log2GobsPerBlock.x, tex->head);
        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_BL, _GOBS_PER_BLOCK_HEIGHT,
                           info.log2GobsPerBlock.y, tex->head);
        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_BL, _GOBS_PER_BLOCK_DEPTH,
                           info.log2GobsPerBlock.z, tex->head);

        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_BL, _WIDTH_MINUS_ONE,
                           info.width - 1, tex->head);
        FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _BORDER_SOURCE,
                           _BORDER_COLOR, tex->head);

        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_BL, _HEIGHT_MINUS_ONE,
                           info.height - 1, tex->head);
        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_BL, _DEPTH_MINUS_ONE,
                           0, tex->head);
        FLD_SET_DRF_NUM_MW(CB97, _TEXHEAD_V2_BL, _NORMALIZED_COORDS,
                           info.normalizedCoords, tex->head);
    }

    switch (info.repeatType) {
        case NV3D_TEXHEAD_REPEAT_TYPE_NORMAL:
            tex->samp[0] = NV3D_C(CB97, TEXSAMP0, ADDRESS_U, WRAP) |
                           NV3D_C(CB97, TEXSAMP0, ADDRESS_V, WRAP);
            break;
        case NV3D_TEXHEAD_REPEAT_TYPE_PAD:
            tex->samp[0] = NV3D_C(CB97, TEXSAMP0, ADDRESS_U, CLAMP_TO_EDGE) |
                           NV3D_C(CB97, TEXSAMP0, ADDRESS_V, CLAMP_TO_EDGE);
            break;
        case NV3D_TEXHEAD_REPEAT_TYPE_REFLECT:
            tex->samp[0] = NV3D_C(CB97, TEXSAMP0, ADDRESS_U, MIRROR) |
                           NV3D_C(CB97, TEXSAMP0, ADDRESS_V, MIRROR);
            break;
        case NV3D_TEXHEAD_REPEAT_TYPE_NONE:
            tex->samp[0] = NV3D_C(CB97, TEXSAMP0, ADDRESS_U, BORDER) |
                           NV3D_C(CB97, TEXSAMP0, ADDRESS_V, BORDER);
            break;
    }

    switch (info.filtering) {
        case NV3D_TEXHEAD_FILTER_TYPE_NEAREST:
            tex->samp[1] = NV3D_C(CB97, TEXSAMP1, MAG_FILTER, MAG_POINT) |
                       NV3D_C(CB97, TEXSAMP1, MIN_FILTER, MIN_POINT) |
                       NV3D_C(CB97, TEXSAMP1, MIP_FILTER, MIP_NONE);
            break;

        case NV3D_TEXHEAD_FILTER_TYPE_LINEAR:
            tex->samp[1] = NV3D_C(CB97, TEXSAMP1, MAG_FILTER, MAG_LINEAR) |
                       NV3D_C(CB97, TEXSAMP1, MIN_FILTER, MIN_LINEAR) |
                       NV3D_C(CB97, TEXSAMP1, MIP_FILTER, MIP_NONE);
            break;

        case NV3D_TEXHEAD_FILTER_TYPE_ANISO_2X:
            tex->samp[0] |= NV3D_C(CB97, TEXSAMP0, MAX_ANISOTROPY, ANISO_2_TO_1);
            tex->samp[1] = NV3D_C(CB97, TEXSAMP1, MAG_FILTER, MAG_LINEAR) |
                           NV3D_C(CB97, TEXSAMP1, MIN_FILTER, MIN_ANISO) |
                           NV3D_C(CB97, TEXSAMP1, MIP_FILTER, MIP_NONE);
            FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _MAX_ANISOTROPY,
                               _ANISO_2_TO_1, tex->head);
            FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _ANISO_FINE_SPREAD_MODIFIER,
                               _SPREAD_MODIFIER_CONST_TWO, tex->head);

            break;

        case NV3D_TEXHEAD_FILTER_TYPE_ANISO_4X:
            tex->samp[0] |= NV3D_C(CB97, TEXSAMP0, MAX_ANISOTROPY, ANISO_4_TO_1);
            tex->samp[1] = NV3D_C(CB97, TEXSAMP1, MAG_FILTER, MAG_LINEAR) |
                           NV3D_C(CB97, TEXSAMP1, MIN_FILTER, MIN_ANISO) |
                           NV3D_C(CB97, TEXSAMP1, MIP_FILTER, MIP_NONE);
            FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _MAX_ANISOTROPY,
                               _ANISO_4_TO_1, tex->head);
            FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _ANISO_FINE_SPREAD_MODIFIER,
                               _SPREAD_MODIFIER_CONST_TWO, tex->head);
            break;

        case NV3D_TEXHEAD_FILTER_TYPE_ANISO_8X:
            tex->samp[0] |= NV3D_C(CB97, TEXSAMP0, MAX_ANISOTROPY, ANISO_8_TO_1);
            tex->samp[1] = NV3D_C(CB97, TEXSAMP1, MAG_FILTER, MAG_LINEAR) |
                           NV3D_C(CB97, TEXSAMP1, MIN_FILTER, MIN_ANISO) |
                           NV3D_C(CB97, TEXSAMP1, MIP_FILTER, MIP_NONE);
            FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _MAX_ANISOTROPY,
                               _ANISO_8_TO_1, tex->head);
            FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _ANISO_FINE_SPREAD_MODIFIER,
                               _SPREAD_MODIFIER_CONST_TWO, tex->head);

            break;

        case NV3D_TEXHEAD_FILTER_TYPE_ANISO_16X:
            tex->samp[0] |=  NV3D_C(CB97, TEXSAMP0, MAX_ANISOTROPY, ANISO_16_TO_1);
            tex->samp[1] = NV3D_C(CB97, TEXSAMP1, MAG_FILTER, MAG_LINEAR) |
                           NV3D_C(CB97, TEXSAMP1, MIN_FILTER, MIN_ANISO) |
                           NV3D_C(CB97, TEXSAMP1, MIP_FILTER, MIP_NONE);
            FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _MAX_ANISOTROPY,
                               _ANISO_16_TO_1, tex->head);
            FLD_SET_DRF_DEF_MW(CB97, _TEXHEAD_V2_BL, _ANISO_FINE_SPREAD_MODIFIER,
                               _SPREAD_MODIFIER_CONST_TWO, tex->head);
            break;

    }
}
