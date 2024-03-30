// Enable strict mode
"use strict";

// Handle websocket communications
var WebsocketServer = function() {

    // Websocket
    var currentWebsocketHost = "";
    var currentWebsocketObj = null;

    // Websocket connection
    var connectingToWebsocket = true;
    var connectionToWebsocketEstablished = false;

    // Callback for onOpen
    var onOpenCallback = null;

    // Callback for OnClose
    var onCloseCallback = null;

    // Callbacks for onMessage
    var onMessageCallbacks = {};

    // Callbacks for onReturn
    var onReturnCallbacks = {};

    // Current message id
    var currentMessageId = 0;

    // Current channel name
    var currentChannelName = "";

    // Register new onMessage callback
    var registerOnMessageCallback = function (channelName, callback) {
        if (onMessageCallbacks.hasOwnProperty(channelName)) {
            throw "Channel " + channelName + " is registered already.";
        }
        onMessageCallbacks[channelName] = callback;
    };

    // Register new onReturn callback
    var registerOnReturnCallback = function (callback) {
        currentMessageId = (currentMessageId >= Number.MAX_SAFE_INTEGER) ? 0 : (currentMessageId + 1);
        onReturnCallbacks[currentMessageId.toString()] = callback;
    };

    // Send a message
    var sendMessage = function (message) {
        if (typeof message !== "object") {
            throw "Message should be an object";
        }
        currentWebsocketObj.send(JSON.stringify(message));
    };

    // Handler for messages coming from the server
    var onMessageMain = function (message) {
        var messageData = JSON.parse(message.data);
        if (messageData.hasOwnProperty("channel") && onMessageCallbacks.hasOwnProperty(messageData.channel)) {
            onMessageCallbacks[messageData.channel](messageData);
        }
        else {
            console.log("No callback found for message " + message);
        }
    };

    // Handler for messages returning
    var onMessageReturnHandler = function (message) {
        var functionName = message.function;
        var isCallback = false;
        if (!isCallback) {
            var messageId = message.message_id;
            if (!messageId) {
                return;
            }
            var onReturnCallback = onReturnCallbacks[messageId.toString()];
            delete onReturnCallbacks[messageId.toString()];
            if (typeof onReturnCallback === "function") {
                var parsedResults = {};
                try {
                    parsedResults = JSON.parse(message.results);
                } catch(e) {
                }
                var onReturnMessage = {
                    "results": parsedResults,
                    "return_value": message.return_value,
                    "error_code": message.error_code,
                    "error_message": message.error_message
                };
                onReturnCallback(onReturnMessage);
            }
        }
    };

    // Handler for websocket errors
    var onWebSocketError = function (error) {
        console.error("Web Socket onError: %o", JSON.stringify(error));
        if (connectingToWebsocket && !connectionToWebsocketEstablished) {
            setTimeout(function () {
                console.log("Trying to re-establish connection after error...");
                connectWebSocket();
            }, 1000);
        }
    };

    // Handler for websocket close
    var onWebSocketClose = function (event) {
        console.log("Web Socket OnClose: Socket is now closed");
        connectionToWebsocketEstablished = false;
        if (onCloseCallback) {
            onCloseCallback();
        }
    };

    // Handler for websocket open
    var onWebSocketOpen = function (event) {
        console.log("Web Socket OnOpen: Socket is now open");
        connectingToWebsocket = false;
        connectionToWebsocketEstablished = true;
        if (onOpenCallback) {
            onOpenCallback();
        }
    };

    // Connect to websocket server
    var connectWebSocket = function () {
        console.log("Web Socket Connect: Connecting to " + currentWebsocketHost);
        currentWebsocketObj = new WebSocket(currentWebsocketHost);
        connectingToWebsocket = true;
        connectionToWebsocketEstablished = false;
        currentWebsocketObj.onerror = onWebSocketError;
        currentWebsocketObj.onclose = onWebSocketClose;
        currentWebsocketObj.onopen = onWebSocketOpen;
        currentWebsocketObj.onmessage = onMessageMain;
        registerOnMessageCallback(currentChannelName, onMessageReturnHandler);
    };

    // Call method on the webserver
    var callServerMethod = function (channelName, functionName, args) {
        return new Promise( function (resolve, reject) {
            registerOnReturnCallback(function(message) {
                console.log("Method " + functionName + ": Received result " + JSON.stringify(message));
                if (message.error_code === 0) {
                    resolve(message.results);
                }
                else {
                    var error = new Error(message.error_message);
                    error.errorCode = message.error_code;
                    reject(error);
                }
            });
            console.log("Method " + functionName + ": Called with args " + JSON.stringify(args));
            var message = {};
            message.message_id = currentMessageId.toString();
            message.channel = currentChannelName;
            message.function = functionName;
            message.args = args;
            sendMessage(message);
        });
    };

    // ------ Public API ------ //
    var pub = {};

    // Constructor
    pub.construct = function (websocketHost, channelName, openCallback, closeCallback) {

        // Init data
        currentWebsocketObj = null;
        currentWebsocketHost = websocketHost;
        currentMessageId = 0;
        currentChannelName = channelName;
        connectingToWebsocket = false;
        connectionToWebsocketEstablished = false;
        onOpenCallback = openCallback;
        onCloseCallback = closeCallback;
        onMessageCallbacks = {};
        onReturnCallbacks = {};

        // Try connecting
        try {
            setTimeout(function () {
                connectWebSocket();
            }, 1000);
        }
        catch (e) {
            console.error("Web Socket Exception: %o", JSON.stringify(e));
        }
    };

    // Shutdown
    pub.shutdown = function () {
        var args = {};
        return callServerMethod(currentChannelName, "shutdown", args);
    };

    // Run module file
    pub.runModuleFile = function (file) {
        var args = {
            "file": file
        };
        return callServerMethod(currentChannelName, "run_module_file", args);
    };

    // Run module file and get results
    pub.runModuleFileResults = function (file, results_id, keep_results) {
        var args = {
            "file": file,
            "results_id": results_id,
            "keep_results": keep_results
        };
        return callServerMethod(currentChannelName, "run_module_file_results", args);
    };

    // Run module command
    pub.runModuleCommand = function (command) {
        var args = {
            "command": command
        };
        return callServerMethod(currentChannelName, "run_module_command", args);
    };

    // Run module command and get results
    pub.runModuleCommandResults = function (command, results_id, keep_results) {
        var args = {
            "command": command,
            "results_id": results_id,
            "keep_results": keep_results
        };
        return callServerMethod(currentChannelName, "run_module_command_results", args);
    };

    // Clear module results
    pub.clearModuleResults = function (results_id) {
        var args = {
            "results_id": results_id
        };
        return callServerMethod(currentChannelName, "clear_module_results", args);
    };

    // Clear all module results
    pub.clearAllModuleResults = function () {
        var args = {};
        return callServerMethod(currentChannelName, "clear_all_module_results", args);
    };

    // Determine if module result exists
    pub.doesModuleResultExist = function (results_id) {
        var args = {
            "results_id": results_id
        };
        return callServerMethod(currentChannelName, "does_module_result_exist", args);
    };

    // Get module result size
    pub.getModuleResultSize = function (results_id) {
        var args = {
            "results_id": results_id
        };
        return callServerMethod(currentChannelName, "get_module_result_size", args);
    };

    // Get module results
    pub.getModuleResults = function (results_id) {
        var args = {
            "results_id": results_id
        };
        return callServerMethod(currentChannelName, "get_module_results", args);
    };

    // Return our public api
    return pub;
}();

//# sourceURL=websocket.js
