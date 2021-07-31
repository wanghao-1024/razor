/*-
* Copyright (c) 2017-2018 Razor, Inc.
*   All rights reserved.
*
* See the file LICENSE for redistribution information.
*/

#ifndef __echo_h265_decoder_h_
#define __echo_h265_decoder_h_

#include "codec_common.h"

/*H265������*/
class H265Decoder : public VideoDecoder
{
public:
    H265Decoder();
    virtual ~H265Decoder();

protected:
    void set_codec_id();
};

#endif


