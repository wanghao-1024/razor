/*
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

#ifndef AVCODEC_OLD_CODEC_IDS_H
#define AVCODEC_OLD_CODEC_IDS_H

/*
 * This header exists to prevent new codec IDs from being accidentally added to
 * the deprecated list.
 * Do not include it directly. It will be removed on next major bump
 *
 * Do not add new items to this list. Use the AVCodecID enum instead.
 */

CODEC_ID_NONE = AV_CODEC_ID_NONE,

/* video codecs */
CODEC_ID_MPEG1VIDEO,
CODEC_ID_MPEG2VIDEO, ///< preferred ID for MPEG-1/2 video decoding
#if FF_API_XVMC
CODEC_ID_MPEG2VIDEO_XVMC,
#endif
CODEC_ID_H261,
CODEC_ID_H263,
CODEC_ID_RV10,
CODEC_ID_RV20,
CODEC_ID_MJPEG,
CODEC_ID_MJPEGB,
CODEC_ID_LJPEG,
CODEC_ID_SP5X,
CODEC_ID_JPEGLS,
CODEC_ID_MPEG4,
CODEC_ID_RAWVIDEO,
CODEC_ID_MSMPEG4V1,
CODEC_ID_MSMPEG4V2,
CODEC_ID_MSMPEG4V3,
CODEC_ID_WMV1,
CODEC_ID_WMV2,
CODEC_ID_H263P,
CODEC_ID_H263I,
CODEC_ID_FLV1,
CODEC_ID_SVQ1,
CODEC_ID_SVQ3,
CODEC_ID_DVVIDEO,
CODEC_ID_HUFFYUV,
CODEC_ID_CYUV,
CODEC_ID_H264,
CODEC_ID_INDEO3,
CODEC_ID_VP3,
CODEC_ID_THEORA,
CODEC_ID_ASV1,
CODEC_ID_ASV2,
CODEC_ID_FFV1,
CODEC_ID_4XM,
CODEC_ID_VCR1,
CODEC_ID_CLJR,
CODEC_ID_MDEC,
CODEC_ID_ROQ,
CODEC_ID_INTERPLAY_VIDEO,
CODEC_ID_XAN_WC3,
CODEC_ID_XAN_WC4,
CODEC_ID_RPZA,
CODEC_ID_CINEPAK,
CODEC_ID_WS_VQA,
CODEC_ID_MSRLE,
CODEC_ID_MSVIDEO1,
CODEC_ID_IDCIN,
CODEC_ID_8BPS,
CODEC_ID_SMC,
CODEC_ID_FLIC,
CODEC_ID_TRUEMOTION1,
CODEC_ID_VMDVIDEO,
CODEC_ID_MSZH,
CODEC_ID_ZLIB,
CODEC_ID_QTRLE,
CODEC_ID_TSCC,
CODEC_ID_ULTI,
CODEC_ID_QDRAW,
CODEC_ID_VIXL,
CODEC_ID_QPEG,
CODEC_ID_PNG,
CODEC_ID_PPM,
CODEC_ID_PBM,
CODEC_ID_PGM,
CODEC_ID_PGMYUV,
CODEC_ID_PAM,
CODEC_ID_FFVHUFF,
CODEC_ID_RV30,
CODEC_ID_RV40,
CODEC_ID_VC1,
CODEC_ID_WMV3,
CODEC_ID_LOCO,
CODEC_ID_WNV1,
CODEC_ID_AASC,
CODEC_ID_INDEO2,
CODEC_ID_FRAPS,
CODEC_ID_TRUEMOTION2,
CODEC_ID_BMP,
CODEC_ID_CSCD,
CODEC_ID_MMVIDEO,
CODEC_ID_ZMBV,
CODEC_ID_AVS,
CODEC_ID_SMACKVIDEO,
CODEC_ID_NUV,
CODEC_ID_KMVC,
CODEC_ID_FLASHSV,
CODEC_ID_CAVS,
CODEC_ID_JPEG2000,
CODEC_ID_VMNC,
CODEC_ID_VP5,
CODEC_ID_VP6,
CODEC_ID_VP6F,
CODEC_ID_TARGA,
CODEC_ID_DSICINVIDEO,
CODEC_ID_TIERTEXSEQVIDEO,
CODEC_ID_TIFF,
CODEC_ID_GIF,
CODEC_ID_DXA,
CODEC_ID_DNXHD,
CODEC_ID_THP,
CODEC_ID_SGI,
CODEC_ID_C93,
CODEC_ID_BETHSOFTVID,
CODEC_ID_PTX,
CODEC_ID_TXD,
CODEC_ID_VP6A,
CODEC_ID_AMV,
CODEC_ID_VB,
CODEC_ID_PCX,
CODEC_ID_SUNRAST,
CODEC_ID_INDEO4,
CODEC_ID_INDEO5,
CODEC_ID_MIMIC,
CODEC_ID_RL2,
CODEC_ID_ESCAPE124,
CODEC_ID_DIRAC,
CODEC_ID_BFI,
CODEC_ID_CMV,
CODEC_ID_MOTIONPIXELS,
CODEC_ID_TGV,
CODEC_ID_TGQ,
CODEC_ID_TQI,
CODEC_ID_AURA,
CODEC_ID_AURA2,
CODEC_ID_V210X,
CODEC_ID_TMV,
CODEC_ID_V210,
CODEC_ID_DPX,
CODEC_ID_MAD,
CODEC_ID_FRWU,
CODEC_ID_FLASHSV2,
CODEC_ID_CDGRAPHICS,
CODEC_ID_R210,
CODEC_ID_ANM,
CODEC_ID_BINKVIDEO,
CODEC_ID_IFF_ILBM,
CODEC_ID_IFF_BYTERUN1,
CODEC_ID_KGV1,
CODEC_ID_YOP,
CODEC_ID_VP8,
CODEC_ID_PICTOR,
CODEC_ID_ANSI,
CODEC_ID_A64_MULTI,
CODEC_ID_A64_MULTI5,
CODEC_ID_R10K,
CODEC_ID_MXPEG,
CODEC_ID_LAGARITH,
CODEC_ID_PRORES,
CODEC_ID_JV,
CODEC_ID_DFA,
CODEC_ID_WMV3IMAGE,
CODEC_ID_VC1IMAGE,
CODEC_ID_UTVIDEO,
CODEC_ID_BMV_VIDEO,
CODEC_ID_VBLE,
CODEC_ID_DXTORY,
CODEC_ID_V410,
CODEC_ID_XWD,
CODEC_ID_CDXL,
CODEC_ID_XBM,
CODEC_ID_ZEROCODEC,
CODEC_ID_MSS1,
CODEC_ID_MSA1,
CODEC_ID_TSCC2,
CODEC_ID_MTS2,
CODEC_ID_CLLC,
CODEC_ID_Y41P       = MKBETAG('Y','4','1','P'),
CODEC_ID_ESCAPE130  = MKBETAG('E','1','3','0'),
CODEC_ID_EXR        = MKBETAG('0','E','X','R'),
CODEC_ID_AVRP       = MKBETAG('A','V','R','P'),

CODEC_ID_G2M        = MKBETAG( 0,'G','2','M'),
CODEC_ID_AVUI       = MKBETAG('A','V','U','I'),
CODEC_ID_AYUV       = MKBETAG('A','Y','U','V'),
CODEC_ID_V308       = MKBETAG('V','3','0','8'),
CODEC_ID_V408       = MKBETAG('V','4','0','8'),
CODEC_ID_YUV4       = MKBETAG('Y','U','V','4'),
CODEC_ID_SANM       = MKBETAG('S','A','N','M'),
CODEC_ID_PAF_VIDEO  = MKBETAG('P','A','F','V'),
CODEC_ID_SNOW       = AV_CODEC_ID_SNOW,

/* various PCM "codecs" */
CODEC_ID_FIRST_AUDIO = 0x10000,     ///< A dummy id pointing at the start of audio codecs
CODEC_ID_PCM_S16LE = 0x10000,
CODEC_ID_PCM_S16BE,
CODEC_ID_PCM_U16LE,
CODEC_ID_PCM_U16BE,
CODEC_ID_PCM_S8,
CODEC_ID_PCM_U8,
CODEC_ID_PCM_MULAW,
CODEC_ID_PCM_ALAW,
CODEC_ID_PCM_S32LE,
CODEC_ID_PCM_S32BE,
CODEC_ID_PCM_U32LE,
CODEC_ID_PCM_U32BE,
CODEC_ID_PCM_S24LE,
CODEC_ID_PCM_S24BE,
CODEC_ID_PCM_U24LE,
CODEC_ID_PCM_U24BE,
CODEC_ID_PCM_S24DAUD,
CODEC_ID_PCM_ZORK,
CODEC_ID_PCM_S16LE_PLANAR,
CODEC_ID_PCM_DVD,
CODEC_ID_PCM_F32BE,
CODEC_ID_PCM_F32LE,
CODEC_ID_PCM_F64BE,
CODEC_ID_PCM_F64LE,
CODEC_ID_PCM_BLURAY,
CODEC_ID_PCM_LXF,
CODEC_ID_S302M,
CODEC_ID_PCM_S8_PLANAR,

/* various ADPCM codecs */
CODEC_ID_ADPCM_IMA_QT = 0x11000,
CODEC_ID_ADPCM_IMA_WAV,
CODEC_ID_ADPCM_IMA_DK3,
CODEC_ID_ADPCM_IMA_DK4,
CODEC_ID_ADPCM_IMA_WS,
CODEC_ID_ADPCM_IMA_SMJPEG,
CODEC_ID_ADPCM_MS,
CODEC_ID_ADPCM_4XM,
CODEC_ID_ADPCM_XA,
CODEC_ID_ADPCM_ADX,
CODEC_ID_ADPCM_EA,
CODEC_ID_ADPCM_G726,
CODEC_ID_ADPCM_CT,
CODEC_ID_ADPCM_SWF,
CODEC_ID_ADPCM_YAMAHA,
CODEC_ID_ADPCM_SBPRO_4,
CODEC_ID_ADPCM_SBPRO_3,
CODEC_ID_ADPCM_SBPRO_2,
CODEC_ID_ADPCM_THP,
CODEC_ID_ADPCM_IMA_AMV,
CODEC_ID_ADPCM_EA_R1,
CODEC_ID_ADPCM_EA_R3,
CODEC_ID_ADPCM_EA_R2,
CODEC_ID_ADPCM_IMA_EA_SEAD,
CODEC_ID_ADPCM_IMA_EA_EACS,
CODEC_ID_ADPCM_EA_XAS,
CODEC_ID_ADPCM_EA_MAXIS_XA,
CODEC_ID_ADPCM_IMA_ISS,
CODEC_ID_ADPCM_G722,
CODEC_ID_ADPCM_IMA_APC,
CODEC_ID_VIMA       = MKBETAG('V','I','M','A'),

/* AMR */
CODEC_ID_AMR_NB = 0x12000,
CODEC_ID_AMR_WB,

/* RealAudio codecs*/
CODEC_ID_RA_144 = 0x13000,
CODEC_ID_RA_288,

/* various DPCM codecs */
CODEC_ID_ROQ_DPCM = 0x14000,
CODEC_ID_INTERPLAY_DPCM,
CODEC_ID_XAN_DPCM,
CODEC_ID_SOL_DPCM,

/* audio codecs */
CODEC_ID_MP2 = 0x15000,
CODEC_ID_MP3, ///< preferred ID for decoding MPEG audio layer 1, 2 or 3
CODEC_ID_AAC,
CODEC_ID_AC3,
CODEC_ID_DTS,
CODEC_ID_VORBIS,
CODEC_ID_DVAUDIO,
CODEC_ID_WMAV1,
CODEC_ID_WMAV2,
CODEC_ID_MACE3,
CODEC_ID_MACE6,
CODEC_ID_VMDAUDIO,
CODEC_ID_FLAC,
CODEC_ID_MP3ADU,
CODEC_ID_MP3ON4,
CODEC_ID_SHORTEN,
CODEC_ID_ALAC,
CODEC_ID_WESTWOOD_SND1,
CODEC_ID_GSM, ///< as in Berlin toast format
CODEC_ID_QDM2,
CODEC_ID_COOK,
CODEC_ID_TRUESPEECH,
CODEC_ID_TTA,
CODEC_ID_SMACKAUDIO,
CODEC_ID_QCELP,
CODEC_ID_WAVPACK,
CODEC_ID_DSICINAUDIO,
CODEC_ID_IMC,
CODEC_ID_MUSEPACK7,
CODEC_ID_MLP,
CODEC_ID_GSM_MS, /* as found in WAV */
CODEC_ID_ATRAC3,
CODEC_ID_VOXWARE,
CODEC_ID_APE,
CODEC_ID_NELLYMOSER,
CODEC_ID_MUSEPACK8,
CODEC_ID_SPEEX,
CODEC_ID_WMAVOICE,
CODEC_ID_WMAPRO,
CODEC_ID_WMALOSSLESS,
CODEC_ID_ATRAC3P,
CODEC_ID_EAC3,
CODEC_ID_SIPR,
CODEC_ID_MP1,
CODEC_ID_TWINVQ,
CODEC_ID_TRUEHD,
CODEC_ID_MP4ALS,
CODEC_ID_ATRAC1,
CODEC_ID_BINKAUDIO_RDFT,
CODEC_ID_BINKAUDIO_DCT,
CODEC_ID_AAC_LATM,
CODEC_ID_QDMC,
CODEC_ID_CELT,
CODEC_ID_G723_1,
CODEC_ID_G729,
CODEC_ID_8SVX_EXP,
CODEC_ID_8SVX_FIB,
CODEC_ID_BMV_AUDIO,
CODEC_ID_RALF,
CODEC_ID_IAC,
CODEC_ID_ILBC,
CODEC_ID_FFWAVESYNTH = MKBETAG('F','F','W','S'),
CODEC_ID_SONIC       = MKBETAG('S','O','N','C'),
CODEC_ID_SONIC_LS    = MKBETAG('S','O','N','L'),
CODEC_ID_PAF_AUDIO   = MKBETAG('P','A','F','A'),
CODEC_ID_OPUS        = MKBETAG('O','P','U','S'),

/* subtitle codecs */
CODEC_ID_FIRST_SUBTITLE = 0x17000,          ///< A dummy ID pointing at the start of subtitle codecs.
CODEC_ID_DVD_SUBTITLE = 0x17000,
CODEC_ID_DVB_SUBTITLE,
CODEC_ID_TEXT,  ///< raw UTF-8 text
CODEC_ID_XSUB,
CODEC_ID_SSA,
CODEC_ID_MOV_TEXT,
CODEC_ID_HDMV_PGS_SUBTITLE,
CODEC_ID_DVB_TELETEXT,
CODEC_ID_SRT,
CODEC_ID_MICRODVD   = MKBETAG('m','D','V','D'),
CODEC_ID_EIA_608    = MKBETAG('c','6','0','8'),
CODEC_ID_JACOSUB    = MKBETAG('J','S','U','B'),
CODEC_ID_SAMI       = MKBETAG('S','A','M','I'),
CODEC_ID_REALTEXT   = MKBETAG('R','T','X','T'),
CODEC_ID_SUBVIEWER  = MKBETAG('S','u','b','V'),

/* other specific kind of codecs (generally used for attachments) */
CODEC_ID_FIRST_UNKNOWN = 0x18000,           ///< A dummy ID pointing at the start of various fake codecs.
CODEC_ID_TTF = 0x18000,
CODEC_ID_BINTEXT    = MKBETAG('B','T','X','T'),
CODEC_ID_XBIN       = MKBETAG('X','B','I','N'),
CODEC_ID_IDF        = MKBETAG( 0,'I','D','F'),
CODEC_ID_OTF        = MKBETAG( 0,'O','T','F'),

CODEC_ID_PROBE = 0x19000, ///< codec_id is not known (like CODEC_ID_NONE) but lavf should attempt to identify it

CODEC_ID_MPEG2TS = 0x20000, /**< _FAKE_ codec to indicate a raw MPEG-2 TS
                                * stream (only used by libavformat) */
                   CODEC_ID_MPEG4SYSTEMS = 0x20001, /**< _FAKE_ codec to indicate a MPEG-4 Systems
                                * stream (only used by libavformat) */
                           CODEC_ID_FFMETADATA = 0x21000,   ///< Dummy codec for streams containing only metadata information.

#endif /* AVCODEC_OLD_CODEC_IDS_H */
