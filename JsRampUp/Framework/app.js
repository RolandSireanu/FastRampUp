



$("#clickMe").click(function () {
    var obj = $G();
    
    $("#slct").hide();
    obj.setLanguage($("#slct").val()).validate().HTMLGreeting("#hello",true);
});