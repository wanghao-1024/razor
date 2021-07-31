#include "flex_fec_receiver.h"

#define k_default_cache_size 20

static void flex_free_segment(skiplist_item_t key, skiplist_item_t val, void* args)
{
}

static void flex_free_fec(skiplist_item_t key, skiplist_item_t val, void* args)
{
    if (val.ptr != NULL)
        free(val.ptr);
}

flex_fec_receiver_t* flex_fec_receiver_create(flex_segment_free_f seg_free, flex_fec_free_f fec_free, void* args)
{
    flex_fec_receiver_t* r = (flex_fec_receiver_t*)calloc(1, sizeof(flex_fec_receiver_t));
    r->cache_size = k_default_cache_size;
    r->cache = calloc(1, sizeof(sim_segment_t*) * k_default_cache_size);

    r->segs = skiplist_create(idu32_compare, flex_free_segment, NULL);
    r->fecs = skiplist_create(idu16_compare, flex_free_fec, NULL);

    r->args = args;
    r->flex_fec_free_cb = fec_free;
    r->flex_seg_free_cb = seg_free;

    return r;
}

void flex_fec_receiver_desotry(flex_fec_receiver_t* r)
{
    if (r != NULL)
    {
        if (r->segs != NULL)
        {
            skiplist_destroy(r->segs);
            r->segs = NULL;
        }

        if (r->fecs != NULL)
        {
            skiplist_destroy(r->fecs);
            r->fecs = NULL;
        }

        if (r->cache != NULL)
        {
            free(r->cache);
            r->cache = NULL;
        }

        free(r);
    }
}

void flex_fec_receiver_reset(flex_fec_receiver_t* r)
{
    if (r == NULL)
        return;

    r->base_id = 0;
    r->row = 0;
    r->col = 0;
    r->fec_id = 0;
    r->inited = 0;
    r->fec_ts = 0;

    skiplist_clear(r->segs);
    skiplist_clear(r->fecs);
}

void flex_fec_receiver_active(flex_fec_receiver_t* r, uint16_t fec_id, uint8_t col, uint8_t row, uint32_t base_id, uint16_t count)
{
    int cache_size;

    r->fec_id = fec_id;
    r->base_id = base_id;
    r->row = row;
    r->col = col;
    r->count = count;
    r->inited = 1;

    skiplist_clear(r->segs);
    skiplist_clear(r->fecs);

    cache_size = SU_MAX(r->col, r->row);
    if (r->cache_size < cache_size)
    {
        r->cache_size = (cache_size / k_default_cache_size + 1) * k_default_cache_size;
        r->cache = realloc(r->cache, sizeof(sim_segment_t*)*r->cache_size);
    }
}

int flex_fec_receiver_full(flex_fec_receiver_t* r)
{
    if (skiplist_size(r->segs) >= r->count)
        return 0;
    else
        return -1;
}

/*�ָ�����ʧ�İ�X
----------------------------------------------
| 1 | 2 | 3 | X | 5 | R0 | X = xor(1,2,3,5,R0)
----------------------------------------------
| 6 | 7 | 8 | 9 | 10| R1 |
----------------------------------------------
*/
static sim_segment_t* flex_recover_row(flex_fec_receiver_t* r, uint8_t row)
{
    sim_segment_t* seg;
    int count, i, loss;
    skiplist_item_t key;
    skiplist_iter_t* iter;

    seg = NULL;
    count = 0;
    loss = 0;

    if (skiplist_size(r->segs) >= r->count)
        return seg;

    /*ƴ�ջ���row�Ļָ���Ϣ�����ж��Ƿ񶪰�*/
    for (i = 0; i < r->col; ++i)
    {
        key.u32 = row * r->col + i + r->base_id;
        if (key.u32 >= r->base_id + r->count)
            break;

        iter = skiplist_search(r->segs, key);
        if (iter != NULL)
        {
            r->cache[count++] = iter->val.ptr;
        }
        else
            loss++;
    }

    /*FEC�޷��ָ�*/
    if (loss != 1 || count == 0)
        return seg;

    key.u16 = row;
    iter = skiplist_search(r->fecs, key);
    if (iter == NULL)
        return seg;

    /*�˴�������ڴ棬��Ҫ�ȴ����մ���������ĺ�����ͷ�*/
    seg = malloc(sizeof(sim_segment_t));
    if (flex_fec_recover(r->cache, count, iter->val.ptr, seg) != 0)
    {
        free(seg);
        seg = NULL;
    }

    return seg;
}

/*�ָ�����ʧ�İ�X
----------------------
| 1 | 2 | 3 | 4 | 5  |
----------------------
| 6 | 7 | 8 | X | 10 |
----------------------
|C1 | C2| C3| C4| C5 |
----------------------
X = xor(4, C4)
*/
static sim_segment_t* flex_recover_col(flex_fec_receiver_t* r, uint8_t col)
{
    sim_segment_t* seg;
    int count, i, loss;
    skiplist_item_t key;
    skiplist_iter_t* iter;

    seg = NULL;
    count = 0;
    loss = 0;

    if (skiplist_size(r->segs) >= r->count)
        return seg;

    /*ƴ�ջ���colum�Ļָ���Ϣ�����ж��Ƿ񶪰�*/
    for (i = 0; i < r->row; ++i)
    {
        key.u32 = i * r->col + col + r->base_id;
        if (key.u32 >= r->base_id + r->count)
            break;

        iter = skiplist_search(r->segs, key);
        if (iter != NULL)
        {
            r->cache[count++] = iter->val.ptr;
        }
        else
            loss++;
    }
    /*FEC�޷��ָ�*/
    if (loss != 1 || count == 0)
        return seg;

    key.u16 = col | 0x80;
    iter = skiplist_search(r->fecs, key);
    if (iter == NULL)
        return seg;

    /*�˴�������ڴ棬��Ҫ�ȴ����մ���������ĺ�����ͷ�*/
    seg = malloc(sizeof(sim_segment_t));
    if (flex_fec_recover(r->cache, count, iter->val.ptr, seg) != 0)
    {
        free(seg);
        seg = NULL;
    }

    return seg;
}

sim_segment_t* flex_fec_receiver_on_fec(flex_fec_receiver_t* r, sim_fec_t* fec)
{
    sim_segment_t* recover;
    skiplist_item_t key, val;
    uint8_t index;

    recover = NULL;

    if (r->inited == 0 || fec == NULL)
        goto err;

    if (r->col < 2 || r->row == 0 || r->count == 0)
        goto err;

    key.u16 = fec->index;
    if (skiplist_search(r->fecs, key) != NULL)
        goto err;

    val.ptr = fec;
    skiplist_insert(r->fecs, key, val);

    /*ȷ�����ھ�����л��������*/
    index = fec->index & 0x7F;
    if ((fec->index & 0x80) == 0x80)
        recover = flex_recover_col(r, index);
    else
        recover = flex_recover_row(r, index);

    return recover;

err:
    free(fec);
    return NULL;
}

int flex_fec_receiver_on_segment(flex_fec_receiver_t* r, sim_segment_t* seg, base_list_t* out)
{
    sim_segment_t* recover;
    skiplist_item_t key, val;

    uint8_t row, col;

    recover = NULL;

    if (r->inited == 0 || seg == NULL)
        goto err;

    if (r->col < 2 || r->row == 0 || r->count == 0 || seg->packet_id < r->base_id)
        goto err;

    key.u32 = seg->packet_id;
    if (skiplist_search(r->segs, key) != NULL)
        goto err;

    val.ptr = seg;
    skiplist_insert(r->segs, key, val);

    col = (seg->packet_id - r->base_id) % r->col;
    row = (seg->packet_id - r->base_id) / r->col;

    recover = flex_recover_row(r, row);
    if (recover != NULL)
        list_push(out, recover);

    recover = flex_recover_col(r, col);
    if (recover != NULL)
        list_push(out, recover);

    return 0;

err:
    return -1;
}

