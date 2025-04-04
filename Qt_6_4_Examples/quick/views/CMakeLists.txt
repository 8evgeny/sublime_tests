cmake_minimum_required(VERSION 3.16)
project(views LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quick/views")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

add_subdirectory("../shared" "shared")

qt_add_executable(viewsexample
    main.cpp
)

set_target_properties(viewsexample PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(viewsexample PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

add_dependencies(viewsexample views_shared)

qt_add_qml_module(viewsexample
    URI views
    VERSION 1.0
    QML_FILES
        "delegatemodel/dragselection.qml"
        "delegatemodel/slideshow.qml"
        "gridview/gridview-example.qml"
        "listview/content/PetsModel.qml"
        "listview/content/PressAndHoldButton.qml"
        "listview/content/RecipesModel.qml"
        "listview/content/SmallText.qml"
        "listview/content/TextButton.qml"
        "listview/content/ToggleButton.qml"
        "listview/displaymargin.qml"
        "listview/dynamiclist.qml"
        "listview/expandingdelegates.qml"
        "listview/highlight.qml"
        "listview/highlightranges.qml"
        "listview/sections.qml"
        "objectmodel/objectmodel.qml"
        "package/Delegate.qml"
        "package/view.qml"
        "pathview/pathview-example.qml"
        "views.qml"
    RESOURCES
        "gridview/pics/AddressBook_48.png"
        "gridview/pics/AudioPlayer_48.png"
        "gridview/pics/Camera_48.png"
        "gridview/pics/DateBook_48.png"
        "gridview/pics/EMail_48.png"
        "gridview/pics/TodoList_48.png"
        "gridview/pics/VideoPlayer_48.png"
        "listview/content/pics/arrow-down.png"
        "listview/content/pics/arrow-up.png"
        "listview/content/pics/fruit-salad.jpg"
        "listview/content/pics/hamburger.jpg"
        "listview/content/pics/lemonade.jpg"
        "listview/content/pics/list-delete.png"
        "listview/content/pics/minus-sign.png"
        "listview/content/pics/moreDown.png"
        "listview/content/pics/moreUp.png"
        "listview/content/pics/pancakes.jpg"
        "listview/content/pics/plus-sign.png"
        "listview/content/pics/vegetable-soup.jpg"
        "pathview/pics/AddressBook_48.png"
        "pathview/pics/AudioPlayer_48.png"
        "pathview/pics/Camera_48.png"
        "pathview/pics/DateBook_48.png"
        "pathview/pics/EMail_48.png"
        "pathview/pics/TodoList_48.png"
        "pathview/pics/VideoPlayer_48.png"
)

install(TARGETS viewsexample
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

bundle_shared(viewsexample)
