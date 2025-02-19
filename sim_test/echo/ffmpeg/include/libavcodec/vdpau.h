/*
 * The Video Decode and Presentation API for UNIX (VDPAU) is used for
 * hardware-accelerated decoding of MPEG-1/2, H.264 and VC-1.
 *
 * Copyright (C) 2008 NVIDIA
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVCODEC_VDPAU_H
#define AVCODEC_VDPAU_H

/**
 * @file
 * @ingroup lavc_codec_hwaccel_vdpau
 * Public libavcodec VDPAU header.
 */


/**
 * @defgroup lavc_codec_hwaccel_vdpau VDPAU Decoder and Renderer
 * @ingroup lavc_codec_hwaccel
 *
 * VDPAU hardware acceleration has two modules
 * - VDPAU decoding
 * - VDPAU presentation
 *
 * The VDPAU decoding module parses all headers using FFmpeg
 * parsing mechanisms and uses VDPAU for the actual decoding.
 *
 * As per the current implementation, the actual decoding
 * and rendering (API calls) are done as part of the VDPAU
 * presentation (vo_vdpau.c) module.
 *
 * @{
 */

#include <vdpau/vdpau.h>
#include <vdpau/vdpau_x11.h>
#include "libavutil/avconfig.h"
#include "libavutil/attributes.h"

#include "avcodec.h"
#include "version.h"

#if FF_API_BUFS_VDPAU
union AVVDPAUPictureInfo
{
    VdpPictureInfoH264        h264;
    VdpPictureInfoMPEG1Or2    mpeg;
    VdpPictureInfoVC1          vc1;
    VdpPictureInfoMPEG4Part2 mpeg4;
};
#endif

struct AVCodecContext;
struct AVFrame;

typedef int (*AVVDPAU_Render2)(struct AVCodecContext*, struct AVFrame*,
                               const VdpPictureInfo*, uint32_t,
                               const VdpBitstreamBuffer*);

/**
 * This structure is used to share data between the libavcodec library and
 * the client video application.
 * The user shall allocate the structure via the av_alloc_vdpau_hwaccel
 * function and make it available as
 * AVCodecContext.hwaccel_context. Members can be set by the user once
 * during initialization or through each AVCodecContext.get_buffer()
 * function call. In any case, they must be valid prior to calling
 * decoding functions.
 *
 * The size of this structure is not a part of the public ABI and must not
 * be used outside of libavcodec. Use av_vdpau_alloc_context() to allocate an
 * AVVDPAUContext.
 */
typedef struct AVVDPAUContext
{
    /**
     * VDPAU decoder handle
     *
     * Set by user.
     */
    VdpDecoder decoder;

    /**
     * VDPAU decoder render callback
     *
     * Set by the user.
     */
    VdpDecoderRender* render;

#if FF_API_BUFS_VDPAU
    /**
     * VDPAU picture information
     *
     * Set by libavcodec.
     */
    attribute_deprecated
    union AVVDPAUPictureInfo info;

    /**
     * Allocated size of the bitstream_buffers table.
     *
     * Set by libavcodec.
     */
    attribute_deprecated
    int bitstream_buffers_allocated;

    /**
     * Useful bitstream buffers in the bitstream buffers table.
     *
     * Set by libavcodec.
     */
    attribute_deprecated
    int bitstream_buffers_used;

    /**
      * Table of bitstream buffers.
      * The user is responsible for freeing this buffer using av_freep().
      *
      * Set by libavcodec.
      */
    attribute_deprecated
    VdpBitstreamBuffer* bitstream_buffers;
#endif
    AVVDPAU_Render2 render2;
} AVVDPAUContext;

/**
 * @brief allocation function for AVVDPAUContext
 *
 * Allows extending the struct without breaking API/ABI
 */
AVVDPAUContext* av_alloc_vdpaucontext(void);

AVVDPAU_Render2 av_vdpau_hwaccel_get_render2(const AVVDPAUContext*);
void av_vdpau_hwaccel_set_render2(AVVDPAUContext*, AVVDPAU_Render2);

/**
 * Associate a VDPAU device with a codec context for hardware acceleration.
 * This function is meant to be called from the get_format() codec callback,
 * or earlier. It can also be called after avcodec_flush_buffers() to change
 * the underlying VDPAU device mid-stream (e.g. to recover from non-transparent
 * display preemption).
 *
 * @note get_format() must return AV_PIX_FMT_VDPAU if this function completes
 * successfully.
 *
 * @param avctx decoding context whose get_format() callback is invoked
 * @param device VDPAU device handle to use for hardware acceleration
 * @param get_proc_address VDPAU device driver
 * @param flags zero of more OR'd AV_HWACCEL_FLAG_* flags
 *
 * @return 0 on success, an AVERROR code on failure.
 */
int av_vdpau_bind_context(AVCodecContext* avctx, VdpDevice device,
                          VdpGetProcAddress* get_proc_address, unsigned flags);

/**
 * Gets the parameters to create an adequate VDPAU video surface for the codec
 * context using VDPAU hardware decoding acceleration.
 *
 * @note Behavior is undefined if the context was not successfully bound to a
 * VDPAU device using av_vdpau_bind_context().
 *
 * @param avctx the codec context being used for decoding the stream
 * @param type storage space for the VDPAU video surface chroma type
 *              (or NULL to ignore)
 * @param width storage space for the VDPAU video surface pixel width
 *              (or NULL to ignore)
 * @param height storage space for the VDPAU video surface pixel height
 *              (or NULL to ignore)
 *
 * @return 0 on success, a negative AVERROR code on failure.
 */
int av_vdpau_get_surface_parameters(AVCodecContext* avctx, VdpChromaType* type,
                                    uint32_t* width, uint32_t* height);

/**
 * Allocate an AVVDPAUContext.
 *
 * @return Newly-allocated AVVDPAUContext or NULL on failure.
 */
AVVDPAUContext* av_vdpau_alloc_context(void);

/**
 * Get a decoder profile that should be used for initializing a VDPAU decoder.
 * Should be called from the AVCodecContext.get_format() callback.
 *
 * @param avctx the codec context being used for decoding the stream
 * @param profile a pointer into which the result will be written on success.
 *                The contents of profile are undefined if this function returns
 *                an error.
 *
 * @return 0 on success (non-negative), a negative AVERROR on failure.
 */
int av_vdpau_get_profile(AVCodecContext* avctx, VdpDecoderProfile* profile);

#if FF_API_CAP_VDPAU
/** @brief The videoSurface is used for rendering. */
#define FF_VDPAU_STATE_USED_FOR_RENDER 1

/**
 * @brief The videoSurface is needed for reference/prediction.
 * The codec manipulates this.
 */
#define FF_VDPAU_STATE_USED_FOR_REFERENCE 2

/**
 * @brief This structure is used as a callback between the FFmpeg
 * decoder (vd_) and presentation (vo_) module.
 * This is used for defining a video frame containing surface,
 * picture parameter, bitstream information etc which are passed
 * between the FFmpeg decoder and its clients.
 */
struct vdpau_render_state
{
    VdpVideoSurface surface; ///< Used as rendered surface, never changed.

    int state; ///< Holds FF_VDPAU_STATE_* values.

#if AV_HAVE_INCOMPATIBLE_LIBAV_ABI
    /** picture parameter information for all supported codecs */
    union AVVDPAUPictureInfo info;
#endif

    /** Describe size/location of the compressed video data.
        Set to 0 when freeing bitstream_buffers. */
    int bitstream_buffers_allocated;
    int bitstream_buffers_used;
    /** The user is responsible for freeing this buffer using av_freep(). */
    VdpBitstreamBuffer* bitstream_buffers;

#if !AV_HAVE_INCOMPATIBLE_LIBAV_ABI
    /** picture parameter information for all supported codecs */
    union AVVDPAUPictureInfo info;
#endif
};
#endif

/* @}*/

#endif /* AVCODEC_VDPAU_H */
