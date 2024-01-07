/* Copyright (C) 2015, Wazuh Inc.
 * Copyright (C) 2009 Trend Micro Inc.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation.
 */

#ifndef MANAGE_AGENTS_H
#define MANAGE_AGENTS_H

#include "shared.h"
#include "sec.h"
#include <cJSON.h>

#ifndef ARGV0
#define ARGV0 "manage_agents"
#endif

/** Prototypes **/

/* Read any input from the user (stdin) */
char *read_from_user(void);

/* Add or remove an agent */
int add_agent(int json_output);
int remove_agent(int json_output);

/* Extract or import a key */
int k_extract(const char *cmdextract, int json_output);
int k_import(const char *cmdimport);
int k_bulkload(const char *cmdbulk);

/**
 * @brief Converts invalid hostnames to valid by eliminating
 * invalid characters
 *
 * @param u_name name to be converted
 * */
void OS_ConvertToValidAgentName(char *u_name);

/* Validation functions */
int OS_IsValidName(const char *u_name);
int OS_IsValidID(const char *id);
int IDExist(const char *id, int discard_removed);
int NameExist(const char *u_name);
char *IPExist(const char *u_ip);
char *getNameById(const char *id);
int OS_AddNewAgent(keystore *keys, const char *id, const char *name, const char *ip, const char *key);
int OS_RemoveAgent(const char *id);
void OS_AddAgentTimestamp(const char *id, const char *name, const char *ip, time_t now);
void OS_RemoveAgentTimestamp(const char *id);
void FormatID(char *id);

/* Print available agents */
int print_agents(int print_status, int active_only, int inactive_only, int csv_output, cJSON *json_output);
int list_agents(int cmdlist);

/* Clear a line */
char *chomp(char *str);

/* Shared variables */
extern time_t time1;
extern time_t time2;
extern time_t time3;
extern long int rand1;
extern long int rand2;
extern fpos_t fp_pos;
extern char shost[];

/* Internal defines */
#define USER_SIZE       514
#define FILE_SIZE       257
#define STR_SIZE        66
#define VALID_AGENT_NAME_CHARS "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_.-"

/* Internal strings */
#define QUIT                "\\q"
#define AGENT_FILE_DELIMS   ","

/* Print agents */
#define PRINT_AVAILABLE     "\nAvailable agents: \n"
#define PRINT_AGENT         "   ID: %s, Name: %s, IP: %s\n"
#define PRINT_AGENT_STATUS  "   ID: %s, Name: %s, IP: %s, %s\n"

/* Add new agent */
#define ADD_NEW         "\n- Adding a new agent"\
                        " (use '\\q' to return to the main menu).\n"\
                        "  Please provide the following:\n"
#define ADD_NAME        "   * A name for the new agent: "
#define ADD_IP          "   * The IP Address of the new agent: "
#define ADD_ID          "   * An ID for the new agent[%s]: "
#define AGENT_INFO      "Agent information:\n   ID:%s\n   Name:%s\n   " \
                        "IP Address:%s\n\n"
#define ADD_CONFIRM     "Confirm adding it?(y/n): "
#define AGENT_ADD       "Agent added with ID %s.\n"
#define ADDED           "Added.\n"
#define ADD_NOT         "Not Adding.\n"
#define PRESS_ENTER     "** Press ENTER to return to the main menu.\n"

/* Add errors */
#define ADD_ERROR_ID    "\n** ID '%s' already present. They must be unique.\n\n"
#define ADD_ERROR_NAME  "\n** Name '%s' already present. Please enter a new name.\n\n"
#define IP_ERROR        "\n** Invalid IP '%s'. Please enter a valid IP Address.\n\n"
#define IP_DUP_ERROR    "\n** Duplicate IP '%s'. Please enter an unique IP Address.\n\n"
#define NO_AGENT        "\n** No agent available. You need to add one first.\n"
#define NO_ID           "\n** Invalid ID '%s' given. ID is not present.\n"
#define NO_KEY          "\n** Invalid authentication key. Starting over again.\n"
#define INVALID_ID      "\n** Invalid ID '%s' given. ID must be numeric (max 8 digits).\n\n"
#define INVALID_NAME    "\n** Invalid name '%s' given. Name must contain only alphanumeric characters (min=2, max=32).\n\n"
#define NO_DEFAULT      "\n** Could not get default ID. Ran out of IDs to try with a max of '%d'. Either need to raise max agents or clean out client.keys.\n\n"
#define SYNTAX_ERROR    "\n** Syntax error at file %s\n\n"

/* Remove agent */
#define REMOVE_ID       "Provide the ID of the agent to be removed (or '\\q' to quit): "
#define REMOVE_CONFIRM  "Confirm deleting it?(y/n): "
#define REMOVE_DONE     "Agent '%s' removed.\n"
#define REMOVE_NOT      "Not removing.\n"

/* Import agent */
#define IMPORT_KEY      "\n* Provide the Key generated by the server.\n" \
                        "* The best approach is to cut and paste it.\n" \
                        "*** OBS: Do not include spaces or new lines.\n\n" \
                        "Paste it here (or '\\q' to quit): "

/* Extract key */
#define EXTRACT_KEY     "Provide the ID of the agent to extract " \
                        "the key (or '\\q' to quit): "
#define EXTRACT_MSG     "\nAgent key information for '%s' is: \n%s\n"

/* Common errors */
#define ERROR_KEYS      "Unable to handle keys file. Exiting.\n"
#define EXTRACT_ERROR   "Unable to extract agent key.\n"
#define INPUT_LARGE     ARGV0 ": Input too large. Not adding it.\n"
#define EXIT            ARGV0 ": Exiting.\n"

#define BANNER          "\n****************************************" \
                        "\n* %s %s Agent manager.%.*s*" \
                        "\n* The following options are available: *" \
                        "\n****************************************\n"

#define BANNER_OPT      "   (A)dd an agent (A).\n" \
                        "   (E)xtract key for an agent (E).\n" \
                        "   (L)ist already added agents (L).\n" \
                        "   (R)emove an agent (R).\n" \
                        "   (Q)uit.\n" \
                        "Choose your action: A,E,L,R or Q: "

#define BANNER_CLIENT   "   (I)mport key from the server (I).\n" \
                        "   (Q)uit.\n" \
                        "Choose your action: I or Q: "

#endif
