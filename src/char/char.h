// Copyright (c) Athena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef _CHAR_SQL_H_
#define _CHAR_SQL_H_

#include "../config/core.h"
#include "../common/core.h" // CORE_ST_LAST
#include "../common/db.h"

enum E_CHARSERVER_ST {
	CHARSERVER_ST_RUNNING = CORE_ST_LAST,
	CHARSERVER_ST_SHUTDOWN,
	CHARSERVER_ST_LAST
};

struct mmo_charstatus;

struct char_session_data {
	bool auth; // whether the session is authed or not
	int account_id, login_id1, login_id2, sex;
	int found_char[MAX_CHARS]; // ids of chars on this account
	char email[40]; // e-mail (default: a@a.com) by [Yor]
	time_t expiration_time; // # of seconds 1/1/1970 (timestamp): Validity limit of the account (0 = unlimited)
	int group_id; // permission
	uint8 char_slots;
	uint32 version;
	uint8 clienttype;
	char pincode[4+1];
	uint32 pincode_seed;
	uint16 pincode_try;
	uint32 pincode_change;
	char new_name[NAME_LENGTH];
	char birthdate[10+1];  // YYYY-MM-DD
};

struct online_char_data {
	int account_id;
	int char_id;
	int fd;
	int waiting_disconnect;
	short server; // -2: unknown server, -1: not connected, 0+: id of server
	int pincode_enable;
};

DBMap* online_char_db; // int account_id -> struct online_char_data*

#define MAX_MAP_SERVERS 2

#define DEFAULT_AUTOSAVE_INTERVAL 300*1000

enum {
	TABLE_INVENTORY,
	TABLE_CART,
	TABLE_STORAGE,
	TABLE_GUILD_STORAGE,
};

int memitemdata_to_sql(const struct item items[], int max, int id, int tableswitch);

int mapif_sendall(unsigned char *buf,unsigned int len);
int mapif_sendallwos(int fd,unsigned char *buf,unsigned int len);
int mapif_send(int fd,unsigned char *buf,unsigned int len);

int char_married(int pl1,int pl2);
int char_child(int parent_id, int child_id);
int char_family(int pl1,int pl2,int pl3);

int request_accreg2(int account_id, int char_id);
int save_accreg2(unsigned char* buf, int len);
int login_fd;
extern int char_name_option;
extern char char_name_letters[];
extern bool char_gm_read;
extern int autosave_interval;
extern int save_log;
extern char db_path[];
extern char char_db[256];
extern char scdata_db[256];
extern char cart_db[256];
extern char inventory_db[256];
extern char charlog_db[256];
extern char storage_db[256];
extern char interlog_db[256];
extern char reg_db[256];
extern char skill_db[256];
extern char memo_db[256];
extern char guild_db[256];
extern char guild_alliance_db[256];
extern char guild_castle_db[256];
extern char guild_expulsion_db[256];
extern char guild_member_db[256];
extern char guild_position_db[256];
extern char guild_skill_db[256];
extern char guild_storage_db[256];
extern char party_db[256];
extern char pet_db[256];
extern char mail_db[256];
extern char auction_db[256];
extern char quest_db[256];
extern char homunculus_db[256];
extern char skill_homunculus_db[256];
extern char mercenary_db[256];
extern char mercenary_owner_db[256];
extern char ragsrvinfo_db[256];

extern int db_use_sqldbs; // added for sql item_db read for char server [Valaris]

extern int guild_exp_rate;
extern int log_inter;

#endif /* _CHAR_SQL_H_ */
