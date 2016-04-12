#ifndef _router_h
#define _router_h

#ifndef UTHASH
#include <uthash.h>
#define UTHASH
#endif

/*
 * A variable of this struct is returned when the respective router function gets executed. It contains the response
 * message and the http status code
 */
struct Response {
	char *responseMessage;
	int httpStatusCode;
};

/*
 * This is a hashmap containing all the URLs defining the REST API. The key is the REST URL and the value is the function
 * with the URL. For ex. Key might be "/api/auth" and the function that's supposed to run when we get a match for this URL 
 * will be authenticateClient()
 */
struct RestAPI {
	char *restUrl;
	struct Response (*func)(char *method, char *data);
	UT_hash_handle hh;
};

/*
 * This is called in the HTTP server client handler. The Client handler passes the URL requested by the client and then
 * this function searches the RestAPI hashmap if the route exists. If it does, it executes the function associated with it
 * by passing the method and MHD_connection struct parameters to it. It returns the result of the operation back to the 
 * handler function
 */
struct Response findRoute(char *url, char *method, char *data);

/*
 * This adds routes to the RestAPI hashmap
 */
void initializeRouter();


#endif