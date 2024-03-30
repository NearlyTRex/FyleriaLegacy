// Enable strict mode
"use strict";

// Handle save management
var SaveManager = function() {

    // Current server object
    var currentServerObject = null;

    // Load save manager
    var loadSaveManager = function () {
        var cmd = `
import saves.savemanager
import saves.savetypes`;
        return currentServerObject.runModuleCommand(cmd);
    };

    // Get save file type names
    var getSaveFileTypeNames = function () {
        var cmd = "saves.savetypes.GetSaveFileTypeNames()";
        var resultid = "SaveManager:getSaveFileTypeNames";
        return currentServerObject.runModuleCommandResults(cmd, resultid, true);
    };

    // Get save capacity
    var getSaveCapacity = function () {
        var cmd = "saves.savemanager.GetSaveCapacity()";
        var resultid = "SaveManager:getSaveCapacity";
        return currentServerObject.runModuleCommandResults(cmd, resultid, true);
    };

    // Get all saves
    var getAllSaves = function () {
        var cmd = "saves.savemanager.GetAllSaves()";
        var resultid = "SaveManager:getAllSaves";
        return currentServerObject.runModuleCommandResults(cmd, resultid, false);
    };

    // Initialize empty save slots
    var initializeEmptySaveSlots = function () {
        var cmd = "saves.savemanager.InitializeEmptySaveSlots()";
        return currentServerObject.runModuleCommand(cmd);
    };

    // Initialize all save slots
    var initializeAllSaveSlots = function () {
        var cmd = "saves.savemanager.InitializeAllSaveSlots()";
        return currentServerObject.runModuleCommand(cmd);
    };

    // Pull save from memory
    var pullSaveFromMemory = function (sSlot, sPartyID) {
        var cmd = "saves.savemanager.PullSaveFromMemory(" + sSlot + ", \"" + sPartyID + "\")";
        return currentServerObject.runModuleCommand(cmd);
    };

    // Push save to memory
    var pushSaveToMemory = function (sSlot) {
        var cmd = "saves.savemanager.PushSaveIntoMemory(" + sSlot + ")";
        return currentServerObject.runModuleCommand(cmd);
    };

    // Load save
    var loadSave = function (sSlot, sSaveJson) {
        var cmd = `
sSaveSlot = %SAVESLOT%
sSaveJson = "%SAVEJSON%"
saves.savemanager.LoadSave(sSaveSlot, sSaveJson)`;
        cmd = cmd.replace(/%SAVESLOT%/g, sSlot);
        cmd = cmd.replace(/%SAVEJSON%/g, sSaveJson);
        return currentServerObject.runModuleCommand(cmd);
    };

    // Unload save
    var unloadSave = function (sSlot) {
        var cmd = "saves.savemanager.UnloadSave(" + sSlot + ")";
        return currentServerObject.runModuleCommand(cmd);
    };

    // Save to file
    var saveToFile = function (sSlot, sFile, sType) {
        var cmd = "saves.savemanager.SaveToFile(" + sSlot + ", \"" + sFile + "\", \"" + sType + "\")";
        return currentServerObject.runModuleCommand(cmd);
    };

    // Load from file
    var loadFromFile = function (sSlot, sFile, sType) {
        var cmd = "saves.savemanager.LoadFromFile(" + sSlot + ", \"" + sFile + "\", \"" + sType + "\")";
        return currentServerObject.runModuleCommand(cmd);
    };

    // Save all to directory
    var saveAllToDirectory = function (sDirectory, sBase, sExt, sType) {
        var cmd = "saves.savemanager.SaveAllToDirectory(\"" + sDirectory + "\", \"" + sBase + "\", \"" + sExt + "\", \"" + sType + "\")";
        return currentServerObject.runModuleCommand(cmd);
    };

    // Load all from directory
    var loadAllFromDirectory = function (sDirectory, sBase, sExt, sType) {
        var cmd = "saves.savemanager.LoadAllFromDirectory(\"" + sDirectory + "\", \"" + sBase + "\", \"" + sExt + "\", \"" + sType + "\")";
        return currentServerObject.runModuleCommand(cmd);
    };

    // ------ UI Updates ------ //

    // Type names have been updated
    var typeNamesUpdated = function () {

        // Update save file type selectors
        for (var i = 0; i < saveFileTypeSelectTags.length; i++) {
            var saveFileTypeTag = saveFileTypeSelectTags[i];
            $(saveFileTypeTag).empty();
            $(saveFileTypeTag).append("<option value=''>Save Type...</option>");
            for (var j = 0; j < saveFileTypeNames.length; j++) {
                if (saveFileTypeNames[j].length > 0 && saveFileTypeNames[j] != "None") {
                    $(saveFileTypeTag).append("<option value='" + saveFileTypeNames[j] + "'>" + saveFileTypeNames[j] + "</option>");
                }
            }
        }
    };

    // Save capacity updated
    var saveCapacityUpdated = function () {

        // Update save slot selectors
        for (var i = 0; i < saveSlotSelectTags.length; i++) {
            var saveSlotTag = saveSlotSelectTags[i];
            $(saveSlotTag).empty();
            $(saveSlotTag).append("<option value=''>Save Slot...</option>");
            for (var j = 0; j < saveCapacity; j++) {
                $(saveSlotTag).append("<option value='" + j + "'>" + j + "</option>");
            }
        }

        // Update save data rows
        $(savaDataGroupTag).empty();
        for (var j = 0; j < saveCapacity; j++) {
            var newRow = saveDataGroupRowBase.replace(/%SAVESLOT%/g, j);
            $(savaDataGroupTag).append(newRow);
        }
    };

    // Save data updated
    var saveDataUpdated = function () {

        // Update save descriptions and raw info
        for (var i = 0; i < allSaves.length; i++) {
            var saveSlot = allSaves[i].Slot;
            var saveDescription = allSaves[i].Description;
            var saveTime = allSaves[i].Time;
            var saveRaw = JSON.stringify(allSaves[i]);
            var tagSaveDescription = "#save" + saveSlot + "Data_description";
            var tagSaveRaw = "#save" + saveSlot + "Data_raw";
            saveRaw = saveRaw.replace(/\"/g, "\\\"");
            $(tagSaveDescription).html(saveDescription);
            $(tagSaveRaw).val(saveRaw);
        }
    };

    // ------ Buttons ------ //

    // Register button handlers
    var registerButtonHandlers = function () {
        $(document).on("click", "#initalizeSaveSlots_submit", function(event) {
            initializeAllSaveSlots().then(function () {
                return getAllSaves();
            }).then(function (results) {
                allSaves = results;
                saveDataUpdated();
                displayResults(true, "Initialized all save slots.");
            }).catch(onError);
        });

        $(document).on("click", "#pullSave_submit", function(event) {
            var sSlot = $("#pullSave_saveSlot").val() || "";
            var sPartyID = $("#pullSave_partyID").val() || "";
            if (sSlot.length == 0 || sPartyID.length == 0) {
                onError("Error: Invalid save slot or party ID.");
                return;
            }
            pullSaveFromMemory(sSlot, sPartyID).then(function () {
                return getAllSaves();
            }).then(function (results) {
                allSaves = results;
                saveDataUpdated();
                displayResults(true, "Pulled save for party " + sPartyID + " and placed in slot " + sSlot + ".");
            }).catch(onError);
        });

        $(document).on("click", "#pushSave_submit", function(event) {
            var sSlot = $("#pushSave_saveSlot").val() || "";
            if (sSlot.length == 0) {
                onError("Error: Invalid save slot.");
                return;
            }
            pushSaveToMemory(sSlot).then(function () {
                displayResults(true, "Pushed save in slot " + sSlot + " into party manager.");
            }).catch(onError);
        });

        $(document).on("click", "#loadSave_submit", function(event) {
            var sSlot = $("#loadSave_saveSlot").val() || "";
            var sSaveJson = $("#loadSave_textarea").val() || "";
            if (sSlot.length == 0 || sSaveJson.length == 0) {
                onError("Error: Invalid save slot or save json.");
                return;
            }
            loadSave(sSlot, sSaveJson).then(function () {
                return getAllSaves();
            }).then(function (results) {
                allSaves = results;
                saveDataUpdated();
                displayResults(true, "Loaded save into slot " + sSlot + ".");
            }).catch(onError);
        });

        $(document).on("click", "#unloadSave_submit", function(event) {
            var sSlot = $("#unloadSave_saveSlot").val() || "";
            if (sSlot.length == 0) {
                onError("Error: Invalid save slot.");
                return;
            }
            unloadSave(sSlot).then(function () {
                return initializeEmptySaveSlots();
            }).then(function () {
                return getAllSaves();
            }).then(function (results) {
                allSaves = results;
                saveDataUpdated();
                displayResults(true, "Unloaded save from slot " + sSlot + ".");
            }).catch(onError);
        });

        $(document).on("click", "#loadFromFile_submit", function(event) {
            var sSlot = $("#loadFromFile_saveSlot").val() || "";
            var sFile = $("#loadFromFile_filename").val() || "";
            var sType = $("#loadFromFile_saveType").val() || "";
            if (sSlot.length == 0 || sFile.length == 0 || sType.length == 0) {
                onError("Error: Invalid save slot, filename, or save type.");
                return;
            }
            loadFromFile(sSlot, sFile, sType).then(function () {
                return getAllSaves();
            }).then(function (results) {
                allSaves = results;
                saveDataUpdated();
                displayResults(true, "Loaded save from file " + sFile + " into slot " + sSlot + ".");
            }).catch(onError);
        });

        $(document).on("click", "#saveToFile_submit", function(event) {
            var sSlot = $("#saveToFile_saveSlot").val() || "";
            var sFile = $("#saveToFile_filename").val() || "";
            var sType = $("#saveToFile_saveType").val() || "";
            if (sSlot.length == 0 || sFile.length == 0 || sType.length == 0) {
                onError("Error: Invalid save slot, filename, or save type.");
                return;
            }
            saveToFile(sSlot, sFile, sType).then(function () {
                displayResults(true, "Saved slot " + sSlot + " into file " + sFile + ".");
            }).catch(onError);
        });

        $(document).on("click", "#saveAllToDir_submit", function(event) {
            var sDir = $("#saveAllToDir_directory").val() || "";
            var sBase = $("#saveAllToDir_basename").val() || "";
            var sExt = $("#saveAllToDir_extension").val() || "";
            var sType = $("#saveAllToDir_saveType").val() || "";
            if (sDir.length == 0 || sBase.length == 0 || sExt.length == 0 || sType.length == 0) {
                onError("Error: Invalid directory, basename, extension, or save type.");
                return;
            }
            saveAllToDirectory(sDir, sBase, sExt, sType).then(function () {
                displayResults(true, "Saved all saves into directory " + sDir + " with a save type of " + sType + ".");
            }).catch(onError);
        });

        $(document).on("click", "#loadAllFromDir_submit", function(event) {
            var sDir = $("#loadAllFromDir_directory").val() || "";
            var sBase = $("#loadAllFromDir_basename").val() || "";
            var sExt = $("#loadAllFromDir_extension").val() || "";
            var sType = $("#loadAllFromDir_saveType").val() || "";
            if (sDir.length == 0 || sBase.length == 0 || sExt.length == 0 || sType.length == 0) {
                onError("Error: Invalid directory, basename, extension, or save type.");
                return;
            }
            loadAllFromDirectory(sDir, sBase, sExt, sType).then(function () {
                return getAllSaves();
            }).then(function (results) {
                allSaves = results;
                saveDataUpdated();
                displayResults(true, "Loaded all saves from directory " + sDir + " with a save type of " + sType + ".");
            }).catch(onError);
        });
    };

    // Local data
    var saveFileTypeNames = [];
    var saveCapacity = 0;
    var allSaves = [];

    // Tags
    var saveSlotSelectTags = [
        "#pullSave_saveSlot",
        "#pushSave_saveSlot",
        "#loadSave_saveSlot",
        "#unloadSave_saveSlot",
        "#loadFromFile_saveSlot",
        "#saveToFile_saveSlot"
    ];
    var saveFileTypeSelectTags = [
        "#loadFromFile_saveType",
        "#saveToFile_saveType",
        "#saveAllToDir_saveType",
        "#loadAllFromDir_saveType"
    ];
    var savaDataGroupTag = "#saveDataGroup";

    // Base strings
    var saveDataGroupRowBase = `
<div class="row">
    <div class="col-sm-6">
        <div class="card">
            <div class="card-header">Save %SAVESLOT%</div>
            <div class="card-body">
                <p class="card-text" id="save%SAVESLOT%Data_description">Save description.</p>
            </div>
        </div>
    </div>
    <div class="col-sm-6">
        <div class="form-group">
            <textarea style="resize: none;" class="form-control" rows="3" id="save%SAVESLOT%Data_raw" placeholder="Raw save data" readonly></textarea>
        </div>
    </div>
</div>`;

    // ------ Public API ------ //
    var pub = {};

    // Init
    pub.init = function (serverObj) {
        currentServerObject = serverObj;
        loadSaveManager().then(function () {
            return getSaveFileTypeNames();
        }).then(function (results) {
            saveFileTypeNames = results;
            typeNamesUpdated();
            return getSaveCapacity();
        }).then(function (results) {
            saveCapacity = results;
            saveCapacityUpdated();
            return initializeEmptySaveSlots();
        }).then(function () {
            return getAllSaves();
        }).then(function (results) {
            allSaves = results;
            saveDataUpdated();
            registerButtonHandlers();
        });
    };

    // Return our public api
    return pub;
}();

//# sourceURL=save_manager.js
