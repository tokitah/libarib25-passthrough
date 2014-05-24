#ifndef ARIB25_H
#define ARIB25_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ARIB_STD_B25_PROGRAM_INFO_T {
       int32_t  program_number;
       int32_t  ecm_unpurchased_count;
       int32_t  last_ecm_error_code;
       int32_t  padding;
       int64_t  total_packet_count;
       int64_t  undecrypted_packet_count;
} ARIB_STD_B25_PROGRAM_INFO;

typedef struct ARIB_STD_B25_BUFFER_T {
    uint8_t *data;
    int32_t  size;
} ARIB_STD_B25_BUFFER;

typedef struct B_CAS_CARD_T {
    void *private_data;

    void (*release)(void* ctx);
    int (*init)(void* ctx);
    int (*get_init_status)(void* ctx, void *x);
    int (*get_id)(void* ctx, void *x);
    int (*get_pwr_on_ctrl)(void* ctx, void *x);
    int (*proc_ecm)(void* ctx, void* x, uint8_t *y, int z);
    int (*proc_emm)(void* ctx, uint8_t *x, int y);
} B_CAS_CARD;

typedef struct ARIB_STD_B25_T {
    void *private_data;

    void (*release)(void* ctx);
    int (*set_multi2_round)(void* ctx, int32_t x);
    int (*set_strip)(void* ctx, int32_t x);
    int (*set_emm_proc)(void* ctx, int32_t x);
    int (*set_b_cas_card)(void* ctx, struct B_CAS_CARD_T* x);
    int (*reset)(void* ctx);
    int (*flush)(void* ctx);
    int (*put)(void* ctx, ARIB_STD_B25_BUFFER *buf);
    int (*get)(void* ctx, ARIB_STD_B25_BUFFER *buf);
    int (*get_program_count)(void* ctx);
    int (*get_program_info)(void* ctx, ARIB_STD_B25_PROGRAM_INFO *x, int32_t y);
} ARIB_STD_B25;

extern ARIB_STD_B25* create_arib_std_b25();
extern B_CAS_CARD* create_b_cas_card();

#ifdef __cplusplus
}
#endif

#endif
