#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sched.h>
#include <linux/sched.h>
#include <signal.h>
#include <execinfo.h>
#include <getopt.h>
#include <syscall.h>

void s1ap_eNB_handle_sctp_data_ind(sctp_data_ind_t *sctp_data_ind);

void s1ap_eNB_itti_send_sctp_data_req(instance_t instance, int32_t assoc_id, uint8_t *buffer,
                                      uint32_t buffer_length, uint16_t stream);

void s1ap_handle_s1_setup_message(s1ap_eNB_mme_data_t *mme_desc_p, int sctp_shutdown);

void s1ap_eNB_handle_sctp_association_resp(instance_t instance, sctp_new_association_resp_t *sctp_new_association_resp);

void s1ap_eNB_register_mme(s1ap_eNB_instance_t *instance_p,
                                  net_ip_address_t    *mme_ip_address,
                                  net_ip_address_t    *local_ip_addr,
                                  uint16_t             in_streams,
                                  uint16_t             out_streams);
void s1ap_eNB_handle_register_eNB(instance_t instance, s1ap_register_enb_req_t *s1ap_register_eNB);
void *s1ap_eNB_task(void *arg);
