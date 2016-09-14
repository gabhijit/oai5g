#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "TLVEncoder.h"
#include "TLVDecoder.h"
#include "MsNetworkCapability.h"

int decode_ms_network_capability(MsNetworkCapability *msnetworkcapability, uint8_t iei, uint8_t *buffer, uint32_t len)
{
  int decoded = 0;
  uint8_t ielen = 0;
  int decode_result;

  if (iei > 0) {
    CHECK_IEI_DECODER(iei, *buffer);
    decoded++;
  }

  ielen = *(buffer + decoded);
  decoded++;
  CHECK_LENGTH_DECODER(len - decoded, ielen);

  if ((decode_result = decode_octet_string(&msnetworkcapability->msnetworkcapabilityvalue, ielen, buffer + decoded, len - decoded)) < 0)
    return decode_result;
  else
    decoded += decode_result;

#if defined (NAS_DEBUG)
  dump_ms_network_capability_xml(msnetworkcapability, iei);
#endif
  return decoded;
}
int encode_ms_network_capability(MsNetworkCapability *msnetworkcapability, uint8_t iei, uint8_t *buffer, uint32_t len)
{
  uint8_t *lenPtr;
  uint32_t encoded = 0;
  int encode_result;
  /* Checking IEI and pointer */
  CHECK_PDU_POINTER_AND_LENGTH_ENCODER(buffer, MS_NETWORK_CAPABILITY_MINIMUM_LENGTH, len);
#if defined (NAS_DEBUG)
  dump_ms_network_capability_xml(msnetworkcapability, iei);
#endif

  if (iei > 0) {
    *buffer = iei;
    encoded++;
  }

  lenPtr  = (buffer + encoded);
  encoded ++;

  if ((encode_result = encode_octet_string(&msnetworkcapability->msnetworkcapabilityvalue, buffer + encoded, len - encoded)) < 0)
    return encode_result;
  else
    encoded += encode_result;

  *lenPtr = encoded - 1 - ((iei > 0) ? 1 : 0);
  return encoded;
}

void dump_ms_network_capability_xml(MsNetworkCapability *msnetworkcapability, uint8_t iei)
{
  printf("<Ms Network Capability>\n");

  if (iei > 0)
    /* Don't display IEI if = 0 */
    printf("    <IEI>0x%X</IEI>\n", iei);

  printf("%s",dump_octet_string_xml(&msnetworkcapability->msnetworkcapabilityvalue));
  printf("</Ms Network Capability>\n");
}

