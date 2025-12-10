#ifndef PORT_HH
#define PORT_HH

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*!
 * \brief Port poprzez który realizowana jest komunikacja z klientem
 *
 * Porzez ten port realizowana jest komunikacja z zewnętrzną
 * aplikacją klienta.
 */
#define PORT  6217

#endif
