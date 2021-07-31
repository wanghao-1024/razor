/*-
* Copyright (c) 2017-2018 Razor, Inc.
*   All rights reserved.
*
* See the file LICENSE for redistribution information.
*/

/*һ��nack������Ĵ���������*/
typedef struct
{
    uint32_t*       buckets;
    uint32_t        index;
    int64_t         oldest_ts;

    int             wnd_size;           /*ͳ�Ƶ�ʱ�䴰*/
    uint32_t        wnd_bytes;
    uint32_t        threshold;          /*�����Է��͵��ֽ���*/
} sim_sender_limiter_t;

struct __sim_sender
{
    int                         actived;
    uint32_t                    base_packet_id;         /*���ܶ˱����Ѿ����յ������������ID*/

    uint32_t                    packet_id_seed;         /*��Ƶ����ID*/
    uint32_t                    send_id_seed;           /*��CCģ������ķ���ID*/
    uint32_t                    frame_id_seed;
    uint32_t                    transport_seq_seed;

    int64_t                     first_ts;           /*��һ֡��ʼʱ���*/

    skiplist_t*                 segs_cache;         /*��Ƶ��Ƭcache*/
    skiplist_t*                 fecs_cache;         /*fec���ʹ���*/
    skiplist_t*                 ack_cache;          /*ack�ش���Ƭcache*/

    razor_sender_t*             cc;                 /*ӵ�����ƶ���*/

    sim_session_t*              s;

    flex_fec_sender_t*          flex;               /*flex FEC����*/
    base_list_t*                out_fecs;

    size_t                      splits_size;
    uint16_t*                   splits;
};




