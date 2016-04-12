#include <stdio.h>
#include <stdbool.h>
#include "uthash.h"

/*
 * This is a hashmap containing all the URLs defining the REST API. The key is the REST URL and the value is the function
 * with the URL. For ex. Key might be "/api/auth" and the function that's supposed to run when we get a match for this URL 
 * will be authenticateClient()
 */
struct RestAPI {
	char *restUrl;
	struct Response (*func)(const char *method, const char *data);
	UT_hash_handle hh;
};

// Global structure of the hashmap. Can we make this not global??
struct RestAPI *router = NULL;

/*
 * This is called in the HTTP server client handler. The Client handler passes the URL requested by the client and then
 * this function searches the RestAPI hashmap if the route exists. If it does, it executes the function associated with it
 * by passing the method and data parameters to it. It returns the result of the operation back to the 
 * handler function
 */
struct Response findRoute(const char *url, const char *method, const char *data) {
	struct RestAPI *tmp;
	struct Response errorResponse;

	HASH_FIND_STR(router, url, tmp);
	if(tmp != NULL) {
		struct Response t = tmp->func(method, data);
		return t;
	} else { // Route not found in the RestAPI hashmap
		errorResponse.responseMessage = "Not Implemented";
		errorResponse.httpStatusCode = NOT_IMPLEMENTED;

		return errorResponse;
	}
}

/*
 * This adds the URL to the RestAPI hashmap
 */
void addURL(char *url, struct Response (*restFunc)()) {
	struct RestAPI *tmp = malloc(sizeof(struct RestAPI));

	tmp->restUrl = url;
	tmp->func = restFunc;
	HASH_ADD_STR(router, restUrl, tmp);

	printf("Added Route: %s\n", url);
}

/*
 * This adds routes to the RestAPI hashmap
 */
void initializeRouter() {
	addURL("/api/register/user", &registerUser); // These are just examples. registerUser() and authenticateHTTPClient() needs to be declared somewhere
	addURL("/api/auth/user", &authenticateHTTPClient);
}