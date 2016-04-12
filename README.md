# URL Router for C (Based on Uthash hashmap)

This is a simple implementation of a URL Router in C. It uses the Uthash hasmap implementation to store routes and the functions associated with each route.   

You just need to clone this repository and include the "router.h" header in your application and you are all set!  

## Adding Routes    
In router.c, you need to edit the initializeRouter() function to add the routes as per your needs:  
```c
void initializeRouter() {
	addURL("/api/register/user", &registerUser); // These are just examples. registerUser() and authenticateHTTPClient() needs to be declared somewhere
	addURL("/api/auth/user", &authenticateHTTPClient);
}
```  
You need to call the __addURL()__ function with the route you wish to create and the function you want to get executed when a request comes in  
  

Next, in you application just call the __initializeRouter()__ function to add all the routes to the hashmap.  

## Matching Routes  
In you client handler function, just call the __findRoute()__ function with the request URL, request method (GET, PUT, POST, DELETE etc.) and any data receieved from the client.  
```c
void httpClientHandler(char *url, char *method, char *data) {
	Struct Response response = findRoute(url, method, data);

	sendResponse(response); // This sends the response back to the client
}
```  
The __findRoute()__ function will check if the route exists in the hashmap. If yes, then it will execute the function associated with it and it not it will return an error message in the Response struct  
