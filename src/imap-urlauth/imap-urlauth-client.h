#ifndef IMAP_URLAUTH_CLIENT_H
#define IMAP_URLAUTH_CLIENT_H

struct client;
struct mail_storage;

struct client {
	struct client *prev, *next;

	int fd_in, fd_out;
	struct ostream *output;
	struct timeout *to_destroy;
	struct event *event;

	char *username, *service;
	ARRAY_TYPE(const_string) access_apps;

	/* settings: */
	const struct imap_urlauth_settings *set;

	struct imap_urlauth_worker_client *worker_client;

	bool disconnected:1;
};

extern struct client *imap_urlauth_clients;
extern unsigned int imap_urlauth_client_count;

int client_create(const char *service, const char *username,
		  int fd_in, int fd_out,
		  const struct imap_urlauth_settings *set,
		  struct client **client_r);
void client_destroy(struct client *client, const char *reason);

void client_send_line(struct client *client, const char *fmt, ...)
		      ATTR_FORMAT(2, 3);

void client_disconnect(struct client *client, const char *reason);

void clients_destroy_all(void);

#endif
