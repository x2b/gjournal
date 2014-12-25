INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

INCLUDE_DIRECTORIES(${GTKMM3_INCLUDE_DIRS}
                    ${LIBXML_INCLUDE_DIRS}
                    ${Boost_INCLUDE_DIRS})

ADD_DEFINITIONS(${GTKMM3_CFLAGS}
                ${LIBXML_CFLAGS}
                ${Boost_CFLAGS})

LINK_DIRECTORIES(${GTKMM3_LIBRARY_DIRS}
                 ${LIBXML_LIBRARY_DIRS}
                 ${Boost_LIBRARY_DIRS})

GRESOURCE(${CMAKE_SOURCE_DIR} gjournal.gresource.xml
  "${CMAKE_BINARY_DIR}/src" RESOURCE_FILE)
               
ADD_EXECUTABLE(gjournal
               ${RESOURCE_FILE}
               ./util/Log.cc
               ./util/Error.cc
               ./util/ReadError.cc
               ./gui/PageWidget.cc
               ./gui/PageLayout.cc
               ./gui/DragHandler.cc
               ./gui/ZoomWidget.cc
               ./gui/ZoomHandler.cc
               ./gui/MainMenu.cc
               ./gui/ScrollHandler.cc
               ./gui/Application.cc
               ./gui/MainWindow.cc
               ./gui/DocumentHandler.cc
               ./gui/PrintOperation.cc
               ./gui/JournalWidget.cc
               ./gui/PositionWidget.cc
               ./gui/SurfaceBuffer.cc
               ./model/Background.cc
               ./model/Color.cc
               ./model/Document.cc
               ./model/Element.cc
               ./model/Image.cc
               ./model/Layer.cc
               ./model/Page.cc
               ./model/Pen.cc
               ./model/Point.cc
               ./model/PressurePoint.cc
               ./model/PressureStroke.cc
               ./model/Rectangle.cc
               ./model/Stroke.cc
               ./model/Text.cc
               ./main.cc
               ./io/XojReader.cc)

TARGET_LINK_LIBRARIES(gjournal
                      ${GTKMM3_LIBRARIES}
                      ${LIBXML_LIBRARIES})
