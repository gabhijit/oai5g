#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "TLVEncoder.h"
#include "TLVDecoder.h"
#include "UeRadioCapabilityInformationUpdateNeeded.h"

int decode_ue_radio_capability_information_update_needed(UeRadioCapabilityInformationUpdateNeeded *ueradiocapabilityinformationupdateneeded, uint8_t iei, uint8_t *buffer, uint32_t len)
{
  int decoded = 0;
  CHECK_PDU_POINTER_AND_LENGTH_DECODER(buffer, UE_RADIO_CAPABILITY_INFORMATION_UPDATE_NEEDED_MINIMUM_LENGTH, len);

  if (iei > 0) {
    CHECK_IEI_DECODER((*buffer & 0xf0), iei);
  }

  *ueradiocapabilityinformationupdateneeded = *buffer & 0x1;
  decoded++;
#if defined (NAS_DEBUG)
  dump_ue_radio_capability_information_update_needed_xml(ueradiocapabilityinformationupdateneeded, iei);
#endif
  return decoded;
}

int decode_u8_ue_radio_capability_information_update_needed(UeRadioCapabilityInformationUpdateNeeded *ueradiocapabilityinformationupdateneeded, uint8_t iei, uint8_t value, uint32_t len)
{
  int decoded = 0;
  uint8_t *buffer = &value;
  *ueradiocapabilityinformationupdateneeded = *buffer & 0x1;
  decoded++;
#if defined (NAS_DEBUG)
  dump_ue_radio_capability_information_update_needed_xml(ueradiocapabilityinformationupdateneeded, iei);
#endif
  return decoded;
}

int encode_ue_radio_capability_information_update_needed(UeRadioCapabilityInformationUpdateNeeded *ueradiocapabilityinformationupdateneeded, uint8_t iei, uint8_t *buffer, uint32_t len)
{
  uint8_t encoded = 0;
  /* Checking length and pointer */
  CHECK_PDU_POINTER_AND_LENGTH_ENCODER(buffer, UE_RADIO_CAPABILITY_INFORMATION_UPDATE_NEEDED_MINIMUM_LENGTH, len);
#if defined (NAS_DEBUG)
  dump_ue_radio_capability_information_update_needed_xml(ueradiocapabilityinformationupdateneeded, iei);
#endif
  *(buffer + encoded) = 0x00 | (iei & 0xf0) |
                        (*ueradiocapabilityinformationupdateneeded & 0x1);
  encoded++;
  return encoded;
}

uint8_t encode_u8_ue_radio_capability_information_update_needed(UeRadioCapabilityInformationUpdateNeeded *ueradiocapabilityinformationupdateneeded)
{
  uint8_t bufferReturn;
  uint8_t *buffer = &bufferReturn;
  uint8_t encoded = 0;
  uint8_t iei = 0;
  dump_ue_radio_capability_information_update_needed_xml(ueradiocapabilityinformationupdateneeded, 0);
  *(buffer + encoded) = 0x00 | (iei & 0xf0) |
                        (*ueradiocapabilityinformationupdateneeded & 0x1);
  encoded++;

  return bufferReturn;
}

void dump_ue_radio_capability_information_update_needed_xml(UeRadioCapabilityInformationUpdateNeeded *ueradiocapabilityinformationupdateneeded, uint8_t iei)
{
  printf("<Ue Radio Capability Information Update Needed>\n");

  if (iei > 0)
    /* Don't display IEI if = 0 */
    printf("    <IEI>0x%X</IEI>\n", iei);

  printf("    <URC upd>%u</URC upd>\n", *ueradiocapabilityinformationupdateneeded);
  printf("</Ue Radio Capability Information Update Needed>\n");
}

