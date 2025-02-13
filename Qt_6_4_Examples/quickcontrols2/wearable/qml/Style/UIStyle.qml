// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

pragma Singleton

QtObject {
    id: uiStyle

    // Font Sizes
    readonly property int fontSizeXXS: 10
    readonly property int fontSizeXS: 15
    readonly property int fontSizeS: 20
    readonly property int fontSizeM: 25
    readonly property int fontSizeL: 30
    readonly property int fontSizeXL: 35
    readonly property int fontSizeXXL: 40

    // Color Scheme
    // Green
    readonly property color colorQtPrimGreen: "#41cd52"
    readonly property color colorQtAuxGreen1: "#21be2b"
    readonly property color colorQtAuxGreen2: "#17a81a"

    // Red
    readonly property color colorRed: "#e6173d"

    // Gray
    readonly property color colorQtGray1: "#09102b"
    readonly property color colorQtGray2: "#222840"
    readonly property color colorQtGray3: "#3a4055"
    readonly property color colorQtGray4: "#53586b"
    readonly property color colorQtGray5: "#53586b"
    readonly property color colorQtGray6: "#848895"
    readonly property color colorQtGray7: "#9d9faa"
    readonly property color colorQtGray8: "#b5b7bf"
    readonly property color colorQtGray9: "#cecfd5"
    readonly property color colorQtGray10: "#f3f3f4"

    // Light/dark versions of the colors above.
    // Some UI elements always use a specific color regardless of theme,
    // which is why we have both sets: so that those elements don't need to hard-code the hex string.
    readonly property color themeColorQtGray1: darkTheme ? colorQtGray10 : colorQtGray1
    readonly property color themeColorQtGray2: darkTheme ? colorQtGray9 : colorQtGray2
    readonly property color themeColorQtGray3: darkTheme ? colorQtGray8 : colorQtGray3
    readonly property color themeColorQtGray4: darkTheme ? colorQtGray7 : colorQtGray4
    readonly property color themeColorQtGray5: darkTheme ? colorQtGray6 : colorQtGray5
    readonly property color themeColorQtGray6: darkTheme ? colorQtGray5 : colorQtGray6
    readonly property color themeColorQtGray7: darkTheme ? colorQtGray4 : colorQtGray7
    readonly property color themeColorQtGray8: darkTheme ? colorQtGray3 : colorQtGray8
    readonly property color themeColorQtGray9: darkTheme ? colorQtGray2 : colorQtGray9
    readonly property color themeColorQtGray10: darkTheme ? colorQtGray1 : colorQtGray10

    property bool darkTheme: false

    function themeImagePath(baseImagePath) {
        return baseImagePath + (darkTheme ? "-dark" : "-light") + ".png"
    }
}
