/*
 * Copyright 2005-2007 Andrew De Ponte
 * 
 * This file is part of lib_zdtm_sync.
 * 
 * lib_zdtm_sync is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or any
 * later version.
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

#include "zdtm_sync.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int r, retval;

    /* Set up a fake message */
    zdtm_lib_env cur_env;
    zdtm_msg msg;
    
    memset(&cur_env, 0, sizeof(zdtm_lib_env));

    retval = _zdtm_open_log(&cur_env);
    printf("_zdtm_open_log returned (%d).\n", retval);

    /* Make a simple RAY msg. */
    printf("RAY\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RAY_MSG_TYPE, MSG_TYPE_SIZE);
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);
    

    /* Make a simple RIG msg. */
    printf("RIG\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RIG_MSG_TYPE, MSG_TYPE_SIZE);
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);

    /* Make a simple RRL msg. */
    printf("RRL pw abcd\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RRL_MSG_TYPE, MSG_TYPE_SIZE);
    msg.body.cont.rrl.pw_size = 4;
    msg.body.cont.rrl.pw = "abcd";
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);
    
    /* Make a simple RMG msg. */
    printf("RMG\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RMG_MSG_TYPE, MSG_TYPE_SIZE);
    msg.body.cont.rmg.uk = 0x01;
    msg.body.cont.rmg.sync_type = SYNC_TYPE_TODO;
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);
    
    /* Make a simple RMS msg. */
    printf("RMS\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RMS_MSG_TYPE, MSG_TYPE_SIZE);
    msg.body.cont.rms.log_size = 12;
    memset(msg.body.cont.rms.log, 0xfe, 12);
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);

    /* Make a simple RTG msg. */
    printf("RTG\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RTG_MSG_TYPE, MSG_TYPE_SIZE);
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);
    
    /* Make a simple RTS msg. */
    printf("RTS\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RTS_MSG_TYPE, MSG_TYPE_SIZE);
    memcpy(msg.body.cont.rts.date, "20060521010000", RTS_DATE_LEN);
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);
    
    /* Make a simple RDI msg. */
    printf("RDI\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RDI_MSG_TYPE, MSG_TYPE_SIZE);
    msg.body.cont.rdi.sync_type = SYNC_TYPE_TODO;
    msg.body.cont.rdi.uk = 0x07;
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);

    /* Make a simple RSY msg. */
    printf("RSY\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RSY_MSG_TYPE, MSG_TYPE_SIZE);
    msg.body.cont.rsy.sync_type = SYNC_TYPE_TODO;
    msg.body.cont.rsy.uk = 0x07;
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);

    /* Make a simple RDR msg. */
    printf("RDR\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RDR_MSG_TYPE, MSG_TYPE_SIZE);
    msg.body.cont.rdr.sync_type = SYNC_TYPE_TODO;
    msg.body.cont.rdr.num_sync_ids = 1;
    msg.body.cont.rdr.sync_id = 0xdeadbeef;
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);

    /* Make a simple RDW msg var 1. */
    printf("RDW - 1\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RDW_MSG_TYPE, MSG_TYPE_SIZE);
    msg.body.cont.rdw.sync_type = SYNC_TYPE_TODO;
    msg.body.cont.rdw.num_sync_ids = 1;
    msg.body.cont.rdw.sync_id = 0xdeadbeef;
    msg.body.cont.rdw.variation = 1;
    memset(msg.body.cont.rdw.vars.one.padding, 0xff, sizeof(msg.body.cont.rdw.vars.one.padding));
    msg.body.cont.rdw.cont.todo.category_len = 5;
    msg.body.cont.rdw.cont.todo.category = "CRUD";
    memcpy(msg.body.cont.rdw.cont.todo.start_date, "abcde", 5);
    memcpy(msg.body.cont.rdw.cont.todo.due_date, "abcde", 5);
    memcpy(msg.body.cont.rdw.cont.todo.completed_date, "abcde", 5);
    msg.body.cont.rdw.cont.todo.progress = 0xa5;
    msg.body.cont.rdw.cont.todo.priority = 0xff;
    msg.body.cont.rdw.cont.todo.description_len = 5;
    msg.body.cont.rdw.cont.todo.description = "CRUD";
    msg.body.cont.rdw.cont.todo.notes_len = 5;
    msg.body.cont.rdw.cont.todo.notes = "CRUD";

    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);

    /* Make a simple RDW msg var 2. */
    printf("RDW - 2\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RDW_MSG_TYPE, MSG_TYPE_SIZE);
    msg.body.cont.rdw.sync_type = SYNC_TYPE_TODO;
    msg.body.cont.rdw.num_sync_ids = 1;
    msg.body.cont.rdw.sync_id = 0xdeadbeef;
    msg.body.cont.rdw.variation = 2;

    msg.body.cont.rdw.vars.two.attribute = 0xfe;

    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);


    /* Make a simple RDW msg var 3. */
    printf("RDW - 3\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RDW_MSG_TYPE, MSG_TYPE_SIZE);
    msg.body.cont.rdw.sync_type = SYNC_TYPE_TODO;
    msg.body.cont.rdw.num_sync_ids = 1;
    msg.body.cont.rdw.sync_id = 0xdeadbeef;
    msg.body.cont.rdw.variation = 3;
    msg.body.cont.rdw.vars.three.attribute = 0xfe;
    memcpy(msg.body.cont.rdw.vars.three.card_created_date_time, "abcde", 5);
    msg.body.cont.rdw.cont.todo.category_len = 5;
    msg.body.cont.rdw.cont.todo.category = "CRUD";
    memcpy(msg.body.cont.rdw.cont.todo.start_date, "abcde", 5);
    memcpy(msg.body.cont.rdw.cont.todo.due_date, "abcde", 5);
    memcpy(msg.body.cont.rdw.cont.todo.completed_date, "abcde", 5);
    msg.body.cont.rdw.cont.todo.progress = 0xa5;
    msg.body.cont.rdw.cont.todo.priority = 0xff;
    msg.body.cont.rdw.cont.todo.description_len = 5;
    msg.body.cont.rdw.cont.todo.description = "CRUD";
    msg.body.cont.rdw.cont.todo.notes_len = 5;
    msg.body.cont.rdw.cont.todo.notes = "CRUD";

    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);

    /* Make a simple RDD msg. */
    printf("RDD\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RDD_MSG_TYPE, MSG_TYPE_SIZE);
    msg.body.cont.rdd.sync_type = SYNC_TYPE_TODO;
    msg.body.cont.rdd.num_sync_ids = 1;
    msg.body.cont.rdd.sync_id = 0xdeadbeef;
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);

    /* Make a simple RDD msg. */
    printf("RDD\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RDD_MSG_TYPE, MSG_TYPE_SIZE);
    msg.body.cont.rdd.sync_type = SYNC_TYPE_TODO;
    msg.body.cont.rdd.num_sync_ids = 1;
    msg.body.cont.rdd.sync_id = 0xdeadbeef;
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);

    /* Make a simple RDS msg. */
    printf("RDS\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RDS_MSG_TYPE, MSG_TYPE_SIZE);
    msg.body.cont.rds.sync_type = SYNC_TYPE_TODO;
    msg.body.cont.rds.status = 0x07;
    memset(msg.body.cont.rds.null_bytes, 0, 
            sizeof(msg.body.cont.rds.null_bytes));
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);

    /* Make a simple RQT msg. */
    printf("RQT\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RQT_MSG_TYPE, MSG_TYPE_SIZE);
    memset(msg.body.cont.rqt.null_bytes, 0, 
            sizeof(msg.body.cont.rqt.null_bytes));
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);

    /* Make a simple RLR msg. */
    printf("RLR\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RLR_MSG_TYPE, MSG_TYPE_SIZE);
    msg.body.cont.rlr.sync_type = SYNC_TYPE_TODO;
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);

    /* Make a simple RGE msg. */
    printf("RGE\n");
    memset(&msg, 0, sizeof(zdtm_msg));
    memcpy(msg.body.type, RGE_MSG_TYPE, MSG_TYPE_SIZE);
    msg.body.cont.rge.path_len = strlen("/home/zaurus/Applications/dtm/SLTODO.BOX");
    msg.body.cont.rge.path = "/home/zaurus/Applications/dtm/SLTODO.BOX";
    r = _zdtm_prepare_message(&cur_env, &msg);
    if(r < 0){ printf("Failed: %d\n", r); return 1; }
    retval = _zdtm_dump_msg_log(&cur_env, &msg);
    printf("_zdtm_dump_msg_log returned (%d).\n", retval);

    retval = _zdtm_close_log(&cur_env);
    printf("_zdtm_close_log returned (%d).\n", retval);

    return 0;
}
