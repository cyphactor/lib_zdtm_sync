/*
 * Copyright 2005-2007 Andrew De Ponte
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
 * @file zdtm_proto.h
 * @brief This is a specifications file for the zdtm protocol.
 *
 * The zdtm_proto.h file is a specifications file for the Zaurus DTM
 * based synchronization protocols private API. This is a layer which
 * basically provides function prototypes for all the private functions
 * which implement logical components found in the protocol, such as
 * obtain an objects sync id, obtaining device info, etc.
 */

#ifndef ZDTM_PROTO_H
#define ZDTM_PROTO_H

#include <time.h>
#include "zdtm_types.h"
#include "zdtm_net.h"
#include "zdtm_log.h"

/**
 * Connect to Zaurus.
 *
 * The zdtm_connect function connects the current library environment to
 * the Zaurus so that a synchronization may be performed. Note: This
 * should be called directly after zdtm_initalize and only if you want
 * to perform a Desktop initiated synchronization.
 * @param cur_env Pointer to the current zdtm library environment.
 * @param ip_addr IP address of Zaurus to connect to in dotted-quad.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully connected to the Zaurus.
 * @retval -1 Failed to make TCP/IP connection to the Zaurus.
 * @retval -2 Failed to send RAY message to the Zaurus.
 * @retval -3 Falied to handle the incoming Zaurus connection.
 */
int _zdtm_connect(zdtm_lib_env *cur_env, const char *ip_addr);

/**
 * Handle Connection.
 *
 * The zdtm_handle_connection function handles accepting a
 * synchronization connection that was initation from the Zaurus. If no
 * connections have been made yet then it blocks waiting for a
 * connection to be made from the Zaurus. Note: This should be called
 * directly after zdtm_initialize and only if you are not perform a
 * Desktop initiated synchronization.
 * @param cur_env Pointer to the current zdtm library environment.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully connected to the Zaurus.
 * @retval -1 Failed to handle the incoming Zaurus connection.
 */
int _zdtm_handle_connection(zdtm_lib_env *cur_env);

/**
 * Obtain Device Information
 *
 * The zdtm_obtain_device_info function obtains the device info (Model,
 * Language, Authentication State, etc). This function updates the key
 * device information stored in the current zdtm library environment.
 * @param cur_env Pointer to the current zdtm library environment.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully obtained and updated device information.
 * @retval -1 Failed to send RIG message.
 * @retval -2 Failed to send AIG message.
 * @retval -3 Received message other than AIG after sending RIG message.
 */
int _zdtm_obtain_device_info(zdtm_lib_env *cur_env);

/**
 * Obtain Sync State
 *
 * The _zdtm_obtain_sync_state function obtains the current sync state
 * from the device and up dates all the necessary sync state fields
 * stored within the current zdtm library environment.
 * @param cur_env Pointer to the current zdtm library environment.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully obtained and updated sync state.
 * @retval -1 Failed to send RMG message.
 * @retval -2 Failed to recv AMG message.
 * @retval -3 Failed, message recv'd was not an AMG message.
 */
int _zdtm_obtain_sync_state(zdtm_lib_env *cur_env);

/**
 * Authenticate Passcode
 *
 * The _zdtm_authenticate_passcode function attempts to authenticate the
 * given passcode with the Zaurus so that a sync may be performed.
 * @param cur_env Pointer to the current zdtm library environment.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully authenticated passcode.
 * @retval 1 Passcode authentication was denied.
 * @retval -1 Failed to allocate memory for RRL message.
 * @retval -2 Failed to send RRL message.
 * @retval -3 Failed to recv response message.
 * @retval -4 Failed to recv'd an unhandled message as a response.
 */
int _zdtm_authenticate_passcode(zdtm_lib_env *cur_env, char *passcode);

/**
 * Obtain Last Time Synced
 *
 * The _zdtm_obtain_last_time_synced function attempts to obtain a
 * timestamp of the last time a synchronization occured. This is often
 * referred to as a synchronization anchor and can be used to help
 * identify if a slow (full) sync needs to be performed.
 * @param cur_env Pointer to the current zdtm library environment.
 * @param p_time Pointer to time_t variable to store returned time in.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully obtained last time synced.
 * @retval -1 Failed to send RTG message.
 * @retval -2 Failed to recv response message.
 * @retval -3 Failed, response message wasn't an ATG message.
 * @retval -4 Failed to convert timestamp into time_t format.
 */
int _zdtm_obtain_last_time_synced(zdtm_lib_env *cur_env, time_t *p_time);

/**
 * Set Last Time Synced
 *
 * The _zdtm_set_last_time_synced function attempts to set the timestamp
 * of the last time a synchronization occured on the Zaurus. This is
 * often referred to as setting the next synchronization anchor. It can
 * be used to help identify if a slow (full) sync needs to be performed.
 * @param cur_env Pointer to the current zdtm library environment.
 * @param time_synced The time of sync as seconds since Epoch.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully set the last time synced.
 * @retval -1 Failed to convert time_synced to useable form.
 * @retval -2 Failed to construct RTS message payload.
 * @retval -3 Failed to send RTS message.
 * @retval -4 Failed to recv a response message.
 * @retval -5 Failed, response message was not an AEX message.
 */
int _zdtm_set_last_time_synced(zdtm_lib_env *cur_env, time_t time_synced);

/**
*  Reset Sync Log
 *
 * The _zdtm_reset_sync_log function attempts to reset the sync log
 * on the Zaurus. This effectively makes a slow (full) sync required.
 * @param cur_env Pointer to the current zdtm library environment.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully obtained and updated sync state.
 * @retval -1 Failed to send RMS message.
 * @retval -2 Failed to recv abort common message as response.
 * @retval -3 Failed to recv response message.
 * @retval -4 Failed, message recv'd was not an ANG message.
 * @retval -5 Failed to send RMS message containing log.
 * @retval -6 Failed to recv response message.
 * @retval -7 Failed, message recv'd was not an AEX message.
*/
int _zdtm_reset_sync_log(zdtm_lib_env *cur_env);

/**
*  Reset Item State
 */
int _zdtm_reset_item_states(zdtm_lib_env *cur_env);

/**
 * Obtain Sync ID Lists
 *
 * The _zdtm_obtain_sync_id_lists function attempts to obtain the three
 * lists of synchronization IDs from the Zaurus. One list contains all
 * the IDs of the new items, one contains all the IDs of modified items,
 * and the third list contains all the IDs of deleted items. In the case
 * of failure none of the vairiables pointed to the parameters will be
 * altered. If this function succeeds the memory containing the lists
 * needs to be freed using the free() function because it is allocated
 * inside this function.
 * @param cur_env Pointer to the current zdtm library environment.
 * @param pp_new_sync_ids Pointer to a pointer to head of new ID list.
 * @param p_num_new_sync_ids Pointer to var to store num new IDs in.
 * @param pp_mod_sync_ids Pointer to a pointer to head of mod ID list.
 * @param p_num_mod_sync_ids Pointer to var to store num mod IDs in.
 * @param pp_del_sync_ids Pointer to a pointer to head of del ID list.
 * @param p_num_del_sync_ids Pointer to var to store num del IDs in.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully obtained sync ID lists.
 * @retval -1 Failed to send RSY message.
 * @retval -2 Failed to recv response message.
 * @retval -3 Failed, response message is NOT an ASY message.
 * @retval -4 Failed to allocate memory for ID lists.
 */
int _zdtm_obtain_sync_id_lists(zdtm_lib_env *cur_env,
    uint32_t **pp_new_sync_ids, uint16_t *p_num_new_sync_ids,
    uint32_t **pp_mod_sync_ids, uint16_t *p_num_mod_sync_ids,
    uint32_t **pp_del_sync_ids, uint16_t *p_num_del_sync_ids);

/**
 * Obtain Parameter Format
 *
 * The _zdtm_obtain_param_format function attempts to obtain the format
 * which describes the current item for the given type of
 * synchronization and store it in the current library environment for
 * later use.
 * @param cur_env Pointer to the current zdtm library environment.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully obtained parameter format.
 * @retval -1 Failed to send RDI message.
 * @retval -2 Failed to recv response message.
 * @retval -3 Failed, response message is NOT an ADI message.
 * @retval -4 Failed, parameter format already obtained for this lib env.
 */
int _zdtm_obtain_param_format(zdtm_lib_env *cur_env);

/**
 * State Sync is Done
 * 
 * The _zdtm_state_sync_done function attempts to notify the Zaurus that
 * the the Desktop side of the synchronization is done.
 * @param cur_env Pointer to the current zdtm library environment.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully told the Zaurus sync is done.
 * @retval -1 Failed to send RDS message.
 * @retval -2 Failed to recv response message.
 * @retval -3 Failed, response message is not an AEX message.
 */
int _zdtm_state_sync_done(zdtm_lib_env *cur_env);

/**
 * Disconnect from Zaurus.
 *
 * The zdtm_disconnect function disconnects the current library
 * environment from the Zaurus terminating the capability of
 * synchronizing over the current library environment.
 * @param cur_env Pointer to the current zdtm library environment.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully disconnected from the Zaurus.
 * @retval -1 Failed to close TCP/IP connection to Zaurus.
 */
int _zdtm_disconnect(zdtm_lib_env *cur_env);

#endif
