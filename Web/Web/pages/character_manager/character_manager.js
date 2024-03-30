// Enable strict mode
"use strict";

// Handle character management
var CharacterManager = function() {

    // Current server object
    var currentServerObject = null;

    // Load character manager
    var loadCharacterManager = function () {
        var cmd = `
import character.charactermanager
import character.charactertypes`;
        return currentServerObject.runModuleCommand(cmd);
    };

    // Load character from json
    var loadCharacterFromJson = function (sCharacterID, sCharacterJson) {
        var cmd = "character.charactermanager.LoadCharacterFromJson(\"" + sCharacterID + "\", " + JSON.stringify(sCharacterJson) + ")";
        return currentServerObject.runModuleCommand(cmd);
    };

    // Load character from file
    var loadCharacterFromFile = function (sCharacterID, sCharacterFile) {
        var cmd = "character.charactermanager.LoadCharacterFromFile(\"" + sCharacterID + "\", \"" + sCharacterFile + "\")";
        return currentServerObject.runModuleCommand(cmd);
    };

    // Save character to file
    var saveCharacterToFile = function (sCharacterID, sCharacterFile) {
        var cmd = "character.charactermanager.SaveCharacterToFile(\"" + sCharacterID + "\", \"" + sCharacterFile + "\")";
        return currentServerObject.runModuleCommand(cmd);
    };

    // Create character
    var createCharacter = function (sCharacterID) {
        var cmd = "character.charactermanager.CreateCharacter(\"" + sCharacterID + "\")";
        return currentServerObject.runModuleCommand(cmd);
    };

    // Unload character
    var unloadCharacter = function (sCharacterID) {
        var cmd = "character.charactermanager.UnloadCharacter(\"" + sCharacterID + "\")";
        return currentServerObject.runModuleCommand(cmd);
    };

    // Does character exist
    var doesCharacterExist = function (sCharacterID) {
        var cmd = "character.charactermanager.DoesCharacterExist(\"" + sCharacterID + "\")";
        var resultid = "CharacterManager:doesCharacterExist";
        return currentServerObject.runModuleCommandResults(cmd, resultid, true);
    };

    // Generate character
    var generateCharacter = function (sCharacterID, sCharacterGeneratorJson) {
        var cmd = "character.charactermanager.GenerateCharacter(\"" + sCharacterID + "\", \"" + sCharacterGeneratorJson + "\")";
        return currentServerObject.runModuleCommand(cmd);
    };

    // Get character
    var getCharacter = function (sCharacterID) {
        var cmd = "character.charactermanager.GetCharacter(\"" + sCharacterID + "\")";
        var resultid = "CharacterManager:getCharacter";
        return currentServerObject.runModuleCommandResults(cmd, resultid, true);
    };

    // Get all type names
    var getAllTypeNames = function () {
        var cmd = "character.charactertypes.GetAllTypeNames()";
        var resultid = "CharacterManager:getAllTypeNames";
        return currentServerObject.runModuleCommandResults(cmd, resultid, true);
    };

    // ------ UI Updates ------ //

    // Type names have been updated
    var typeNamesUpdated = function () {

        // Create character select tags
        for (var i = 0; i < createCharacterSelectTags.length; i++) {
            var tag = createCharacterSelectTags[i].tag;
            var initial = createCharacterSelectTags[i].initial;
            var type = createCharacterSelectTags[i].type;
            $(tag).empty();
            $(tag).append("<option value=''>" + initial + "</option>");
            for (var j = 0; j < allTypeNames[type].length; j++) {
                var value = allTypeNames[type][j];
                if (value.length > 0) {
                    $(tag).append("<option value='" + value + "'>" + value + "</option>");
                }
            }
        }
    };

    // ------ Buttons ------ //

    // Register button handlers
    var registerButtonHandlers = function () {
        $(document).on("click", "#loadCharacterFromJson_submit", function(event) {
            var sCharID = $("#loadCharacterFromJson_charID").val() || 0;
            var sCharJson = $("#loadCharacterFromJson_textarea").val() || 0;
            if (sCharID.length == 0 || sCharJson.length == 0) {
                onError("Error: Invalid character ID or character json.");
                return;
            }
            loadCharacterFromJson(sCharID, sCharJson).then(function () {
                displayResults(true, "Loaded character " + sCharID + ".");
            }).catch(onError);
        });

        $(document).on("click", "#loadCharacterFromFile_submit", function(event) {
            var sCharID = $("#loadCharacterFromFile_charID").val() || "";
            var sFile = $("#loadCharacterFromFile_filename").val() || "";
            if (sCharID.length == 0 || sFile.length == 0) {
                onError("Error: Invalid character ID or filename.");
                return;
            }
            loadCharacterFromFile(sCharID, sFile).then(function () {
                displayResults(true, "Loaded character " + sCharID + ".");
            }).catch(onError);
        });

        $(document).on("click", "#saveCharacterToFile_submit", function(event) {
            var sCharID = $("#saveCharacterToFile_charID").val() || "";
            var sFile = $("#saveCharacterToFile_filename").val() || "";
            if (sCharID.length == 0 || sFile.length == 0) {
                onError("Error: Invalid character ID or filename.");
                return;
            }
            saveCharacterToFile(sCharID, sFile).then(function () {
                displayResults(true, "Saved character " + sCharID + ".");
            }).catch(onError);
        });

        $(document).on("click", "#unloadCharacter_submit", function(event) {
            var sCharID = $("#unloadCharacter_charID").val() || 0;
            if (sSlot.length == 0) {
                onError("Error: Invalid character ID.");
                return;
            }
            unloadCharacter(sCharID).then(function () {
                displayResults(true, "Unloaded character " + sCharID + ".");
            }).catch(onError);
        });

        $(document).on("click", "#generateCharacter_submit", function(event) {
            var sCharID = $("#generateCharacter_charID").val() || 0;
            var sGeneratorJson = $("#generateCharacter_textarea").val() || 0;
            if (sCharID.length == 0 || sGeneratorJson.length == 0) {
                onError("Error: Invalid character ID or character generator json.");
                return;
            }
            generateCharacter(sCharID, sGeneratorJson).then(function () {
                displayResults(true, "Generated character " + sCharID + ".");
            }).catch(onError);
        });

        $(document).on("click", "#editCharacter_submit", function(event) {
            var sCharID = $("#editCharacter_charID").val() || 0;
            if (sCharID.length == 0) {
                onError("Error: Invalid character ID.");
                return;
            }
            doesCharacterExist(sCharID).then(function (result) {
                if(result)
                {
                    return Promise.resolve();
                }
                else
                {
                    return Promise.reject("Character does not exist");
                }
            }).then(function() {
                return getCharacter(sCharID);
            }).then(function (charObj) {
                $("#createCharacter_fname").val(charObj.FirstName);
                $("#createCharacter_lname").val(charObj.LastName);
                $("#createCharacter_currentweaponset").val(charObj.CurrentWeaponSet);
                $("#createCharacter_transformedrace").val(charObj.TransformedRace);
                $("#createCharacter_baserace").val(charObj.BaseRace);
                $("#createCharacter_eyes").val(charObj.Eyes);
                $("#createCharacter_gender").val(charObj.Gender);
                $("#createCharacter_hair").val(charObj.Hair);
                $("#createCharacter_handed").val(charObj.Handedness);
                $("#createCharacter_powerset").val(charObj.PowerSet);
                $("#createCharacter_age").val(charObj.Age);
                $("#createCharacter_alchemist_cur").val(charObj.AlchemistCurrent);
                $("#createCharacter_alchemist_rank").val(charObj.AlchemistRank);
                $("#createCharacter_ambidext_cur").val(charObj.AmbidextrousCurrent);
                $("#createCharacter_ambidext_rank").val(charObj.AmbidextrousRank);
                $("#createCharacter_avatar_cur").val(charObj.AvatarCurrent);
                $("#createCharacter_avatar_rank").val(charObj.AvatarRank);
                $("#createCharacter_barbarian_cur").val(charObj.BarbarianCurrent);
                $("#createCharacter_barbarian_rank").val(charObj.BarbarianRank);
                $("#createCharacter_bash_cur").val(charObj.BashCurrent);
                $("#createCharacter_bash_rank").val(charObj.BashRank);
                $("#createCharacter_blademaster_cur").val(charObj.BlademasterCurrent);
                $("#createCharacter_blademaster_rank").val(charObj.BlademasterRank);
                $("#createCharacter_block_cur").val(charObj.BlockCurrent);
                $("#createCharacter_block_rank").val(charObj.BlockRank);
                $("#createCharacter_blood_cur").val(charObj.BloodCurrent);
                $("#createCharacter_blood_rank").val(charObj.BloodRank);
                $("#createCharacter_bowbane_cur").val(charObj.BowbaneCurrent);
                $("#createCharacter_bowbane_rank").val(charObj.BowbaneRank);
                $("#createCharacter_bowsmith_cur").val(charObj.BowsmithCurrent);
                $("#createCharacter_bowsmith_rank").val(charObj.BowsmithRank);
                $("#createCharacter_break_cur").val(charObj.BreakCurrent);
                $("#createCharacter_break_rank").val(charObj.BreakRank);
                $("#createCharacter_chemist_cur").val(charObj.ChemistCurrent);
                $("#createCharacter_chemist_rank").val(charObj.ChemistRank);
                $("#createCharacter_cleave_cur").val(charObj.CleaveCurrent);
                $("#createCharacter_cleave_rank").val(charObj.CleaveRank);
                $("#createCharacter_counter_cur").val(charObj.CounterCurrent);
                $("#createCharacter_counter_rank").val(charObj.CounterRank);
                $("#createCharacter_crack_cur").val(charObj.CrackCurrent);
                $("#createCharacter_crack_rank").val(charObj.CrackRank);
                $("#createCharacter_cshot_cur").val(charObj.CriticalShotCurrent);
                $("#createCharacter_cshot_rank").val(charObj.CriticalShotRank);
                $("#createCharacter_crush_cur").val(charObj.CrushCurrent);
                $("#createCharacter_crush_rank").val(charObj.CrushRank);
                $("#createCharacter_dark_cur").val(charObj.DarkCurrent);
                $("#createCharacter_dark_rank").val(charObj.DarkRank);
                $("#createCharacter_decapitate_cur").val(charObj.DecapitateCurrent);
                $("#createCharacter_decapitate_rank").val(charObj.DecapitateRank);
                $("#createCharacter_dodge_cur").val(charObj.DodgeCurrent);
                $("#createCharacter_dodge_rank").val(charObj.DodgeRank);
                $("#createCharacter_drill_cur").val(charObj.DrillCurrent);
                $("#createCharacter_drill_rank").val(charObj.DrillRank);
                $("#createCharacter_earth_cur").val(charObj.EarthCurrent);
                $("#createCharacter_earth_rank").val(charObj.EarthRank);
                $("#createCharacter_energist_cur").val(charObj.EnergistCurrent);
                $("#createCharacter_energist_rank").val(charObj.EnergistRank);
                $("#createCharacter_fire_cur").val(charObj.FireCurrent);
                $("#createCharacter_fire_rank").val(charObj.FireRank);
                $("#createCharacter_flesh_cur").val(charObj.FleshCurrent);
                $("#createCharacter_flesh_rank").val(charObj.FleshRank);
                $("#createCharacter_focused_cur").val(charObj.FocusedCurrent);
                $("#createCharacter_focused_rank").val(charObj.FocusedRank);
                $("#createCharacter_force_cur").val(charObj.ForceCurrent);
                $("#createCharacter_force_rank").val(charObj.ForceRank);
                $("#createCharacter_goldbane_cur").val(charObj.GoldbaneCurrent);
                $("#createCharacter_goldbane_rank").val(charObj.GoldbaneRank);
                $("#createCharacter_goldsmith_cur").val(charObj.GoldsmithCurrent);
                $("#createCharacter_goldsmith_rank").val(charObj.GoldsmithRank);
                $("#createCharacter_hammerbane_cur").val(charObj.HammerbaneCurrent);
                $("#createCharacter_hammerbane_rank").val(charObj.HammerbaneRank);
                $("#createCharacter_hammersmith_cur").val(charObj.HammersmithCurrent);
                $("#createCharacter_hammersmith_rank").val(charObj.HammersmithRank);
                $("#createCharacter_healer_cur").val(charObj.HealerCurrent);
                $("#createCharacter_healer_rank").val(charObj.HealerRank);
                $("#createCharacter_holy_cur").val(charObj.HolyCurrent);
                $("#createCharacter_holy_rank").val(charObj.HolyRank);
                $("#createCharacter_ice_cur").val(charObj.IceCurrent);
                $("#createCharacter_ice_rank").val(charObj.IceRank);
                $("#createCharacter_impact_cur").val(charObj.ImpactCurrent);
                $("#createCharacter_impact_rank").val(charObj.ImpactRank);
                $("#createCharacter_impale_cur").val(charObj.ImpaleCurrent);
                $("#createCharacter_impale_rank").val(charObj.ImpaleRank);
                $("#createCharacter_light_cur").val(charObj.LightCurrent);
                $("#createCharacter_light_rank").val(charObj.LightRank);
                $("#createCharacter_mage_cur").val(charObj.MageCurrent);
                $("#createCharacter_mage_rank").val(charObj.MageRank);
                $("#createCharacter_mind_cur").val(charObj.MindCurrent);
                $("#createCharacter_mind_rank").val(charObj.MindRank);
                $("#createCharacter_parry_cur").val(charObj.ParryCurrent);
                $("#createCharacter_parry_rank").val(charObj.ParryRank);
                $("#createCharacter_pierce_cur").val(charObj.PierceCurrent);
                $("#createCharacter_pierce_cur").val(charObj.PierceRank);
                $("#createCharacter_platebane_cur").val(charObj.PlatebaneCurrent);
                $("#createCharacter_platebane_rank").val(charObj.PlatebaneRank);
                $("#createCharacter_platesmith_cur").val(charObj.PlatesmithCurrent);
                $("#createCharacter_platesmith_rank").val(charObj.PlatesmithRank);
                $("#createCharacter_riposte_cur").val(charObj.RiposteCurrent);
                $("#createCharacter_riposte_rank").val(charObj.RiposteRank);
                $("#createCharacter_rogue_cur").val(charObj.RogueCurrent);
                $("#createCharacter_rogue_rank").val(charObj.RogueRank);
                $("#createCharacter_rush_cur").val(charObj.RushCurrent);
                $("#createCharacter_rush_rank").val(charObj.RushRank);
                $("#createCharacter_scalebane_cur").val(charObj.ScalebaneCurrent);
                $("#createCharacter_scalebane_rank").val(charObj.ScalebaneRank);
                $("#createCharacter_scalesmith_cur").val(charObj.ScalesmithCurrent);
                $("#createCharacter_scalesmith_rank").val(charObj.ScalesmithRank);
                $("#createCharacter_sever_cur").val(charObj.SeverCurrent);
                $("#createCharacter_sever_rank").val(charObj.SeverRank);
                $("#createCharacter_shieldbane_cur").val(charObj.ShieldbaneCurrent);
                $("#createCharacter_shieldbane_rank").val(charObj.ShieldbaneRank);
                $("#createCharacter_shieldsmith_cur").val(charObj.ShieldsmithCurrent);
                $("#createCharacter_shieldsmith_rank").val(charObj.ShieldsmithRank);
                $("#createCharacter_shock_cur").val(charObj.ShockCurrent);
                $("#createCharacter_shock_rank").val(charObj.ShockRank);
                $("#createCharacter_shoot_cur").val(charObj.ShootCurrent);
                $("#createCharacter_shoot_rank").val(charObj.ShootRank);
                $("#createCharacter_slash_cur").val(charObj.SlashCurrent);
                $("#createCharacter_slash_rank").val(charObj.SlashRank);
                $("#createCharacter_slice_cur").val(charObj.SliceCurrent);
                $("#createCharacter_slice_rank").val(charObj.SliceRank);
                $("#createCharacter_slit_cur").val(charObj.SlitCurrent);
                $("#createCharacter_slit_rank").val(charObj.SlitRank);
                $("#createCharacter_smash_cur").val(charObj.SmashCurrent);
                $("#createCharacter_smash_rank").val(charObj.SmashRank);
                $("#createCharacter_spellbane_cur").val(charObj.SpellbaneCurrent);
                $("#createCharacter_spellbane_rank").val(charObj.SpellbaneRank);
                $("#createCharacter_spellsmith_cur").val(charObj.SpellsmithCurrent);
                $("#createCharacter_spellsmith_rank").val(charObj.SpellsmithRank);
                $("#createCharacter_stalwart_cur").val(charObj.StalwartCurrent);
                $("#createCharacter_stalwart_rank").val(charObj.StalwartRank);
                $("#createCharacter_sstrike_cur").val(charObj.StealthStrikeCurrent);
                $("#createCharacter_sstrike_rank").val(charObj.StealthStrikeRank);
                $("#createCharacter_studremover_cur").val(charObj.StudRemoverCurrent);
                $("#createCharacter_studremover_rank").val(charObj.StudRemoverRank);
                $("#createCharacter_swordbane_cur").val(charObj.SwordbaneCurrent);
                $("#createCharacter_swordbane_rank").val(charObj.SwordbaneRank);
                $("#createCharacter_swordsmith_cur").val(charObj.SwordsmithCurrent);
                $("#createCharacter_swordsmith_rank").val(charObj.SwordsmithRank);
                $("#createCharacter_tanner_cur").val(charObj.TannerCurrent);
                $("#createCharacter_tanner_rank").val(charObj.TannerRank);
                $("#createCharacter_threadbare_cur").val(charObj.ThreadbareCurrent);
                $("#createCharacter_threadbare_rank").val(charObj.ThreadbareRank);
                $("#createCharacter_weaver_cur").val(charObj.WeaverCurrent);
                $("#createCharacter_weaver_rank").val(charObj.WeaverRank);
                $("#createCharacter_wind_cur").val(charObj.WindCurrent);
                $("#createCharacter_wind_rank").val(charObj.WindRank);
                $("#createCharacter_bash_ap").val(charObj.ProgressDataBase.BashPoints);
                $("#createCharacter_block_ap").val(charObj.ProgressDataBase.BlockPoints);
                $("#createCharacter_batk").val(charObj.ProgressDataBase.BluntAttack);
                $("#createCharacter_bdef").val(charObj.ProgressDataBase.BluntDefense);
                $("#createCharacter_break_ap").val(charObj.ProgressDataBase.BreakPoints);
                $("#createCharacter_cleave_ap").val(charObj.ProgressDataBase.CleavePoints);
                $("#createCharacter_counter_ap").val(charObj.ProgressDataBase.CounterPoints);
                $("#createCharacter_crack_ap").val(charObj.ProgressDataBase.CrackPoints);
                $("#createCharacter_cshot_ap").val(charObj.ProgressDataBase.CriticalShotPoints);
                $("#createCharacter_crush_ap").val(charObj.ProgressDataBase.CrushPoints);
                $("#createCharacter_decapitate_ap").val(charObj.ProgressDataBase.DecapitatePoints);
                $("#createCharacter_dodge_ap").val(charObj.ProgressDataBase.DodgePoints);
                $("#createCharacter_drill_ap").val(charObj.ProgressDataBase.DrillPoints);
                $("#createCharacter_eatk").val(charObj.ProgressDataBase.EnergyAttack);
                $("#createCharacter_epdelta").val(charObj.ProgressDataBase.EnergyCostDelta);
                $("#createCharacter_edef").val(charObj.ProgressDataBase.EnergyDefense);
                $("#createCharacter_epcur").val(charObj.ProgressDataBase.EnergyPointsCurrent);
                $("#createCharacter_epmax").val(charObj.ProgressDataBase.EnergyPointsMax);
                $("#createCharacter_epregen").val(charObj.ProgressDataBase.EnergyRegen);
                $("#createCharacter_hpdelta").val(charObj.ProgressDataBase.HealthCostDelta);
                $("#createCharacter_hpcur").val(charObj.ProgressDataBase.HealthPointsCurrent);
                $("#createCharacter_hpmax").val(charObj.ProgressDataBase.HealthPointsMax);
                $("#createCharacter_hpregen").val(charObj.ProgressDataBase.HealthRegen);
                $("#createCharacter_impact_ap").val(charObj.ProgressDataBase.ImpactPoints);
                $("#createCharacter_impale_ap").val(charObj.ProgressDataBase.ImpalePoints);
                $("#createCharacter_matk").val(charObj.ProgressDataBase.MagicAttack);
                $("#createCharacter_mpdelta").val(charObj.ProgressDataBase.MagicCostDelta);
                $("#createCharacter_mdef").val(charObj.ProgressDataBase.MagicDefense);
                $("#createCharacter_mpcur").val(charObj.ProgressDataBase.MagicPointsCurrent);
                $("#createCharacter_mpmax").val(charObj.ProgressDataBase.MagicPointsMax);
                $("#createCharacter_mpregen").val(charObj.ProgressDataBase.MagicRegen);
                $("#createCharacter_parry_ap").val(charObj.ProgressDataBase.ParryPoints);
                $("#createCharacter_patk").val(charObj.ProgressDataBase.PierceAttack);
                $("#createCharacter_pdef").val(charObj.ProgressDataBase.PierceDefense);
                $("#createCharacter_pierce_ap").val(charObj.ProgressDataBase.PiercePoints);
                $("#createCharacter_riposte_ap").val(charObj.ProgressDataBase.RipostePoints);
                $("#createCharacter_rush_ap").val(charObj.ProgressDataBase.RushPoints);
                $("#createCharacter_sever_ap").val(charObj.ProgressDataBase.SeverPoints);
                $("#createCharacter_shoot_ap").val(charObj.ProgressDataBase.ShootPoints);
                $("#createCharacter_satk").val(charObj.ProgressDataBase.SlashAttack);
                $("#createCharacter_sdef").val(charObj.ProgressDataBase.SlashDefense);
                $("#createCharacter_slash_ap").val(charObj.ProgressDataBase.SlashPoints);
                $("#createCharacter_slice_ap").val(charObj.ProgressDataBase.SlicePoints);
                $("#createCharacter_slit_ap").val(charObj.ProgressDataBase.SlitPoints);
                $("#createCharacter_smash_ap").val(charObj.ProgressDataBase.SmashPoints);
                $("#createCharacter_speed").val(charObj.ProgressDataBase.Speed);
                $("#createCharacter_sstrike_ap").val(charObj.ProgressDataBase.StealthStrikePoints);
            });

            // var weapon1left = $("#createCharacter_weapon1left").val() || "";
            // var weapon1right = $("#createCharacter_weapon1right").val() || "";
            // var neck = $("#createCharacter_neck").val() || "";
            // var weapon2left = $("#createCharacter_weapon2left").val() || "";
            // var weapon2right = $("#createCharacter_weapon2right").val() || "";
            // var head = $("#createCharacter_head").val() || "";
            // var leftfingers = $("#createCharacter_leftfingers").val() || "";
            // var rightfingers = $("#createCharacter_rightfingers").val() || "";
            // var hands = $("#createCharacter_hands").val() || "";
            // var feet = $("#createCharacter_feet").val() || "";
            // var legs = $("#createCharacter_legs").val() || "";
            // var chest = $("#createCharacter_chest").val() || "";
        });

        $(document).on("click", "#createCharacter_submit", function(event) {
            var sCharID = $("#createCharacter_charID").val() || "";
            if (sCharID.length == 0) {
                onError("Error: Invalid character ID.");
                return;
            }
            doesCharacterExist(sCharID).then(function (result) {
                if(result)
                {
                    return Promise.resolve();
                }
                else
                {
                    return createCharacter(sCharID);
                }
            }).then(function() {
                return getCharacter(sCharID);
            }).then(function (charObj) {
                charObj.FirstName = $("#createCharacter_fname").val() || "";
                charObj.LastName = $("#createCharacter_lname").val() || "";
                charObj.CurrentWeaponSet = $("#createCharacter_currentweaponset").val() || "None";
                charObj.TransformedRace = $("#createCharacter_transformedrace").val() || "None";
                charObj.BaseRace = $("#createCharacter_baserace").val() || "None";
                charObj.Eyes = $("#createCharacter_eyes").val() || "None";
                charObj.Gender = $("#createCharacter_gender").val() || "None";
                charObj.Hair = $("#createCharacter_hair").val() || "None";
                charObj.Handedness = $("#createCharacter_handed").val() || "None";
                charObj.PowerSet = $("#createCharacter_powerset").val() || "None";
                charObj.Age = parseInt($("#createCharacter_age").val() || 0);
                charObj.AlchemistCurrent = parseInt($("#createCharacter_alchemist_cur").val() || 0);
                charObj.AlchemistRank = parseInt($("#createCharacter_alchemist_rank").val() || 0);
                charObj.AmbidextrousCurrent = parseInt($("#createCharacter_ambidext_cur").val() || 0);
                charObj.AmbidextrousRank = parseInt($("#createCharacter_ambidext_rank").val() || 0);
                charObj.AvatarCurrent = parseInt($("#createCharacter_avatar_cur").val() || 0);
                charObj.AvatarRank = parseInt($("#createCharacter_avatar_rank").val() || 0);
                charObj.BarbarianCurrent = parseInt($("#createCharacter_barbarian_cur").val() || 0);
                charObj.BarbarianRank = parseInt($("#createCharacter_barbarian_rank").val() || 0);
                charObj.BashCurrent = parseInt($("#createCharacter_bash_cur").val() || 0);
                charObj.BashRank = parseInt($("#createCharacter_bash_rank").val() || 0);
                charObj.BlademasterCurrent = parseInt($("#createCharacter_blademaster_cur").val() || 0);
                charObj.BlademasterRank = parseInt($("#createCharacter_blademaster_rank").val() || 0);
                charObj.BlockCurrent = parseInt($("#createCharacter_block_cur").val() || 0);
                charObj.BlockRank = parseInt($("#createCharacter_block_rank").val() || 0);
                charObj.BloodCurrent = parseInt($("#createCharacter_blood_cur").val() || 0);
                charObj.BloodRank = parseInt($("#createCharacter_blood_rank").val() || 0);
                charObj.BowbaneCurrent = parseInt($("#createCharacter_bowbane_cur").val() || 0);
                charObj.BowbaneRank = parseInt($("#createCharacter_bowbane_rank").val() || 0);
                charObj.BowsmithCurrent = parseInt($("#createCharacter_bowsmith_cur").val() || 0);
                charObj.BowsmithRank = parseInt($("#createCharacter_bowsmith_rank").val() || 0);
                charObj.BreakCurrent = parseInt($("#createCharacter_break_cur").val() || 0);
                charObj.BreakRank = parseInt($("#createCharacter_break_rank").val() || 0);
                charObj.ChemistCurrent = parseInt($("#createCharacter_chemist_cur").val() || 0);
                charObj.ChemistRank = parseInt($("#createCharacter_chemist_rank").val() || 0);
                charObj.CleaveCurrent = parseInt($("#createCharacter_cleave_cur").val() || 0);
                charObj.CleaveRank = parseInt($("#createCharacter_cleave_rank").val() || 0);
                charObj.CounterCurrent = parseInt($("#createCharacter_counter_cur").val() || 0);
                charObj.CounterRank = parseInt($("#createCharacter_counter_rank").val() || 0);
                charObj.CrackCurrent = parseInt($("#createCharacter_crack_cur").val() || 0);
                charObj.CrackRank = parseInt($("#createCharacter_crack_rank").val() || 0);
                charObj.CriticalShotCurrent = parseInt($("#createCharacter_cshot_cur").val() || 0);
                charObj.CriticalShotRank = parseInt($("#createCharacter_cshot_rank").val() || 0);
                charObj.CrushCurrent = parseInt($("#createCharacter_crush_cur").val() || 0);
                charObj.CrushRank = parseInt($("#createCharacter_crush_rank").val() || 0);
                charObj.DarkCurrent = parseInt($("#createCharacter_dark_cur").val() || 0);
                charObj.DarkRank = parseInt($("#createCharacter_dark_rank").val() || 0);
                charObj.DecapitateCurrent = parseInt($("#createCharacter_decapitate_cur").val() || 0);
                charObj.DecapitateRank = parseInt($("#createCharacter_decapitate_rank").val() || 0);
                charObj.DodgeCurrent = parseInt($("#createCharacter_dodge_cur").val() || 0);
                charObj.DodgeRank = parseInt($("#createCharacter_dodge_rank").val() || 0);
                charObj.DrillCurrent = parseInt($("#createCharacter_drill_cur").val() || 0);
                charObj.DrillRank = parseInt($("#createCharacter_drill_rank").val() || 0);
                charObj.EarthCurrent = parseInt($("#createCharacter_earth_cur").val() || 0);
                charObj.EarthRank = parseInt($("#createCharacter_earth_rank").val() || 0);
                charObj.EnergistCurrent = parseInt($("#createCharacter_energist_cur").val() || 0);
                charObj.EnergistRank = parseInt($("#createCharacter_energist_rank").val() || 0);
                charObj.FireCurrent = parseInt($("#createCharacter_fire_cur").val() || 0);
                charObj.FireRank = parseInt($("#createCharacter_fire_rank").val() || 0);
                charObj.FleshCurrent = parseInt($("#createCharacter_flesh_cur").val() || 0);
                charObj.FleshRank = parseInt($("#createCharacter_flesh_rank").val() || 0);
                charObj.FocusedCurrent = parseInt($("#createCharacter_focused_cur").val() || 0);
                charObj.FocusedRank = parseInt($("#createCharacter_focused_rank").val() || 0);
                charObj.ForceCurrent = parseInt($("#createCharacter_force_cur").val() || 0);
                charObj.ForceRank = parseInt($("#createCharacter_force_rank").val() || 0);
                charObj.GoldbaneCurrent = parseInt($("#createCharacter_goldbane_cur").val() || 0);
                charObj.GoldbaneRank = parseInt($("#createCharacter_goldbane_rank").val() || 0);
                charObj.GoldsmithCurrent = parseInt($("#createCharacter_goldsmith_cur").val() || 0);
                charObj.GoldsmithRank = parseInt($("#createCharacter_goldsmith_rank").val() || 0);
                charObj.HammerbaneCurrent = parseInt($("#createCharacter_hammerbane_cur").val() || 0);
                charObj.HammerbaneRank = parseInt($("#createCharacter_hammerbane_rank").val() || 0);
                charObj.HammersmithCurrent = parseInt($("#createCharacter_hammersmith_cur").val() || 0);
                charObj.HammersmithRank = parseInt($("#createCharacter_hammersmith_rank").val() || 0);
                charObj.HealerCurrent = parseInt($("#createCharacter_healer_cur").val() || 0);
                charObj.HealerRank = parseInt($("#createCharacter_healer_rank").val() || 0);
                charObj.HolyCurrent = parseInt($("#createCharacter_holy_cur").val() || 0);
                charObj.HolyRank = parseInt($("#createCharacter_holy_rank").val() || 0);
                charObj.IceCurrent = parseInt($("#createCharacter_ice_cur").val() || 0);
                charObj.IceRank = parseInt($("#createCharacter_ice_rank").val() || 0);
                charObj.ImpactCurrent = parseInt($("#createCharacter_impact_cur").val() || 0);
                charObj.ImpactRank = parseInt($("#createCharacter_impact_rank").val() || 0);
                charObj.ImpaleCurrent = parseInt($("#createCharacter_impale_cur").val() || 0);
                charObj.ImpaleRank = parseInt($("#createCharacter_impale_rank").val() || 0);
                charObj.LightCurrent = parseInt($("#createCharacter_light_cur").val() || 0);
                charObj.LightRank = parseInt($("#createCharacter_light_rank").val() || 0);
                charObj.MageCurrent = parseInt($("#createCharacter_mage_cur").val() || 0);
                charObj.MageRank = parseInt($("#createCharacter_mage_rank").val() || 0);
                charObj.MindCurrent = parseInt($("#createCharacter_mind_cur").val() || 0);
                charObj.MindRank = parseInt($("#createCharacter_mind_rank").val() || 0);
                charObj.ParryCurrent = parseInt($("#createCharacter_parry_cur").val() || 0);
                charObj.ParryRank = parseInt($("#createCharacter_parry_rank").val() || 0);
                charObj.PierceCurrent = parseInt($("#createCharacter_pierce_cur").val() || 0);
                charObj.PierceRank = parseInt($("#createCharacter_pierce_cur").val() || 0);
                charObj.PlatebaneCurrent = parseInt($("#createCharacter_platebane_cur").val() || 0);
                charObj.PlatebaneRank = parseInt($("#createCharacter_platebane_rank").val() || 0);
                charObj.PlatesmithCurrent = parseInt($("#createCharacter_platesmith_cur").val() || 0);
                charObj.PlatesmithRank = parseInt($("#createCharacter_platesmith_rank").val() || 0);
                charObj.RiposteCurrent = parseInt($("#createCharacter_riposte_cur").val() || 0);
                charObj.RiposteRank = parseInt($("#createCharacter_riposte_rank").val() || 0);
                charObj.RogueCurrent = parseInt($("#createCharacter_rogue_cur").val() || 0);
                charObj.RogueRank = parseInt($("#createCharacter_rogue_rank").val() || 0);
                charObj.RushCurrent = parseInt($("#createCharacter_rush_cur").val() || 0);
                charObj.RushRank = parseInt($("#createCharacter_rush_rank").val() || 0);
                charObj.ScalebaneCurrent = parseInt($("#createCharacter_scalebane_cur").val() || 0);
                charObj.ScalebaneRank = parseInt($("#createCharacter_scalebane_rank").val() || 0);
                charObj.ScalesmithCurrent = parseInt($("#createCharacter_scalesmith_cur").val() || 0);
                charObj.ScalesmithRank = parseInt($("#createCharacter_scalesmith_rank").val() || 0);
                charObj.SeverCurrent = parseInt($("#createCharacter_sever_cur").val() || 0);
                charObj.SeverRank = parseInt($("#createCharacter_sever_rank").val() || 0);
                charObj.ShieldbaneCurrent = parseInt($("#createCharacter_shieldbane_cur").val() || 0);
                charObj.ShieldbaneRank = parseInt($("#createCharacter_shieldbane_rank").val() || 0);
                charObj.ShieldsmithCurrent = parseInt($("#createCharacter_shieldsmith_cur").val() || 0);
                charObj.ShieldsmithRank = parseInt($("#createCharacter_shieldsmith_rank").val() || 0);
                charObj.ShockCurrent = parseInt($("#createCharacter_shock_cur").val() || 0);
                charObj.ShockRank = parseInt($("#createCharacter_shock_rank").val() || 0);
                charObj.ShootCurrent = parseInt($("#createCharacter_shoot_cur").val() || 0);
                charObj.ShootRank = parseInt($("#createCharacter_shoot_rank").val() || 0);
                charObj.SlashCurrent = parseInt($("#createCharacter_slash_cur").val() || 0);
                charObj.SlashRank = parseInt($("#createCharacter_slash_rank").val() || 0);
                charObj.SliceCurrent = parseInt($("#createCharacter_slice_cur").val() || 0);
                charObj.SliceRank = parseInt($("#createCharacter_slice_rank").val() || 0);
                charObj.SlitCurrent = parseInt($("#createCharacter_slit_cur").val() || 0);
                charObj.SlitRank = parseInt($("#createCharacter_slit_rank").val() || 0);
                charObj.SmashCurrent = parseInt($("#createCharacter_smash_cur").val() || 0);
                charObj.SmashRank = parseInt($("#createCharacter_smash_rank").val() || 0);
                charObj.SpellbaneCurrent = parseInt($("#createCharacter_spellbane_cur").val() || 0);
                charObj.SpellbaneRank = parseInt($("#createCharacter_spellbane_rank").val() || 0);
                charObj.SpellsmithCurrent = parseInt($("#createCharacter_spellsmith_cur").val() || 0);
                charObj.SpellsmithRank = parseInt($("#createCharacter_spellsmith_rank").val() || 0);
                charObj.StalwartCurrent = parseInt($("#createCharacter_stalwart_cur").val() || 0);
                charObj.StalwartRank = parseInt($("#createCharacter_stalwart_rank").val() || 0);
                charObj.StealthStrikeCurrent = parseInt($("#createCharacter_sstrike_cur").val() || 0);
                charObj.StealthStrikeRank = parseInt($("#createCharacter_sstrike_rank").val() || 0);
                charObj.StudRemoverCurrent = parseInt($("#createCharacter_studremover_cur").val() || 0);
                charObj.StudRemoverRank = parseInt($("#createCharacter_studremover_rank").val() || 0);
                charObj.SwordbaneCurrent = parseInt($("#createCharacter_swordbane_cur").val() || 0);
                charObj.SwordbaneRank = parseInt($("#createCharacter_swordbane_rank").val() || 0);
                charObj.SwordsmithCurrent = parseInt($("#createCharacter_swordsmith_cur").val() || 0);
                charObj.SwordsmithRank = parseInt($("#createCharacter_swordsmith_rank").val() || 0);
                charObj.TannerCurrent = parseInt($("#createCharacter_tanner_cur").val() || 0);
                charObj.TannerRank = parseInt($("#createCharacter_tanner_rank").val() || 0);
                charObj.ThreadbareCurrent = parseInt($("#createCharacter_threadbare_cur").val() || 0);
                charObj.ThreadbareRank = parseInt($("#createCharacter_threadbare_rank").val() || 0);
                charObj.WeaverCurrent = parseInt($("#createCharacter_weaver_cur").val() || 0);
                charObj.WeaverRank = parseInt($("#createCharacter_weaver_rank").val() || 0);
                charObj.WindCurrent = parseInt($("#createCharacter_wind_cur").val() || 0);
                charObj.WindRank = parseInt($("#createCharacter_wind_rank").val() || 0);
                charObj.ProgressDataBase.BashPoints = parseInt($("#createCharacter_bash_ap").val() || 0);
                charObj.ProgressDataBase.BlockPoints = parseInt($("#createCharacter_block_ap").val() || 0);
                charObj.ProgressDataBase.BluntAttack = parseInt($("#createCharacter_batk").val() || 0);
                charObj.ProgressDataBase.BluntDefense = parseInt($("#createCharacter_bdef").val() || 0);
                charObj.ProgressDataBase.BreakPoints = parseInt($("#createCharacter_break_ap").val() || 0);
                charObj.ProgressDataBase.CleavePoints = parseInt($("#createCharacter_cleave_ap").val() || 0);
                charObj.ProgressDataBase.CounterPoints = parseInt($("#createCharacter_counter_ap").val() || 0);
                charObj.ProgressDataBase.CrackPoints = parseInt($("#createCharacter_crack_ap").val() || 0);
                charObj.ProgressDataBase.CriticalShotPoints = parseInt($("#createCharacter_cshot_ap").val() || 0);
                charObj.ProgressDataBase.CrushPoints = parseInt($("#createCharacter_crush_ap").val() || 0);
                charObj.ProgressDataBase.DecapitatePoints = parseInt($("#createCharacter_decapitate_ap").val() || 0);
                charObj.ProgressDataBase.DodgePoints = parseInt($("#createCharacter_dodge_ap").val() || 0);
                charObj.ProgressDataBase.DrillPoints = parseInt($("#createCharacter_drill_ap").val() || 0);
                charObj.ProgressDataBase.EnergyAttack = parseInt($("#createCharacter_eatk").val() || 0);
                charObj.ProgressDataBase.EnergyCostDelta = parseInt($("#createCharacter_epdelta").val() || 0);
                charObj.ProgressDataBase.EnergyDefense = parseInt($("#createCharacter_edef").val() || 0);
                charObj.ProgressDataBase.EnergyPointsCurrent = parseInt($("#createCharacter_epcur").val() || 0);
                charObj.ProgressDataBase.EnergyPointsMax = parseInt($("#createCharacter_epmax").val() || 0);
                charObj.ProgressDataBase.EnergyRegen = parseInt($("#createCharacter_epregen").val() || 0);
                charObj.ProgressDataBase.HealthCostDelta = parseInt($("#createCharacter_hpdelta").val() || 0);
                charObj.ProgressDataBase.HealthPointsCurrent = parseInt($("#createCharacter_hpcur").val() || 0);
                charObj.ProgressDataBase.HealthPointsMax = parseInt($("#createCharacter_hpmax").val() || 0);
                charObj.ProgressDataBase.HealthRegen = parseInt($("#createCharacter_hpregen").val() || 0);
                charObj.ProgressDataBase.ImpactPoints = parseInt($("#createCharacter_impact_ap").val() || 0);
                charObj.ProgressDataBase.ImpalePoints = parseInt($("#createCharacter_impale_ap").val() || 0);
                charObj.ProgressDataBase.MagicAttack = parseInt($("#createCharacter_matk").val() || 0);
                charObj.ProgressDataBase.MagicCostDelta = parseInt($("#createCharacter_mpdelta").val() || 0);
                charObj.ProgressDataBase.MagicDefense = parseInt($("#createCharacter_mdef").val() || 0);
                charObj.ProgressDataBase.MagicPointsCurrent = parseInt($("#createCharacter_mpcur").val() || 0);
                charObj.ProgressDataBase.MagicPointsMax = parseInt($("#createCharacter_mpmax").val() || 0);
                charObj.ProgressDataBase.MagicRegen = parseInt($("#createCharacter_mpregen").val() || 0);
                charObj.ProgressDataBase.ParryPoints = parseInt($("#createCharacter_parry_ap").val() || 0);
                charObj.ProgressDataBase.PierceAttack = parseInt($("#createCharacter_patk").val() || 0);
                charObj.ProgressDataBase.PierceDefense = parseInt($("#createCharacter_pdef").val() || 0);
                charObj.ProgressDataBase.PiercePoints = parseInt($("#createCharacter_pierce_ap").val() || 0);
                charObj.ProgressDataBase.RipostePoints = parseInt($("#createCharacter_riposte_ap").val() || 0);
                charObj.ProgressDataBase.RushPoints = parseInt($("#createCharacter_rush_ap").val() || 0);
                charObj.ProgressDataBase.SeverPoints = parseInt($("#createCharacter_sever_ap").val() || 0);
                charObj.ProgressDataBase.ShootPoints = parseInt($("#createCharacter_shoot_ap").val() || 0);
                charObj.ProgressDataBase.SlashAttack = parseInt($("#createCharacter_satk").val() || 0);
                charObj.ProgressDataBase.SlashDefense = parseInt($("#createCharacter_sdef").val() || 0);
                charObj.ProgressDataBase.SlashPoints = parseInt($("#createCharacter_slash_ap").val() || 0);
                charObj.ProgressDataBase.SlicePoints = parseInt($("#createCharacter_slice_ap").val() || 0);
                charObj.ProgressDataBase.SlitPoints = parseInt($("#createCharacter_slit_ap").val() || 0);
                charObj.ProgressDataBase.SmashPoints = parseInt($("#createCharacter_smash_ap").val() || 0);
                charObj.ProgressDataBase.Speed = parseInt($("#createCharacter_speed").val() || 0);
                charObj.ProgressDataBase.StealthStrikePoints = parseInt($("#createCharacter_sstrike_ap").val() || 0);
                var sCharJson = JSON.stringify(charObj);
                return loadCharacterFromJson(sCharID, sCharJson);
            }).then(function () {
                displayResults(true, "Saved character " + sCharID + ".");
            }).catch(onError);
        });
    };

    // Local data
    var allTypeNames = [];

    // Select tags
    var createCharacterSelectTags = [
        {"tag": "#createCharacter_gender", "initial": "Gender Type...", "type": "CharacterGenderType"},
        {"tag": "#createCharacter_hair", "initial": "Hair Type...", "type": "CharacterHairType"},
        {"tag": "#createCharacter_eyes", "initial": "Eyes Type...", "type": "CharacterEyeType"},
        {"tag": "#createCharacter_handed", "initial": "Handed Type...", "type": "CharacterHandednessType"},
        {"tag": "#createCharacter_powerset", "initial": "Power Set Type...", "type": "CharacterPowerSetType"},
        {"tag": "#createCharacter_baserace", "initial": "Base Race Type...", "type": "CharacterBaseRaceType"},
        {"tag": "#createCharacter_transformedrace", "initial": "Transformed Race Type...", "type": "CharacterTransformedRaceType"},
        {"tag": "#createCharacter_currentweaponset", "initial": "Weapon Set Type...", "type": "CharacterWeaponSetType"}
    ];

    // ------ Public API ------ //
    var pub = {};

    // Init
    pub.init = function (serverObj) {
        currentServerObject = serverObj;
        loadCharacterManager().then(function () {
            return getAllTypeNames();
        }).then(function (results) {
            allTypeNames = results;
            typeNamesUpdated();
            registerButtonHandlers();
        });
    };

    // Return our public api
    return pub;
}();

//# sourceURL=character_manager.js
