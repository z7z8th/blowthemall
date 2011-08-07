var http = require('http');
var RpcHandler = require('deimos').RpcHandler;
var isArray = require('deimos/utils').isArray;
var tracker = require('./tracker.js');

var methods = {
    publish: function(rpc, args) {
        if (!isArray(args)
            || args.length != 2) {
            rpc.invalidParams();
            return;
        }

        tracker.publish(args[0], args[1], rpc);
    },
    unpublish: function(rpc, args) {
        if (!isArray(args)
            || args.length != 1) {
            rpc.invalidParams();
            return;
        }

        tracker.unpublish(args[0], rpc);
    },
    publishTimeout: function(rpc, args) {
        if (args) {
            rpc.invalidParams();
            return;
        }

        tracker.publishTimeout(rpc);
    },
    listFirst: function(rpc, args) {
        if (!isArray(args)
            || args.length != 1) {
            rpc.invalidParams();
            return;
        }

        tracker.listFirst(args[0], rpc);
    },
    list: function(rpc, args) {
        if (!isArray(args)
            || args.length != 2) {
            rpc.invalidParams();
            return;
        }

        tracker.list(args[0], args[1], rpc);
    },
    verify: function(rpc, args) {
        if (!isArray(args)
            || args.length != 2) {
            rpc.invalidParams();
            return;
        }

        tracker.verify(args[0], args[1], rpc);
    },
    altUrls: function(rpc, args) {
        if (args) {
            rpc.invalidParams();
            return;
        }

        tracker.altUrls(rpc);
    },
    friends: function(rpc, args) {
        if (args) {
            rpc.invalidParams();
            return;
        }

        tracker.friends(rpc);
    }
};

http.createServer(function(request, response) {
    if (request.method == 'POST')
        new RpcHandler(request, response, methods);
    else
        response.end();
}).listen(80);
