var PUBLISH_TIMEOUT = 10;
var ALT_URLS = {};
var FRIENDS = [];

function publish(gameId, portNumber)
{
}

function unpublish(port)
{
}

function publishTimeout()
{
    rpc.response(PUBLISH_TIMEOUT);
}

function listFirst(gameId)
{
}

function list(gameId, offset)
{
}

function verify(address, port)
{
}

function altUrls()
{
    rpc.response(ALT_URLS);
}

function friends()
{
    rpc.response(FRIENDS);
}

exports.publish = publish;
exports.unpublish = unpublish;
exports.publishTimeout = publishTimeout;
exports.listFirst = listFirst;
exports.list = list;
exports.verify = verify;
exports.altUrls = altUrls;
exports.friends = friends;
