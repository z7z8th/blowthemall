var http = require('http');
var RpcHandler = require('deimos').RpcHandler;
var methods = require('./rpc.js').methods;

http.createServer(function(request, response) {
    if (request.method == 'POST')
        new RpcHandler(request, response, methods);
    else
        response.end();
}).listen(80);
