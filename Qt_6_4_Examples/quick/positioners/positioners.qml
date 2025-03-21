// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import shared as Examples

Item {
    height: 480
    width: 320
    Examples.LauncherList {
        id: ll
        anchors.fill: parent
        Component.onCompleted: {
            addExample("Transitions", "Fluidly shows and hides elements",  Qt.resolvedUrl("positioners-transitions.qml"));
            addExample("Attached Properties", "Knows where it is in the positioner", Qt.resolvedUrl("positioners-attachedproperties.qml"));
        }
    }
}
