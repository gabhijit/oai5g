#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ProtocolDiscriminator.h"
#include "SecurityHeaderType.h"
#include "MessageType.h"
#include "EmmCause.h"
#include "EsmMessageContainer.h"

#ifndef ATTACH_REJECT_H_
#define ATTACH_REJECT_H_

/* Minimum length macro. Formed by minimum length of each mandatory field */
#define ATTACH_REJECT_MINIMUM_LENGTH ( \
    EMM_CAUSE_MINIMUM_LENGTH )

/* Maximum length macro. Formed by maximum length of each field */
#define ATTACH_REJECT_MAXIMUM_LENGTH ( \
    EMM_CAUSE_MAXIMUM_LENGTH + \
    ESM_MESSAGE_CONTAINER_MAXIMUM_LENGTH )

/* If an optional value is present and should be encoded, the corresponding
 * Bit mask should be set to 1.
 */
# define ATTACH_REJECT_ESM_MESSAGE_CONTAINER_PRESENT (1<<0)

typedef enum attach_reject_iei_tag {
  ATTACH_REJECT_ESM_MESSAGE_CONTAINER_IEI  = 0x78, /* 0x78 = 120 */
} attach_reject_iei;

/*
 * Message name: Attach reject
 * Description: This message is sent by the network to the UE to indicate that the corresponding attach request has been rejected. See table 8.2.3.1.
 * Significance: dual
 * Direction: network to UE
 */

typedef struct attach_reject_msg_tag {
  /* Mandatory fields */
  ProtocolDiscriminator       protocoldiscriminator:4;
  SecurityHeaderType          securityheadertype:4;
  MessageType                 messagetype;
  EmmCause                    emmcause;
  /* Optional fields */
  uint32_t                    presencemask;
  EsmMessageContainer         esmmessagecontainer;
} attach_reject_msg;

int decode_attach_reject(attach_reject_msg *attachreject, uint8_t *buffer, uint32_t len);

int encode_attach_reject(attach_reject_msg *attachreject, uint8_t *buffer, uint32_t len);

#endif /* ! defined(ATTACH_REJECT_H_) */

