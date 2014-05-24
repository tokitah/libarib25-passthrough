#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "arib25.h"

static void arib_std_b25_release(void* ctx)
{
	ARIB_STD_B25_BUFFER* internal_buf = (ARIB_STD_B25_BUFFER*)(((ARIB_STD_B25*)ctx)->private_data);
	free(internal_buf->data);
	free((internal_buf+1)->data);
	free(((ARIB_STD_B25*)ctx)->private_data);
	free(ctx);
}

static int arib_std_b25_set_multi2_round(void *x, int32_t y) { return 0; }
static int arib_std_b25_set_strip(void* ctx, int32_t x) { return 0; }
static int arib_std_b25_set_emm_proc(void* ctx, int32_t x) { return 0; }
static int arib_std_b25_set_b_cas_card(void* ctx, B_CAS_CARD *x) { return 0; }
static int arib_std_b25_get_program_count(void* ctx) { return 0; }
static int arib_std_b25_get_program_info(void* ctx, ARIB_STD_B25_PROGRAM_INFO *x, int32_t y) { return 0; }

static int arib_std_b25_put(void* ctx, ARIB_STD_B25_BUFFER *buf)
{
	ARIB_STD_B25_BUFFER* internal_buf = (ARIB_STD_B25_BUFFER*)(((ARIB_STD_B25*)ctx)->private_data);
	//ARIB_STD_B25_BUFFER* out_buf = internal_buf+1;
	unsigned int newsize = internal_buf->size + buf->size;

	void* newbuf = realloc(internal_buf->data, newsize);

	newbuf += internal_buf->size;
	memcpy(newbuf, buf->data, buf->size);

	internal_buf->data = newbuf;
	internal_buf->size = newsize;

	return 0;
}

static int arib_std_b25_get(void* ctx, ARIB_STD_B25_BUFFER *buf)
{
	ARIB_STD_B25_BUFFER* internal_buf = (ARIB_STD_B25_BUFFER*)(((ARIB_STD_B25*)ctx)->private_data);
	ARIB_STD_B25_BUFFER* out_buf = internal_buf+1;
	unsigned int newsize = internal_buf->size;

	void* newbuf = realloc(out_buf->data, newsize);
	memcpy(newbuf, internal_buf->data, newsize);

	out_buf->data = newbuf;
	out_buf->size = internal_buf->size;
	internal_buf->size = 0;

	buf->size = out_buf->size;
	buf->data = out_buf->data;

	return 0;
}

static int arib_std_b25_reset(void* ctx)
{
	ARIB_STD_B25_BUFFER* internal_buf = (ARIB_STD_B25_BUFFER*)(((ARIB_STD_B25*)ctx)->private_data);
	ARIB_STD_B25_BUFFER* out_buf = internal_buf+1;
	internal_buf->size = 0;
	out_buf->size = 0;
	return 0;
}

static int arib_std_b25_flush(void* ctx) { return 0; }

ARIB_STD_B25* create_arib_std_b25() {
	ARIB_STD_B25* context = (ARIB_STD_B25*)malloc(sizeof(ARIB_STD_B25) );
	context->release = arib_std_b25_release;
	context->set_multi2_round = arib_std_b25_set_multi2_round;
	context->set_strip = arib_std_b25_set_strip;
	context->set_emm_proc = arib_std_b25_set_emm_proc;
	context->set_b_cas_card = arib_std_b25_set_b_cas_card;
	context->reset = arib_std_b25_reset;
	context->flush = arib_std_b25_flush;
	context->put = arib_std_b25_put;
	context->get = arib_std_b25_get;
	context->get_program_count = arib_std_b25_get_program_count;
	context->get_program_info = arib_std_b25_get_program_info;
	context->private_data = malloc(sizeof(ARIB_STD_B25_BUFFER)*2 );
	memset(context->private_data, 0, sizeof(ARIB_STD_B25_BUFFER)*2);
	
	return context;
}

static void b_cas_card_release(void* ctx) { free(ctx); return; }
static int b_cas_card_init(void* ctx) { return 0; }
static int b_cas_card_get_init_status(void* ctx, void *x) { return 0; }
static int b_cas_card_get_id(void* ctx, void *y) { return 0; }
static int b_cas_card_get_pwr_on_ctrl(void* ctx, void *x) { return 0; }
static int b_cas_card_proc_ecm(void* ctx, void *x, uint8_t *y, int z) { return 0; }
static int b_cas_card_proc_emm(void* ctx, uint8_t *x, int y) { return 0; }

B_CAS_CARD *create_b_cas_card() {
	B_CAS_CARD* context = malloc(sizeof(B_CAS_CARD) );
	context->release = b_cas_card_release;
	context->init =b_cas_card_init;
	context->get_init_status = b_cas_card_get_init_status;
	context->get_id = b_cas_card_get_id;
	context->get_pwr_on_ctrl = b_cas_card_get_pwr_on_ctrl;
	context->proc_ecm - b_cas_card_proc_ecm;
	context->proc_emm = b_cas_card_proc_emm;

	return context;
}
