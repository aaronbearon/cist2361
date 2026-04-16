// Aaron Blum
// CIST2361: Lab 11
// 04/10/2026
/*******************************************************************************
getaddrinfo set up.
*******************************************************************************/

#include <arpa/inet.h>  // For inet_ntop
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cstring>
#include <iostream>

using namespace std;

int main() {
  // Set up the environment for getaddrinfo.
  // Node represents the hostname or IP address (like "www.puppies.com") to be
  // resolved.
  const char* node = "www.puppies.com";
  // Service represents the service name (like "http") or port number (like
  // "80") to be resolved.
  const char* service = "http";

  // Hints is an addrinfo structure that that specifies options for getaddrinfo.
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));  // Zero out the structure.
  hints.ai_family = AF_INET;         // Use IPv4.
  hints.ai_socktype = SOCK_STREAM;   // Use TCP.
  hints.ai_flags = AI_CANONNAME;     // Request canonical name.

  // Res is a pointer to an addrinfo structure that will be filled in by
  // getaddrinfo. Here's a description of why res is a pointer to a pointer:
  // After the function call, res will need to point to the addresses of several
  // structures throughout the process. These structures will contain data, but
  // the calling function needs to reflect the data changes in different
  // structures.
  struct addrinfo* res;

  // Print the node and service to be resolved.
  cout << "Node: " << node << endl;
  cout << "Service: " << service << endl;

  // Declare this variable as the return value of getaddrinfo.
  int ret;

  // Note: the instructions say not to call the function, so we can leave the
  // code, but comment it out.

  // // Call getaddrinfo with the specified node, service, hints, and res.
  // ret = getaddrinfo(node, service, &hints, &res);
  // cout << "getaddrinfo returned: " << ret << endl;
  // if (ret == 0) {
  //   cout << "Canonical name: " << res->ai_canonname << endl;
  //   char ipstr[INET_ADDRSTRLEN];
  //   struct sockaddr_in* ipv4 = (struct sockaddr_in*) res->ai_addr;
  //   inet_ntop(res->ai_family, &(ipv4->sin_addr), ipstr, sizeof(ipstr));
  //   cout << "IP address: " << ipstr << endl;
  // } else {
  //   cerr << "getaddrinfo error: " << gai_strerror(ret) << endl;
  // }
  // return ret;

  /* Expected output below (the actual IP address may vary):
      Node: www.puppies.com
      Service: http
      getaddrinfo returned: 0
      Canonical name: www.puppies.com
      IP address: 172.66.149.168
  */
}
