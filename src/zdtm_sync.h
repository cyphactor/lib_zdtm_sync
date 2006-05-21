/*
 * Copyright 2005-2006 Andrew De Ponte
 * 
 * This file is part of lib_zdtm_sync.
 * 
 * lib_zdtm_sync is free software; you can redistribute it and/or
 * modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * lib_zdtm_sync is distributed in the hopes that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with lib_zdtm_sync; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

/**
 * @file zdtm_sync.h
 * @brief This is a specifications file for a Zaurus DTM support library.
 *
 * The zdtm_sync.h file is a specifications for a Zaurus DTM based
 * synchronization, general support library. It provides all prototypes
 * of the general functions used to perform a Zaurus DTM based
 * synchronization.
 */

#ifndef ZDTM_SYNC_H
#define ZDTM_SYNC_H

// Standard Input/Output Includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Memory Includes
#include <string.h>

// Network Related Includes
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Standard Integer Type Includes
#include <stdint.h>

#include "config.h"

// This is the port that the Zaurus listens on waiting for a connection
// to initiate a synchronization from the Desktop.
#define ZLISTPORT 4244
// This is the port that the Desktop synchronization server listens on
// waiting for a connection from the Zaurus to perform a synchronization.
#define DLISTPORT 4245

// This is the size, in bytes,  of a Zaurus DTM Message header.
#define MSG_HDR_SIZE 13
// This is the size, in bytes,  of a Zaurus DTM Message type.
#define MSG_TYPE_SIZE 3
// This is the size, in bytes,  of a common messages.
#define COM_MSG_SIZE 7

// Return values
#define RET_NNULL_RAW     -7
#define RET_SIZE_MISMATCH -8
#define RET_MEM_CONTENT   -9
#define RET_UNK_TYPE      -10
#define RET_BAD_SIZE      -11

// Sync Types
#define SYNC_TYPE_CALENDAR  0x01
#define SYNC_TYPE_TODO      0x06
#define SYNC_TYPE_ADDRESS   0x07

// This is the static message header for the Zaurus
const unsigned char ZMSG_HDR[MSG_HDR_SIZE] =
{0x00, 0x00, 0x00, 0x00, 0x00, 0x96, 0x01, 0x01, 0x00, 0xff, 0xff, 0xff, 0xff};

// This is the static message header for the Desktop
// The two 0xff bytes are to be replaced by the message content size later
const unsigned char DMSG_HDR[MSG_HDR_SIZE] =
{0x00, 0x00, 0x00, 0x00, 0x00, 0x96, 0x01, 0x01, 0x0c, 0xff, 0xff, 0x00, 0x00};

#define MSG_HDR_CONT_OFFSET 0x09

/**
 * Zaurus DTM library environment.
 *
 * The zdtm_lib_env is a type defined to represent the environment for a
 * given synchronization. It contains all the data that is required to
 * be shared among all the different zdtm library functions. Hence,
 * every synchronization must first have it's own non-shared (not shared
 * between synchronizations) environment before being able to use
 * the provided functions. Note: It does not have to be initialized in
 * any certain way, it can be filled with garbage as long as the
 * provided functions are called in the proper order.
 */
typedef struct zdtm_environment {
    int listenfd;   // socket - listen for zaurus conn request
    int connfd;     // socket - connection from zaurus to desktop
    int reqfd;      // socket - connection to zaurus from the desktop
    FILE *logfp;    // file pointer - used as the log file.
} zdtm_lib_env;

/*
 * ### This section denotes the start of the definitions of the specific
 * ### message content type definitions which are designed to be used
 * ### within a union inside the message type.
 */

/**
 * Zaurus AAY message content.
 *
 * The zdtm_aay_msg_content is a structure which represents an AAY
 * Zaurus message content after being parsed from the raw message
 * content.
 */
struct zdtm_aay_msg_content {
    unsigned char uk_data_0[3]; // general unknown data
};

const char *AAY_MSG_TYPE = "AAY";
#define IS_AAY(x) (memcmp(x->body.type, AAY_MSG_TYPE, MSG_TYPE_SIZE) == 0)

/**
 * Zaurus AIG message content.
 *
 * The zdtm_aig_msg_content is a structure which represents an AIG
 * Zaurus message content after being parsed from the raw message
 * content.
 */
struct zdtm_aig_msg_content {
    uint16_t model_str_len;     // length of the model string
    unsigned char *model_str;   // string of the zaurus model info
    unsigned char uk_data_0[5]; // general unknown data
    unsigned char language[2];  // an identifier of the zaurus lang
    unsigned char auth_state;   // zaurus authentication state
    unsigned char uk_data_1[6]; // general unknown data
};

const char *AIG_MSG_TYPE = "AIG";
#define IS_AIG(x) (memcmp(x->body.type, AIG_MSG_TYPE, MSG_TYPE_SIZE) == 0)

/**
 * Zaurus AMG message content.
 *
 * The zdtm_amg_msg_content is a structure which represents an AMG
 * Zaurus message content after being parsed from the raw message
 * content.
 */
struct zdtm_amg_msg_content {

};
const char *AMG_MSG_TYPE = "AMG";
#define IS_AMG(x) (memcmp(x->body.type, AMG_MSG_TYPE, MSG_TYPE_SIZE) == 0)

/**
 * Zaurus ATG message content.
 *
 * The zdtm_atg_msg_content is a structure which represents an ATG
 * Zaurus message content after being parsed from the raw message
 * content.
 */
struct zdtm_atg_msg_content {
    unsigned char year[4];
    unsigned char month[2];
    unsigned char day[2];
    unsigned char hour[2];
    unsigned char minutes[2];
    unsigned char seconds[2];
};

const char *ATG_MSG_TYPE = "ATG";
#define IS_ATG(x) (memcmp(x->body.type, ATG_MSG_TYPE, MSG_TYPE_SIZE) == 0)

/**
 * Zaurus AEX message content.
 *
 * The zdtm_aex_msg_content is a structure which represents an AEX
 * Zaurus message content after being parsed from the raw message
 * content.
 */
struct zdtm_aex_msg_content {

};
const char *AEX_MSG_TYPE = "AEX";
#define IS_AEX(x) (memcmp(x->body.type, AEX_MSG_TYPE, MSG_TYPE_SIZE) == 0)

/**
 * Desktop RAY message content.
 *
 * The zdtm_ray_msg_content represents an RAY Desktop to Zaurus message
 * in response to the AAY message.  It contains no specific content.
 */
struct zdtm_ray_msg_content {

};

const char *RAY_MSG_TYPE = "RAY";
#define IS_RAY(x) (memcmp(x->body.type, RAY_MSG_TYPE, MSG_TYPE_SIZE) == 0)

/**
 * Desktop RIG message content.
 *
 * The zdtm_rig_msg_content represents an RIG Desktop to Zaurus message
 * to request an AIG information packet.
 */
struct zdtm_rig_msg_content {
};

const char *RIG_MSG_TYPE = "RIG";
#define IS_RIG(x) (memcmp(x->body.type, RIG_MSG_TYPE, MSG_TYPE_SIZE) == 0)

/**
 * Desktop RRL message content.
 *
 * The zdtm_rrl_msg_content represents an RRL Desktop to Zaurus message
 * for authentication.
 */
struct zdtm_rrl_msg_content {
    unsigned char pw_size;
    char *pw;
};

const char *RRL_MSG_TYPE = "RRL";
#define IS_RRL(x) (memcmp(x->body.type, RRL_MSG_TYPE, MSG_TYPE_SIZE) == 0)

/**
 * Desktop RMG message content.
 *
 * The zdtm_rmg_msg_content represents an RMG Desktop to Zaurus message
 * to indicate the synchronization type.
 *      - uk is typically 0x01
 *      - sync_type
 *          - todo 0x06
 *          - calendar 0x01
 *          - address book 0x07
 * Synchronization log.
 */

struct zdtm_rmg_msg_content {
    unsigned char uk;
    unsigned char sync_type;
};

const char *RMG_MSG_TYPE = "RMG";
#define IS_RMG(x) (memcmp(x->body.type, RMG_MSG_TYPE, MSG_TYPE_SIZE) == 0)


/**
 * Desktop RMS message content.
 *
 * The zdtm_rms_msg_content represents an RMS Desktop to Zaurus message
 * in the process of doing a full synchronization.
 * Not really implemented at the moment.
 * First two bytes are size, the remaining 38 are log message.
 * The message is padded with 0x00 if it is not the full size.
 */

struct zdtm_rms_msg_content {
    uint16_t log_size;
    unsigned char log[38];
};

const char *RMS_MSG_TYPE = "RMS";
#define IS_RMS(x) (memcmp(x, RMS_MSG_TYPE, MSG_TYPE_SIZE) == 0)

/**
 * Desktop RTG message content.
 *
 * The zdtm_rtg_msg_content represents an RTG Desktop to Zaurus message
 * Request for time stamp.
 */

struct zdtm_rtg_msg_content {
};

const char *RTG_MSG_TYPE = "RTG";
#define IS_RTG(x) (memcmp(x->body.type, RTG_MSG_TYPE, MSG_TYPE_SIZE) == 0)

/**
 * Desktop RTS message content.
 *
 * The zdtm_rts_msg_content represents an RTS Desktop to Zaurus message
 * notify Zaurus of the time.
 *
 * String of YYYYMMDDhhmmss
 */

#define RTS_DATE_LEN 14

struct zdtm_rts_msg_content {
    char date[RTS_DATE_LEN];
};

const char *RTS_MSG_TYPE = "RTS";
#define IS_RTS(x) (memcmp(x->body.type, RTS_MSG_TYPE, MSG_TYPE_SIZE) == 0)

/**
 * Desktop RDI message content.
 *
 * The zdtm_rdi_msg_content represents an RDI Desktop to Zaurus message
 * solicits ADI message.
 *      - sync_type
 *          - todo 0x06
 *          - calendar 0x01
 *          - address book 0x07
 *      - uk is typically 0x07
 */

struct zdtm_rdi_msg_content {
    unsigned char sync_type;
    unsigned char uk;
};

const char *RDI_MSG_TYPE = "RDI";
#define IS_RDI(x) (memcmp(x->body.type, RDI_MSG_TYPE, MSG_TYPE_SIZE) == 0)

/**
 * Desktop RSY message content.
 *
 * The zdtm_rsy_msg_content represents an RDI Desktop to Zaurus message
 * solicits ASY message.
 *      - sync_type
 *          - todo 0x06
 *          - calendar 0x01
 *          - address book 0x07
 *      - uk is typically 0x07
 */

struct zdtm_rsy_msg_content {
    unsigned char sync_type;
    unsigned char uk;
};

const char *RSY_MSG_TYPE = "RSY";
#define IS_RSY(x) (memcmp(x->body.type, RSY_MSG_TYPE, MSG_TYPE_SIZE) == 0)

/**
 * Zaurus DTM Message Body.
 *
 * The zdtm_message_body is a structure which represents the body of a
 * Zaurus DTM message.
 */
struct zdtm_message_body {
    unsigned char type[MSG_TYPE_SIZE];  // type identifier for a message
    void *p_raw_content;                // content for a given message
    union zdtm_spec_type_content {
        // Content structures for Zaurus messages
        struct zdtm_aay_msg_content aay;
        struct zdtm_aig_msg_content aig;
        struct zdtm_amg_msg_content amg;
        struct zdtm_atg_msg_content atg;
        struct zdtm_aex_msg_content aex;

        // Content structures for Qtopia Desktop messages
        struct zdtm_ray_msg_content ray;
        struct zdtm_rig_msg_content rig;
        struct zdtm_rrl_msg_content rrl;
        struct zdtm_rmg_msg_content rmg;
        struct zdtm_rms_msg_content rms;
        struct zdtm_rtg_msg_content rtg;
        struct zdtm_rts_msg_content rts;
        struct zdtm_rdi_msg_content rdi;
        struct zdtm_rsy_msg_content rsy;
    } cont;
};

/**
 * Zaurus DTM Message.
 *
 * The zdtm_message is a structure which represents a Zaurus DTM
 * Message.
 */
typedef struct zdtm_message {
    char header[MSG_HDR_SIZE];      // header of the message
    struct zdtm_message_body body;  // body of the msg (type and cont)
    uint16_t body_size;             // size of the msg body in bytes
    uint16_t check_sum;             // sum of each byte in msg body
    uint16_t cont_size;             // msg body size - msg type size
} zdtm_msg;



/*
Options for Message storage

typedef struct zdtm_message {
    char header[MSG_HDR_SIZE];      // header of the message
    struct zdtm_message_body body;  // body of the msg (type and cont)
    union type_body {
        struct ray_msg_type ray_body;
        struct rig_msg_type rig_body;
        struct aig_msg_type aig_body;
    }
    uint16_t body_size;             // size of the msg body in bytes
    uint16_t check_sum;             // sum of each byte in msg body
    uint16_t cont_size;             // msg body size - msg type size
} zdtm_msg;

This first method requires checking of the message type to determin
which body to access for both sides of any functions that it is passed
into. For example:

if(memcmp(zdtm_message.header, "AIG", 3) == 0) {
    parse_aig_message(zdtm_msg *some_msg); 
} else if (memcmp(zdtm_message.header, "RAY", 3) == 0) {
    parse_ray_message(zdtm_msg *some_msg);
} else if...
...

This method is on the top of my list right now.

Or I could provide functions to parse each member out of each specific
type of message. I do NOT like this solution, it polutes the name space.

Or I could just create seperate structs for each type of message using
common namings for shared members and pass them through functions using
void * pointers which would then have to be type casted appropriately on
both sides of the functions dependent upon the message type.
*/

uint16_t zdtm_liltobigs(uint16_t lilshort);
uint32_t zdtm_liltobigl(uint32_t lillong);
uint16_t zdtm_bigtolils(uint16_t bigshort);
uint32_t zdtm_bigtolill(uint32_t biglong);

uint16_t zdtm_checksum(unsigned char *buf, uint16_t n);

int zdtm_listen_for_zaurus(zdtm_lib_env *cur_env);
int zdtm_handle_zaurus_conn(zdtm_lib_env *cur_env);
int zdtm_close_zaurus_conn(zdtm_lib_env *cur_env);
int zdtm_conn_to_zaurus(zdtm_lib_env *cur_env, const char *zaurus_ip);

int zdtm_open_log(zdtm_lib_env *cur_env);
int zdtm_write_log(zdtm_lib_env *cur_env, const unsigned char *buff,
    unsigned int size);
int zdtm_close_log(zdtm_lib_env *cur_env);

int zdtm_is_ack_message(const unsigned char *buff);
int zdtm_is_rqst_message(const unsigned char *buff);
int zdtm_is_abrt_message(const unsigned char *buff);

int zdtm_clean_message(zdtm_msg *p_msg);
int zdtm_recv_message(zdtm_lib_env *cur_env, zdtm_msg *p_msg);
int zdtm_prepare_message(zdtm_lib_env *cur_env, zdtm_msg *p_msg);
//int zdtm_send_message(zdtm_lib_env *cur_env, zdtm_msg *p_msg);

int zdtm_parse_raw_msg(zdtm_lib_env *cur_env, zdtm_msg *p_msg);

//struct zdtm_aay_msg * zdtm_msg_to_aay_msg(zdtm_msg *p_msg);

#endif
