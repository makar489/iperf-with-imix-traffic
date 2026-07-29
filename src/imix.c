#include "imix.h"
#include <string.h>

imix_state_t* imix_init(unsigned int seed) {
    imix_state_t *st = malloc(sizeof(imix_state_t));
    if (!st) return NULL;
    st->seq_len = IMIX_SEQ_LEN;
    st->seq = malloc(st->seq_len);
    if (!st->seq) { free(st); return NULL; }
    st->pos = 0;
    srand(seed);

    uint32_t total = IMIX_WEIGHTS[0] + IMIX_WEIGHTS[1] + IMIX_WEIGHTS[2];
    for (size_t i = 0; i < st->seq_len; ++i) {
        uint32_t r = rand() % total;
        if (r < IMIX_WEIGHTS[0]) {
            st->seq[i] = 0;
        } else if (r < IMIX_WEIGHTS[0] + IMIX_WEIGHTS[1]) {
            st->seq[i] = 1;
        } else {
            st->seq[i] = 2;
        }
    }
    return st;
}

uint32_t imix_next_size(imix_state_t *state) {
    if (!state || state->seq_len == 0) {
        return 0;
    }
    uint8_t idx = state->seq[state->pos];
    state->pos = (state->pos + 1) % state->seq_len;
    return IMIX_PAYLOAD_SIZES[idx];
}

void imix_free(imix_state_t *state) {
    if (!state) return;
    free(state->seq);
    free(state);
}
