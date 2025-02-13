qt_internal_add_example(quick-accessibility)
qt_internal_add_example(animation)
qt_internal_add_example(draganddrop)
qt_internal_add_example(externaldraganddrop)
qt_internal_add_example(canvas)
qt_internal_add_example(imageelements)
qt_internal_add_example(keyinteraction)
qt_internal_add_example(layouts)
qt_internal_add_example(localstorage)
add_subdirectory(models)
qt_internal_add_example(views)
add_subdirectory(tableview)
qt_internal_add_example(mousearea)
qt_internal_add_example(positioners)
qt_internal_add_example(righttoleft)
add_subdirectory(scenegraph)
qt_internal_add_example(shadereffects)
qt_internal_add_example(text)
qt_internal_add_example(threading)
qt_internal_add_example(touchinteraction)
add_subdirectory(tutorials)
add_subdirectory(customitems)
qt_internal_add_example(imageprovider)
qt_internal_add_example(imageresponseprovider)
qt_internal_add_example(window)
add_subdirectory(particles)
qt_internal_add_example(delegatechooser)
qt_internal_add_example(shapes)
if(QT_FEATURE_opengl OR QT_FEATURE_opengles2 OR QT_FEATURE_opengles3)
    add_subdirectory(rendercontrol)
endif()
if(TARGET Qt::Widgets)
    qt_internal_add_example(embeddedinwidgets)
endif()
if(TARGET Qt::QuickWidgets AND TARGET Qt::Widgets AND (QT_FEATURE_opengl OR QT_FEATURE_opengles2 OR QT_FEATURE_opengles3))
    add_subdirectory(quickwidgets)
endif()

# qt_examples_build_end() misses at least some of these due to some
# source subdirectories being added multiple times. See QTBUG-96159.
set(reused_dir_targets
    animation_shared
    canvas_shared
    views_shared
    positioners_shared
    righttoleft_shared
    text_shared
    threading_shared
    touchinteraction_shared
    window_shared
    shapes_shared
    imageelements_shared
    delegatechooser_shared
    pointerhandlers_shared
    affectors_shared
    emitters_shared
    imageparticle_shared
    itemparticle_shared
    system_shared
    draganddrop_shared
)

foreach(target IN LISTS reused_dir_targets)
    if(TARGET ${target})
        qt_autogen_tools(${target} ENABLE_AUTOGEN_TOOLS moc rcc)
        if(TARGET Qt::Widgets)
            qt_autogen_tools(${target} ENABLE_AUTOGEN_TOOLS uic)
        endif()
    endif()
endforeach()
