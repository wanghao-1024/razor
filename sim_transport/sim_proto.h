/*-
* Copyright (c) 2017-2018 Razor, Inc.
*   All rights reserved.
*
* See the file LICENSE for redistribution information.
*/

#ifndef __sim_proto_h_001__
#define __sim_proto_h_001__

#include "cf_platform.h"
#include "cf_stream.h"

/*����ģ�⴫���Э�鶨�壬����ֻ�Ǽ򵥵ĵ�Ե�ͨ��ģ�⣬���漰·���Ż������Ӱ�ȫ�ԣ���������������ʹ��*/

enum
{
    MIN_MSG_ID  =   0x10,

    SIM_CONNECT,            /*���ӽ��ն�����*/
    SIM_CONNECT_ACK,        /*��Ӧ*/

    SIM_DISCONNECT,
    SIM_DISCONNECT_ACK,

    SIM_PING,
    SIM_PONG,

    SIM_SEG,
    SIM_SEG_ACK,
    SIM_FEEDBACK,
    SIM_FIR,                /*����ؼ�֡�ش�*/
    SIM_PAD,                /*padding����*/
    SIM_FEC,                /*FEC����*/

    MAX_MSG_ID
};

#define protocol_ver            0x01

typedef struct
{
    uint8_t     ver;            /*Э��汾��Ĭ��Ϊ0x01*/
    uint8_t     mid;            /*��ϢID*/
    uint32_t    uid;            /*��Ϣ����ID*/
} sim_header_t;

#define INIT_SIM_HEADER(h, msg_id, userid) \
    h.ver = protocol_ver;   \
    h.mid = (msg_id);       \
    h.uid = (userid)

#define SIM_HEADER_SIZE         6
#define SIM_VIDEO_SIZE          1000
#define SIM_TOKEN_SIZE          128
#define NACK_NUM                20
#define ACK_NUM                 NACK_NUM
#define SIM_FEEDBACK_SIZE       1000
typedef struct
{
    uint32_t cid;                       /*Э�̵ĺ���ID��ÿ����һ�����ֵ,��disconnect����Ϣ����һ��*/
    uint16_t token_size;                /*token��һ����֤��Ϣ������������֤��ķ�ʽ��������֤*/
    uint8_t  token[SIM_TOKEN_SIZE];
    uint8_t  cc_type;                   /*ӵ����������*/
} sim_connect_t;

typedef struct
{
    uint32_t cid;
    uint32_t result;
} sim_connect_ack_t;

typedef struct
{
    uint32_t cid;
} sim_disconnect_t;

typedef sim_connect_ack_t sim_disconnect_ack_t;

typedef struct
{
    uint32_t    packet_id;              /*�����*/
    uint32_t    fid;                    /*֡���*/
    uint32_t    timestamp;              /*֡ʱ���*/
    uint16_t    index;                  /*֡�ְ����*/
    uint16_t    total;                  /*֡�ְ�����*/
    uint8_t     ftype;                  /*��Ƶ֡����*/
    uint8_t     payload_type;           /*����������*/

    uint8_t     remb;                   /*0��ʾ����remb, ������ʾ������*/
    uint16_t    fec_id;                 /*1��ʾ����FEC, ������ʾ������*/
    uint16_t    send_ts;                /*����ʱ�����֡����ʱ�̵�ʱ���*/
    uint16_t    transport_seq;          /*����ͨ����ţ�����Ǵ���ͨ��ÿ����һ�����ģ�����������1�������ط�����Ҳ������*/

    uint32_t    send_id;

    uint16_t    data_size;
    uint8_t     data[SIM_VIDEO_SIZE];
} sim_segment_t;

#define SIM_SEGMENT_HEADER_SIZE (SIM_HEADER_SIZE + 24)

typedef struct
{
    uint32_t    base_packet_id;         /*�����ն�ȷ���������İ�ID*/
    uint32_t    acked_packet_id;        /*����ȷ�ϵı������id,���ڼ���rtt*/
    /*�ش�������*/
    uint8_t     nack_num;
    uint16_t    nack[NACK_NUM];

    uint8_t     ack_num;
    uint16_t    acked[ACK_NUM];
} sim_segment_ack_t;

typedef struct
{
    int64_t ts;                         /*����ʱ��*/
} sim_ping_t;

typedef sim_ping_t sim_pong_t;

typedef struct
{
    uint32_t    base_packet_id;                     /*�����ն�ȷ���������İ�ID*/

    uint16_t    feedback_size;                      /*cc�еķ�����Ϣ,�ɽ��ն˵�ӵ�����ƶ������*/
    uint8_t     feedback[SIM_FEEDBACK_SIZE];
} sim_feedback_t;

typedef struct
{
    uint32_t    fir_seq;                            /*fir����ţ�ÿ�ν��ն˴�������ʱ����*/
} sim_fir_t;

#define PADDING_DATA_SIZE  500
typedef struct
{
    uint32_t    send_ts;                /*����ʱ�����֡����ʱ�̵�ʱ���*/
    uint16_t    transport_seq;          /*����ͨ����ţ�����Ǵ���ͨ��ÿ����һ�����ģ�����������1�������ط�����Ҳ������*/

    uint16_t    data_size;
    uint8_t     data[PADDING_DATA_SIZE];
} sim_pad_t;

typedef struct
{
    uint32_t    seq;
    uint32_t    fid;
    uint32_t    ts;
    uint16_t    index;                  /*֡�ְ����*/
    uint16_t    total;                  /*֡�ְ�����*/
    uint8_t     ftype;                  /*��Ƶ֡����*/
    uint8_t     payload_type;           /*����������*/
    uint16_t    size;                   /*���ݳ���*/
} sim_fec_meta_t;

typedef struct
{
    uint16_t        fec_id;                 /*fec����ID��������*/
    uint8_t         row;                    /*fec����*/
    uint8_t         col;                    /*fec����*/
    uint8_t         index;                  /*�ڲ���������,���ڻָ��к����ϵı���*/
    uint16_t        count;                  /*�����ڱ��ĸ���*/
    uint32_t        base_id;                /*��ʼ���ĵ�id*/

    uint32_t    send_ts;                    /*����ʱ�����֡����ʱ�̵�ʱ���*/
    uint16_t    transport_seq;              /*����ͨ����ţ�����Ǵ���ͨ��ÿ����һ�����ģ�����������1�������ط�����Ҳ������*/

    sim_fec_meta_t  fec_meta;               /*FECԪ����,���ڻָ�segment�е�Ԫ��Ϣ*/

    uint16_t        fec_data_size;          /*FEC���ݳ���*/
    uint8_t         fec_data[SIM_VIDEO_SIZE];/*FEC���ݿ�*/

} sim_fec_t;

void                            sim_encode_msg(bin_stream_t* strm, sim_header_t* header, void* body);
int                             sim_decode_header(bin_stream_t* strm, sim_header_t* header);
int                             sim_decode_msg(bin_stream_t* strm, sim_header_t* header, void* body);
const char*                     sim_get_msg_name(uint8_t msg_id);

#endif



