#ifndef ZDTM_ADI_MSG_H
#define ZDTM_ADI_MSG_H

#include "zdtm_common.h"
#include "zdtm_types.h"

/**
 * Zaurus ADI message content.
 *
 * The zdtm_adi_msg_content is a structure which represents an ADI
 * Zaurus message content after being parsed from the raw message
 * content.
 */
struct zdtm_adi_msg_content {
    uint32_t num_cards;
    uint16_t num_params;
    unsigned char uk_data_0;
    struct zdtm_adi_msg_param *params;
};
extern const char *ADI_MSG_TYPE;
#define IS_ADI(x) (memcmp(x->body.type, ADI_MSG_TYPE, MSG_TYPE_SIZE) == 0)

int zdtm_parse_raw_adi_msg(void *buf, struct zdtm_adi_msg_content *adi);

#endif
