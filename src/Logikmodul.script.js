function LOG_checkUserFormula(device, online, progress, context) {
    var lFormulaIndex = context.formulaIndex;
    var parFormula = device.getParameterByName("LOG_UserFormula" + lFormulaIndex);
    var lFormula = parFormula.value;

    progress.setText("Logik: Benutzerformel " + lFormulaIndex + " prüfen...");
    if (lFormula.length == 0) {
        throw new Error("Logik: Formel ist leer");
    }
    // first we try to get rid of all '\n' strings
    newline(device, online, progress, { "textbox": "LOG_UserFormula" + lFormulaIndex })
    online.connect();
    var data = [1]; // check user formula command

    // user formula index to check
    data = data.concat(lFormulaIndex);
    // send formula length to avoid APDU problems
    data = data.concat(lFormula.length);
    // we send the client formula, because it might not have been sent to device
    // and we convert everything to lowercase
    for (var i = 0; i < lFormula.length; i++) {
        var code = lFormula.charCodeAt(i);
        // if (code >= 65 && code <= 90) code += 32;
        data = data.concat([code]);
    }
    data = data.concat(0); // ensure zero-terminated string

    var resp = online.invokeFunctionProperty(160, 4, data);
    online.disconnect();
    if (resp[0] == 0)
        progress.setText("Logik: Benutzerformel " + lFormulaIndex + " ist korrekt");
    else if (resp[0] == -1)
        throw new Error("Logik: Fehler bei der Übertragung:\n\nAPDU ist zu kurz, prüfen der Formel nicht möglich");
    else {
        var lErr = resp[0];
        var lErrorFormula = parFormula.value;
        var lStart = lErrorFormula.substr(0, lErr - 1);
        var lLetter = lErrorFormula.charAt(lErr - 1);
        var lEnd = lErrorFormula.slice(lErr);
        throw new Error("Logik: Fehler bei '" + lLetter + "':\n\n" + lStart + " ==>" + lLetter + "<== " + lEnd);
    }
}
