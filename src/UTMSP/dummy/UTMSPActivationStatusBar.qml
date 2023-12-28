import QtQuick

Item {
    property string activationStartTimestamp
    property bool   activationApproval
    property string flightID
    property string timeDifference

    signal  activationTriggered(bool value)
}
