var settings = {
    publishTimeout: 10,
    altUrls: {},
    altTrackers: [],
    supportedGames: []
}

function publish(gameId, port, options, rpc)
{
    dbKey = rpc.httpRequest.connection.remoteAddress + ',' + port;
}

function unpublish(port, rpc)
{
    dbKey = rpc.httpRequest.connection.remoteAddress + ',' + port;
}

function publishTimeout(rpc)
{
    rpc.response(settings.publishTimeout);
}

function listFirst(gameId, options, rpc)
{
}

function list(gameId, options, offset, rpc)
{
}

function verify(address, port, rpc)
{
    dbKey = address + ',' + port;
}

function altUrls(rpc)
{
    rpc.response(settings.altUrls);
}

function altTrackers(rpc)
{
    rpc.response(settings.altTrackers);
}

function supportedGames(rpc)
{
    rpc.response(settings.supportedGames);
}

exports.settings = settings;
exports.publish = publish;
exports.unpublish = unpublish;
exports.publishTimeout = publishTimeout;
exports.listFirst = listFirst;
exports.list = list;
exports.verify = verify;
exports.altUrls = altUrls;
exports.altTrackers = altTrackers;
exports.supportedGames = supportedGames;
