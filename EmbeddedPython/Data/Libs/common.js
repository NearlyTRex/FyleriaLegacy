(function(){window.SwitchToScene=function(s){
    var p = {
        Function:"SwitchToScene",
        Args:[s]
    };
    window.external.invoke(JSON.stringify(p));
};})();

(function(){window.SubmitForm=function(s){
    var p = {
        Function:"SubmitForm",
        Args:[s,$('form').serialize()]
    };
    window.external.invoke(JSON.stringify(p));
};})();

(function(){window.ReloadPage=function(){
    var p = {
        Function:"ReloadPage",
        Args:[]
    };
    window.external.invoke(JSON.stringify(p));
};})();
