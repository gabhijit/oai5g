/*****************************************************************************

Source      emm_recv.h

Version     0.1

Date        2013/01/30

Product     NAS stack

Subsystem   EPS Mobility Management

Author      Frederic Maurel

Description Defines functions executed at the EMMAS Service Access
        Point upon receiving EPS Mobility Management messages
        from the Access Stratum sublayer.

*****************************************************************************/
#ifndef __EMM_RECV_H__
#define __EMM_RECV_H__

#include "EmmStatus.h"

#include "DetachRequest.h"
#include "DetachAccept.h"

#include "AttachAccept.h"
#include "AttachReject.h"
#include "TrackingAreaUpdateAccept.h"
#include "TrackingAreaUpdateReject.h"
#include "ServiceReject.h"
#include "GutiReallocationCommand.h"
#include "AuthenticationRequest.h"
#include "AuthenticationReject.h"
#include "IdentityRequest.h"
#include "NASSecurityModeCommand.h"
#include "EmmInformation.h"
#include "DownlinkNasTransport.h"
#include "CsServiceNotification.h"

/****************************************************************************/
/*********************  G L O B A L    C O N S T A N T S  *******************/
/****************************************************************************/

/****************************************************************************/
/************************  G L O B A L    T Y P E S  ************************/
/****************************************************************************/

/****************************************************************************/
/********************  G L O B A L    V A R I A B L E S  ********************/
/****************************************************************************/

/****************************************************************************/
/******************  E X P O R T E D    F U N C T I O N S  ******************/
/****************************************************************************/

/*
 * --------------------------------------------------------------------------
 * Functions executed by both the UE and the MME upon receiving EMM messages
 * --------------------------------------------------------------------------
 */
int emm_recv_status(unsigned int ueid, emm_status_msg *msg, int *emm_cause);

/*
 * --------------------------------------------------------------------------
 * Functions executed by the UE upon receiving EMM message from the network
 * --------------------------------------------------------------------------
 */
int emm_recv_attach_accept(attach_accept_msg *msg, int *emm_cause);
int emm_recv_attach_reject(attach_reject_msg *msg, int *emm_cause);

int emm_recv_detach_accept(detach_accept_msg *msg, int *emm_cause);

int emm_recv_identity_request(identity_request_msg *msg, int *emm_cause);
int emm_recv_authentication_request(authentication_request_msg *msg,
                                    int *emm_cause);
int emm_recv_authentication_reject(authentication_reject_msg *msg,
                                   int *emm_cause);
int emm_recv_security_mode_command(security_mode_command_msg *msg,
                                   int *emm_cause);

#endif /* __EMM_RECV_H__*/
