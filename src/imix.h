#ifndef IMIX_H
#define IMIX_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IMIX_NUM_SIZES 3
static const uint32_t IMIX_PAYLOAD_SIZES[IMIX_NUM_SIZES] = {36, 548, 1472};

static const uint32_t IMIX_WEIGHTS[IMIX_NUM_SIZES] = {7, 3, 2};

#define IMIX_SEQ_LEN 8192  /* Length of the precomputed sequence of indices */

typedef struct {
    uint8_t *seq;       /* Array of indices */
    size_t seq_len;
    size_t pos;         /* Current position in the cyclic sequence */
} imix_state_t;

/* Initialize IMIX (populate the index array) */
imix_state_t* imix_init(unsigned int seed);

/* Get the next UDP payload size */
uint32_t imix_next_size(imix_state_t *state);

/* Free the memory occupied by IMIX. */
void imix_free(imix_state_t *state);

#ifdef __cplusplus
}
#endif

#endif /* IMIX_H */
