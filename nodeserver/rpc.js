var isArray = require('deimos/utils').isArray;
var tracker = require('./tracker.js');

function checkParams(rpc, args, paramsNumber)
{
    if (!isArray(args)
        || args.length != paramsNumber) {
        rpc.invalidParams();
        return false;
    }
    return true;
}

var methods = {
    publish: function(rpc, args) {
        if (checkParams(rpc, args, 3))
            tracker.publish(args[0], args[1], args[2], rpc);
    },
    unpublish: function(rpc, args) {
        if (checkParams(rpc, args, 1))
            tracker.unpublish(args[0], rpc);
    },
    publishTimeout: function(rpc, args) {
        if (checkParams(rpc, args, 0))
            tracker.publishTimeout(rpc);
    },
    listFirst: function(rpc, args) {
        if (checkParams(rpc, args, 2))
            tracker.listFirst(args[0], args[1], rpc);
    },
    list: function(rpc, args) {
        if (checkParams(rpc, args, 3))
            tracker.list(args[0], args[1], args[2], rpc);
    },
    verify: function(rpc, args) {
        if (checkParams(rpc, args, 2))
            tracker.verify(args[0], args[1], rpc);
    },
    altUrls: function(rpc, args) {
        if (checkParams(rpc, args, 0))
            tracker.altUrls(rpc);
    },
    altTrackers: function(rpc, args) {
        if (checkParams(rpc, args, 0))
            tracker.altTrackers(rpc);
    },
    supportedGames: function(rpc, args) {
        if (checkParams(rpc, args, 0))
            tracker.supportedGames(rpc);
    }
};

exports.methods = methods;
