bin_PROGRAMS = gjournal

gjournal_SOURCES = \
	main.cc \
	gui/Application.cc \
	gui/DocumentHandler.cc \
	gui/DragHandler.cc \
	gui/JournalWidget.cc \
	gui/MainWindow.cc \
	gui/PageLayout.cc \
	gui/PageWidget.cc \
	gui/PositionWidget.cc \
	gui/ScrollHandler.cc \
	gui/ZoomWidget.cc \
	gui/ZoomHandler.cc \
	io/XojReader.cc \
	model/Color.cc \
	model/Document.cc \
	model/Element.cc \
	model/Layer.cc \
	model/Page.cc \
	model/Pen.cc \
	model/Point.cc \
	model/PressurePoint.cc \
	model/PressureStroke.cc \
	model/Rectangle.cc \
	model/Stroke.cc \
	model/Text.cc \
	util/Log.cc \
	util/Error.cc \
	util/ReadError.cc

RESOURCE_SRC = gjournal-resources.c

nodist_gjournal_SOURCES = \
	$(RESOURCE_SRC)

BUILT_SOURCES = \
	$(RESOURCE_SRC)

CLEANFILES = \
	$(RESOURCE_SRC)

$(RESOURCE_SRC): $(abs_top_srcdir)/gjournal.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --generate-dependencies --sourcedir=$(abs_top_srcdir) $(abs_top_srcdir)/gjournal.gresource.xml)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(abs_top_srcdir) --generate-source --c-name=gj $<

gjournal_CFLAGS= @PACKAGE_CC_CFLAGS@
gjournal_CXXFLAGS = @PACKAGE_CPP_CFLAGS@
gjournal_LDADD = @PACKAGE_CPP_LIBS@ @PACKAGE_CC_LIBS@
