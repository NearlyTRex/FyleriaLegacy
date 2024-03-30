// Enable strict mode
"use strict";

// Handle rest communications
var RestServer = function() {

    // Rest
    var currentRestHost = "";

    // Callback for onOpen
    var onOpenCallback = null;

    // Callback for OnClose
    var onCloseCallback = null;

    // Constants
    const XHR_READYSTATE_UNSENT = 0;
    const XHR_READYSTATE_OPENED = 1;
    const XHR_READYSTATE_HEADERS_RECEIVED = 2;
    const XHR_READYSTATE_LOADING = 3;
    const XHR_READYSTATE_DONE = 4;
    const HTTP_CODE_OK = 200;
    const HTTP_CODE_CREATED = 201;
    const HTTP_CODE_ACCEPTED = 202;
    const HTTP_CODE_BADREQUEST = 400;
    const HTTP_CODE_NOTFOUND = 404;
    const HTTP_CODE_CONFLICT = 409;

    // Validate ready state
    var isSuccessReadyState = function (code) {
        switch (code)
        {
            case XHR_READYSTATE_DONE:
                return true;
            default:
                return false;
        }
    };

    // Validate http code
    var isSuccessHttpCode = function (code) {
        switch (code)
        {
            case HTTP_CODE_OK:
            case HTTP_CODE_CREATED:
            case HTTP_CODE_ACCEPTED:
                return true;
            default:
                return false;
        }
    };

    // Handler for rest close
    var onRestClose = function () {
        console.log("Rest OnClose: Rest is now closed");
        if (onCloseCallback) {
            onCloseCallback();
        }
    };

    // Handler for rest open
    var onRestOpen = function () {
        console.log("Rest OnOpen: Rest is now open");
        if (onOpenCallback) {
            onOpenCallback();
        }
    };

    // Call method on the webserver
    var callServerMethodGet = function (method, args) {
        console.log("Call server method " + method + " with args " + JSON.stringify(args));
        return new Promise( function (resolve, reject) {
            var url = currentRestHost + "/api/" + method;
            var data = JSON.stringify(args);
            var jqXHR = $.getJSON(url, data);
            jqXHR.done(function (data, textStatus) {
                resolve(data);
            });
            jqXHR.fail(function (jqXHR, textStatus, errorThrown) {
                reject(errorThrown);
            });
        });
    };
    var callServerMethodPost = function (method, args) {
        console.log("Call server method " + method + " with args " + JSON.stringify(args));
        return new Promise( function (resolve, reject) {
            var url = currentRestHost + "/api/" + method;
            var data = JSON.stringify(args);
            var jqXHR = $.post(url, data, null, "json");
            jqXHR.done(function (data, textStatus) {
                resolve(data);
            });
            jqXHR.fail(function (jqXHR, textStatus, errorThrown) {
                reject(errorThrown);
            });
        });
    };

    // ------ Public API ------ //
    var pub = {};

    // Constructor
    pub.construct = function (restHost, openCallback, closeCallback) {

        // Init data
        currentRestHost = restHost;
        onOpenCallback = openCallback;
        onCloseCallback = closeCallback;

        // Open connection
        onRestOpen();
    };

    // Shutdown
    pub.shutdown = function () {};

    // Run module file
    pub.runModuleFile = function (file) {
        var args = {
            "file": file
        };
        return callServerMethodPost("run_module_file", args);
    };

    // Run module file and get results
    pub.runModuleFileResults = function (file, results_id, keep_results) {
        var args = {
            "file": file,
            "results_id": results_id,
            "keep_results": keep_results
        };
        return callServerMethodPost("run_module_file_results", args);
    };

    // Run module command
    pub.runModuleCommand = function (command) {
        var args = {
            "command": command
        };
        return callServerMethodPost("run_module_command", args);
    };

    // Run module command and get results
    pub.runModuleCommandResults = function (command, results_id, keep_results) {
        var args = {
            "command": command,
            "results_id": results_id,
            "keep_results": keep_results
        };
        return callServerMethodPost("run_module_command_results", args);
    };

    // Clear module results
    pub.clearModuleResults = function (results_id) {
        var args = {
            "results_id": results_id
        };
        return callServerMethodPost("clear_module_results", args);
    };

    // Clear all module results
    pub.clearAllModuleResults = function () {
        var args = {};
        return callServerMethodPost("clear_all_module_results", args);
    };

    // Determine if module result exists
    pub.doesModuleResultExist = function (results_id) {
        var args = {
            "results_id": results_id
        };
        return callServerMethodGet("does_module_result_exist", args);
    };

    // Get module result size
    pub.getModuleResultSize = function (results_id) {
        var args = {
            "results_id": results_id
        };
        return callServerMethodGet("get_module_result_size", args);
    };

    // Get module results
    pub.getModuleResults = function (results_id) {
        var args = {
            "results_id": results_id
        };
        return callServerMethodGet("get_module_results", args);
    };

    // Return our public api
    return pub;
}();

//# sourceURL=rest.js
