import QtQuick
Item {
    // Dummy Properties
    property var    myGeoFenceController
    property var    flightMap
    property var    currentMissionItems
    property bool   triggerSubmitButton
    // Dummy Signals
     signal responseSent(string response)
     signal vehicleIDSent(int id)
     signal resetTriggered()
     signal timeStampSent(string timestamp, bool activateflag, string id)
     signal approvalSent(bool approval)
}
