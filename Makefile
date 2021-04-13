#############################################################################
# Makefile for building: dist/MM_gradient
# Generated by qmake (3.1) (Qt 5.12.8)
# Project:  MM_gradient.pro
# Template: app
# Command: /usr/lib/qt5/bin/qmake -o Makefile MM_gradient.pro
#############################################################################

MAKEFILE      = Makefile

EQ            = =

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -pipe -fpermissive -O3 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I. -I-L/usr/lib/ -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++
QMAKE         = /usr/lib/qt5/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
QINSTALL      = /usr/lib/qt5/bin/qmake -install qinstall
QINSTALL_PROGRAM = /usr/lib/qt5/bin/qmake -install qinstall -exe
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = MM_gradient1.0.0
DISTDIR = /mnt/c/things/projects/edge_simplification/MM_gradient/MM_gradient/build/MM_gradient1.0.0
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS) /usr/lib/x86_64-linux-gnu/libQt5Gui.so /usr/lib/x86_64-linux-gnu/libQt5Core.so /usr/lib/x86_64-linux-gnu/libGL.so -lpthread   
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = build/

####### Files

SOURCES       = source/main.cpp \
		source/Lib_Tri/Vertex3D.cpp \
		source/Lib_Tri/Vertex2D.cpp \
		source/Lib_Tri/Triangle.cpp \
		source/Lib_Tri/Timer.cpp \
		source/Lib_Tri/Reader.cpp \
		source/Lib_Tri/formangradientvector.cpp \
		source/Lib_Tri/Edge.cpp \
		source/Lib_Tri/forman_feature.cpp \
		source/Lib_Tri/IO.cpp \
		source/Lib_Tri/forman_refinement.cpp \
		source/Lib_Tri/forman_extraction_query.cpp \
		source/Lib_Tri/forman_simplify_mr.cpp \
		source/Lib_Tri/forman_simplify.cpp \
		source/Lib_Tri/string_management.cpp 
OBJECTS       = build/main.o \
		build/Vertex3D.o \
		build/Vertex2D.o \
		build/Triangle.o \
		build/Timer.o \
		build/Reader.o \
		build/formangradientvector.o \
		build/Edge.o \
		build/forman_feature.o \
		build/IO.o \
		build/forman_refinement.o \
		build/forman_extraction_query.o \
		build/forman_simplify_mr.o \
		build/forman_simplify.o \
		build/string_management.o
DIST          = /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_edid_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_vulkan_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qmake_use.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		MM_gradient.pro source/Lib_Tri/Vertex3D.h \
		source/Lib_Tri/Vertex2D.h \
		source/Lib_Tri/Triangle.h \
		source/Lib_Tri/Timer.h \
		source/Lib_Tri/Sorting.h \
		source/Lib_Tri/Reader.h \
		source/Lib_Tri/Mesh.h \
		source/Lib_Tri/formangradientvector.h \
		source/Lib_Tri/Edge.h \
		source/Lib_Tri/forman_arrow.h \
		source/Ig/ig.h \
		source/Dag/Dag.h \
		source/Lib_Tri/Matrix.h \
		source/Lib_Tri/string_management.h source/main.cpp \
		source/Lib_Tri/Vertex3D.cpp \
		source/Lib_Tri/Vertex2D.cpp \
		source/Lib_Tri/Triangle.cpp \
		source/Lib_Tri/Timer.cpp \
		source/Lib_Tri/Reader.cpp \
		source/Lib_Tri/formangradientvector.cpp \
		source/Lib_Tri/Edge.cpp \
		source/Lib_Tri/forman_feature.cpp \
		source/Lib_Tri/IO.cpp \
		source/Lib_Tri/forman_refinement.cpp \
		source/Lib_Tri/forman_extraction_query.cpp \
		source/Lib_Tri/forman_simplify_mr.cpp \
		source/Lib_Tri/forman_simplify.cpp \
		source/Lib_Tri/string_management.cpp
QMAKE_TARGET  = MM_gradient
DESTDIR       = dist/
TARGET        = dist/MM_gradient


first: all
####### Build rules

dist/MM_gradient:  $(OBJECTS)  
	@test -d dist/ || mkdir -p dist/
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: MM_gradient.pro /usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_edid_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_vulkan_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qmake_use.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		MM_gradient.pro
	$(QMAKE) -o Makefile MM_gradient.pro
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_edid_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_egl_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fb_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_glx_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_input_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_kms_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_service_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_theme_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_vulkan_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf:
.qmake.stash:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qmake_use.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf:
MM_gradient.pro:
qmake: FORCE
	@$(QMAKE) -o Makefile MM_gradient.pro

qmake_all: FORCE


all: Makefile dist/MM_gradient

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp $(DISTDIR)/
	$(COPY_FILE) --parents source/Lib_Tri/Vertex3D.h source/Lib_Tri/Vertex2D.h source/Lib_Tri/Triangle.h source/Lib_Tri/Timer.h source/Lib_Tri/Sorting.h source/Lib_Tri/Reader.h source/Lib_Tri/Mesh.h source/Lib_Tri/formangradientvector.h source/Lib_Tri/Edge.h source/Lib_Tri/forman_arrow.h source/Ig/ig.h source/Dag/Dag.h source/Lib_Tri/Matrix.h source/Lib_Tri/string_management.h $(DISTDIR)/
	$(COPY_FILE) --parents source/main.cpp source/Lib_Tri/Vertex3D.cpp source/Lib_Tri/Vertex2D.cpp source/Lib_Tri/Triangle.cpp source/Lib_Tri/Timer.cpp source/Lib_Tri/Reader.cpp source/Lib_Tri/formangradientvector.cpp source/Lib_Tri/Edge.cpp source/Lib_Tri/forman_feature.cpp source/Lib_Tri/IO.cpp source/Lib_Tri/forman_refinement.cpp source/Lib_Tri/forman_extraction_query.cpp source/Lib_Tri/forman_simplify_mr.cpp source/Lib_Tri/forman_simplify.cpp source/Lib_Tri/string_management.cpp $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) .qmake.stash
	-$(DEL_FILE) Makefile


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_objc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_objc_header_make_all compiler_moc_source_make_all

check: first

benchmark: first

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_predefs_make_all: moc_predefs.h
compiler_moc_predefs_clean:
	-$(DEL_FILE) moc_predefs.h
moc_predefs.h: /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp
	g++ -pipe -fpermissive -O3 -std=gnu++11 -Wall -W -dM -E -o moc_predefs.h /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp

compiler_moc_header_make_all:
compiler_moc_header_clean:
compiler_moc_objc_header_make_all:
compiler_moc_objc_header_clean:
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_predefs_clean 

####### Compile

build/main.o: source/main.cpp source/Lib_Tri/formangradientvector.h \
		source/Lib_Tri/Reader.h \
		source/Lib_Tri/Vertex2D.h \
		source/Lib_Tri/Vertex3D.h \
		source/Lib_Tri/Mesh.h \
		source/Lib_Tri/Matrix.h \
		source/Lib_Tri/Sorting.h \
		source/Lib_Tri/Edge.h \
		source/Dag/Dag.h \
		source/Ig/ig.h \
		source/Lib_Tri/Triangle.h \
		source/Lib_Tri/string_management.h \
		source/Lib_Tri/forman_arrow.h \
		source/Lib_Tri/aux_forman_gradient_vector.h \
		source/Lib_Tri/Timer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/main.o source/main.cpp

build/Vertex3D.o: source/Lib_Tri/Vertex3D.cpp source/Lib_Tri/Vertex3D.h \
		source/Lib_Tri/Vertex2D.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Vertex3D.o source/Lib_Tri/Vertex3D.cpp

build/Vertex2D.o: source/Lib_Tri/Vertex2D.cpp source/Lib_Tri/Vertex2D.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Vertex2D.o source/Lib_Tri/Vertex2D.cpp

build/Triangle.o: source/Lib_Tri/Triangle.cpp source/Lib_Tri/Triangle.h \
		source/Lib_Tri/Edge.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Triangle.o source/Lib_Tri/Triangle.cpp

build/Timer.o: source/Lib_Tri/Timer.cpp source/Lib_Tri/Timer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Timer.o source/Lib_Tri/Timer.cpp

build/Reader.o: source/Lib_Tri/Reader.cpp source/Lib_Tri/Reader.h \
		source/Lib_Tri/Vertex2D.h \
		source/Lib_Tri/Vertex3D.h \
		source/Lib_Tri/Mesh.h \
		source/Lib_Tri/Matrix.h \
		source/Lib_Tri/Sorting.h \
		source/Lib_Tri/Edge.h \
		source/Dag/Dag.h \
		source/Ig/ig.h \
		source/Lib_Tri/Triangle.h \
		source/Lib_Tri/string_management.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Reader.o source/Lib_Tri/Reader.cpp

build/formangradientvector.o: source/Lib_Tri/formangradientvector.cpp source/Lib_Tri/formangradientvector.h \
		source/Lib_Tri/Reader.h \
		source/Lib_Tri/Vertex2D.h \
		source/Lib_Tri/Vertex3D.h \
		source/Lib_Tri/Mesh.h \
		source/Lib_Tri/Matrix.h \
		source/Lib_Tri/Sorting.h \
		source/Lib_Tri/Edge.h \
		source/Dag/Dag.h \
		source/Ig/ig.h \
		source/Lib_Tri/Triangle.h \
		source/Lib_Tri/string_management.h \
		source/Lib_Tri/forman_arrow.h \
		source/Lib_Tri/aux_forman_gradient_vector.h \
		source/Lib_Tri/Timer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/formangradientvector.o source/Lib_Tri/formangradientvector.cpp

build/Edge.o: source/Lib_Tri/Edge.cpp source/Lib_Tri/Edge.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Edge.o source/Lib_Tri/Edge.cpp

build/forman_feature.o: source/Lib_Tri/forman_feature.cpp source/Lib_Tri/formangradientvector.h \
		source/Lib_Tri/Reader.h \
		source/Lib_Tri/Vertex2D.h \
		source/Lib_Tri/Vertex3D.h \
		source/Lib_Tri/Mesh.h \
		source/Lib_Tri/Matrix.h \
		source/Lib_Tri/Sorting.h \
		source/Lib_Tri/Edge.h \
		source/Dag/Dag.h \
		source/Ig/ig.h \
		source/Lib_Tri/Triangle.h \
		source/Lib_Tri/string_management.h \
		source/Lib_Tri/forman_arrow.h \
		source/Lib_Tri/aux_forman_gradient_vector.h \
		source/Lib_Tri/Timer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/forman_feature.o source/Lib_Tri/forman_feature.cpp

build/IO.o: source/Lib_Tri/IO.cpp source/Lib_Tri/formangradientvector.h \
		source/Lib_Tri/Reader.h \
		source/Lib_Tri/Vertex2D.h \
		source/Lib_Tri/Vertex3D.h \
		source/Lib_Tri/Mesh.h \
		source/Lib_Tri/Matrix.h \
		source/Lib_Tri/Sorting.h \
		source/Lib_Tri/Edge.h \
		source/Dag/Dag.h \
		source/Ig/ig.h \
		source/Lib_Tri/Triangle.h \
		source/Lib_Tri/string_management.h \
		source/Lib_Tri/forman_arrow.h \
		source/Lib_Tri/aux_forman_gradient_vector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/IO.o source/Lib_Tri/IO.cpp

build/forman_refinement.o: source/Lib_Tri/forman_refinement.cpp source/Lib_Tri/formangradientvector.h \
		source/Lib_Tri/Reader.h \
		source/Lib_Tri/Vertex2D.h \
		source/Lib_Tri/Vertex3D.h \
		source/Lib_Tri/Mesh.h \
		source/Lib_Tri/Matrix.h \
		source/Lib_Tri/Sorting.h \
		source/Lib_Tri/Edge.h \
		source/Dag/Dag.h \
		source/Ig/ig.h \
		source/Lib_Tri/Triangle.h \
		source/Lib_Tri/string_management.h \
		source/Lib_Tri/forman_arrow.h \
		source/Lib_Tri/aux_forman_gradient_vector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/forman_refinement.o source/Lib_Tri/forman_refinement.cpp

build/forman_extraction_query.o: source/Lib_Tri/forman_extraction_query.cpp source/Lib_Tri/formangradientvector.h \
		source/Lib_Tri/Reader.h \
		source/Lib_Tri/Vertex2D.h \
		source/Lib_Tri/Vertex3D.h \
		source/Lib_Tri/Mesh.h \
		source/Lib_Tri/Matrix.h \
		source/Lib_Tri/Sorting.h \
		source/Lib_Tri/Edge.h \
		source/Dag/Dag.h \
		source/Ig/ig.h \
		source/Lib_Tri/Triangle.h \
		source/Lib_Tri/string_management.h \
		source/Lib_Tri/forman_arrow.h \
		source/Lib_Tri/aux_forman_gradient_vector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/forman_extraction_query.o source/Lib_Tri/forman_extraction_query.cpp

build/forman_simplify_mr.o: source/Lib_Tri/forman_simplify_mr.cpp source/Lib_Tri/formangradientvector.h \
		source/Lib_Tri/Reader.h \
		source/Lib_Tri/Vertex2D.h \
		source/Lib_Tri/Vertex3D.h \
		source/Lib_Tri/Mesh.h \
		source/Lib_Tri/Matrix.h \
		source/Lib_Tri/Sorting.h \
		source/Lib_Tri/Edge.h \
		source/Dag/Dag.h \
		source/Ig/ig.h \
		source/Lib_Tri/Triangle.h \
		source/Lib_Tri/string_management.h \
		source/Lib_Tri/forman_arrow.h \
		source/Lib_Tri/aux_forman_gradient_vector.h \
		source/Lib_Tri/edge_collapse.cpp \
		source/Eigen/Eigen \
		source/Eigen/Dense \
		source/Eigen/Core \
		source/Eigen/src/Core/util/DisableStupidWarnings.h \
		source/Eigen/src/Core/util/Macros.h \
		source/Eigen/src/Core/util/MKL_support.h \
		source/Eigen/src/Core/util/Constants.h \
		source/Eigen/src/Core/util/ForwardDeclarations.h \
		source/Eigen/src/Core/util/Meta.h \
		source/Eigen/src/Core/util/XprHelper.h \
		source/Eigen/src/Core/util/StaticAssert.h \
		source/Eigen/src/Core/util/Memory.h \
		source/Eigen/src/Core/NumTraits.h \
		source/Eigen/src/Core/MathFunctions.h \
		source/Eigen/src/Core/GenericPacketMath.h \
		source/Eigen/src/Core/arch/SSE/PacketMath.h \
		source/Eigen/src/Core/arch/SSE/MathFunctions.h \
		source/Eigen/src/Core/arch/SSE/Complex.h \
		source/Eigen/src/Core/arch/AltiVec/PacketMath.h \
		source/Eigen/src/Core/arch/AltiVec/Complex.h \
		source/Eigen/src/Core/arch/NEON/PacketMath.h \
		source/Eigen/src/Core/arch/NEON/Complex.h \
		source/Eigen/src/Core/arch/Default/Settings.h \
		source/Eigen/src/Core/Functors.h \
		source/Eigen/src/Core/DenseCoeffsBase.h \
		source/Eigen/src/Core/DenseBase.h \
		source/Eigen/src/plugins/BlockMethods.h \
		source/Eigen/src/Core/MatrixBase.h \
		source/Eigen/src/plugins/CommonCwiseUnaryOps.h \
		source/Eigen/src/plugins/CommonCwiseBinaryOps.h \
		source/Eigen/src/plugins/MatrixCwiseUnaryOps.h \
		source/Eigen/src/plugins/MatrixCwiseBinaryOps.h \
		source/Eigen/src/Core/EigenBase.h \
		source/Eigen/src/Core/Assign.h \
		source/Eigen/src/Core/util/BlasUtil.h \
		source/Eigen/src/Core/DenseStorage.h \
		source/Eigen/src/Core/NestByValue.h \
		source/Eigen/src/Core/ForceAlignedAccess.h \
		source/Eigen/src/Core/ReturnByValue.h \
		source/Eigen/src/Core/NoAlias.h \
		source/Eigen/src/Core/PlainObjectBase.h \
		source/Eigen/src/Core/Matrix.h \
		source/Eigen/src/Core/Array.h \
		source/Eigen/src/Core/CwiseBinaryOp.h \
		source/Eigen/src/Core/CwiseUnaryOp.h \
		source/Eigen/src/Core/CwiseNullaryOp.h \
		source/Eigen/src/Core/CwiseUnaryView.h \
		source/Eigen/src/Core/SelfCwiseBinaryOp.h \
		source/Eigen/src/Core/Dot.h \
		source/Eigen/src/Core/StableNorm.h \
		source/Eigen/src/Core/MapBase.h \
		source/Eigen/src/Core/Stride.h \
		source/Eigen/src/Core/Map.h \
		source/Eigen/src/Core/Block.h \
		source/Eigen/src/Core/VectorBlock.h \
		source/Eigen/src/Core/Transpose.h \
		source/Eigen/src/Core/DiagonalMatrix.h \
		source/Eigen/src/Core/Diagonal.h \
		source/Eigen/src/Core/DiagonalProduct.h \
		source/Eigen/src/Core/PermutationMatrix.h \
		source/Eigen/src/Core/Transpositions.h \
		source/Eigen/src/Core/Redux.h \
		source/Eigen/src/Core/Visitor.h \
		source/Eigen/src/Core/Fuzzy.h \
		source/Eigen/src/Core/IO.h \
		source/Eigen/src/Core/Swap.h \
		source/Eigen/src/Core/CommaInitializer.h \
		source/Eigen/src/Core/Flagged.h \
		source/Eigen/src/Core/ProductBase.h \
		source/Eigen/src/Core/GeneralProduct.h \
		source/Eigen/src/Core/TriangularMatrix.h \
		source/Eigen/src/Core/SelfAdjointView.h \
		source/Eigen/src/Core/products/GeneralBlockPanelKernel.h \
		source/Eigen/src/Core/products/Parallelizer.h \
		source/Eigen/src/Core/products/CoeffBasedProduct.h \
		source/Eigen/src/Core/products/GeneralMatrixVector.h \
		source/Eigen/src/Core/products/GeneralMatrixMatrix.h \
		source/Eigen/src/Core/SolveTriangular.h \
		source/Eigen/src/Core/products/GeneralMatrixMatrixTriangular.h \
		source/Eigen/src/Core/products/SelfadjointMatrixVector.h \
		source/Eigen/src/Core/products/SelfadjointMatrixMatrix.h \
		source/Eigen/src/Core/products/SelfadjointProduct.h \
		source/Eigen/src/Core/products/SelfadjointRank2Update.h \
		source/Eigen/src/Core/products/TriangularMatrixVector.h \
		source/Eigen/src/Core/products/TriangularMatrixMatrix.h \
		source/Eigen/src/Core/products/TriangularSolverMatrix.h \
		source/Eigen/src/Core/products/TriangularSolverVector.h \
		source/Eigen/src/Core/BandMatrix.h \
		source/Eigen/src/Core/BooleanRedux.h \
		source/Eigen/src/Core/Select.h \
		source/Eigen/src/Core/VectorwiseOp.h \
		source/Eigen/src/Core/Random.h \
		source/Eigen/src/Core/Replicate.h \
		source/Eigen/src/Core/Reverse.h \
		source/Eigen/src/Core/ArrayBase.h \
		source/Eigen/src/plugins/ArrayCwiseUnaryOps.h \
		source/Eigen/src/plugins/ArrayCwiseBinaryOps.h \
		source/Eigen/src/Core/ArrayWrapper.h \
		source/Eigen/src/Core/products/GeneralMatrixMatrix_MKL.h \
		source/Eigen/src/Core/products/GeneralMatrixVector_MKL.h \
		source/Eigen/src/Core/products/GeneralMatrixMatrixTriangular_MKL.h \
		source/Eigen/src/Core/products/SelfadjointMatrixMatrix_MKL.h \
		source/Eigen/src/Core/products/SelfadjointMatrixVector_MKL.h \
		source/Eigen/src/Core/products/TriangularMatrixMatrix_MKL.h \
		source/Eigen/src/Core/products/TriangularMatrixVector_MKL.h \
		source/Eigen/src/Core/products/TriangularSolverMatrix_MKL.h \
		source/Eigen/src/Core/Assign_MKL.h \
		source/Eigen/src/Core/GlobalFunctions.h \
		source/Eigen/src/Core/util/ReenableStupidWarnings.h \
		source/Eigen/Eigen2Support \
		source/Eigen/src/Eigen2Support/Macros.h \
		source/Eigen/src/Eigen2Support/Memory.h \
		source/Eigen/src/Eigen2Support/Meta.h \
		source/Eigen/src/Eigen2Support/Lazy.h \
		source/Eigen/src/Eigen2Support/Cwise.h \
		source/Eigen/src/Eigen2Support/CwiseOperators.h \
		source/Eigen/src/Eigen2Support/TriangularSolver.h \
		source/Eigen/src/Eigen2Support/Block.h \
		source/Eigen/src/Eigen2Support/VectorBlock.h \
		source/Eigen/src/Eigen2Support/Minor.h \
		source/Eigen/src/Eigen2Support/MathFunctions.h \
		source/Eigen/LU \
		source/Eigen/src/misc/Solve.h \
		source/Eigen/src/misc/Kernel.h \
		source/Eigen/src/misc/Image.h \
		source/Eigen/src/LU/FullPivLU.h \
		source/Eigen/src/LU/PartialPivLU.h \
		source/Eigen/src/LU/PartialPivLU_MKL.h \
		source/Eigen/src/LU/Determinant.h \
		source/Eigen/src/LU/Inverse.h \
		source/Eigen/src/LU/arch/Inverse_SSE.h \
		source/Eigen/src/Eigen2Support/LU.h \
		source/Eigen/Cholesky \
		source/Eigen/src/Cholesky/LLT.h \
		source/Eigen/src/Cholesky/LDLT.h \
		source/Eigen/src/Cholesky/LLT_MKL.h \
		source/Eigen/QR \
		source/Eigen/Jacobi \
		source/Eigen/src/Jacobi/Jacobi.h \
		source/Eigen/Householder \
		source/Eigen/src/Householder/Householder.h \
		source/Eigen/src/Householder/HouseholderSequence.h \
		source/Eigen/src/Householder/BlockHouseholder.h \
		source/Eigen/src/QR/HouseholderQR.h \
		source/Eigen/src/QR/FullPivHouseholderQR.h \
		source/Eigen/src/QR/ColPivHouseholderQR.h \
		source/Eigen/src/QR/HouseholderQR_MKL.h \
		source/Eigen/src/QR/ColPivHouseholderQR_MKL.h \
		source/Eigen/src/Eigen2Support/QR.h \
		source/Eigen/Eigenvalues \
		source/Eigen/Geometry \
		source/Eigen/SVD \
		source/Eigen/src/SVD/JacobiSVD.h \
		source/Eigen/src/SVD/JacobiSVD_MKL.h \
		source/Eigen/src/SVD/UpperBidiagonalization.h \
		source/Eigen/src/Eigen2Support/SVD.h \
		source/Eigen/src/Geometry/OrthoMethods.h \
		source/Eigen/src/Geometry/EulerAngles.h \
		source/Eigen/src/Geometry/Homogeneous.h \
		source/Eigen/src/Geometry/RotationBase.h \
		source/Eigen/src/Geometry/Rotation2D.h \
		source/Eigen/src/Geometry/Quaternion.h \
		source/Eigen/src/Geometry/AngleAxis.h \
		source/Eigen/src/Geometry/Transform.h \
		source/Eigen/src/Geometry/Translation.h \
		source/Eigen/src/Geometry/Scaling.h \
		source/Eigen/src/Geometry/Hyperplane.h \
		source/Eigen/src/Geometry/ParametrizedLine.h \
		source/Eigen/src/Geometry/AlignedBox.h \
		source/Eigen/src/Geometry/Umeyama.h \
		source/Eigen/src/Geometry/arch/Geometry_SSE.h \
		source/Eigen/src/Eigen2Support/Geometry/All.h \
		source/Eigen/src/Eigen2Support/Geometry/RotationBase.h \
		source/Eigen/src/Eigen2Support/Geometry/Rotation2D.h \
		source/Eigen/src/Eigen2Support/Geometry/Quaternion.h \
		source/Eigen/src/Eigen2Support/Geometry/AngleAxis.h \
		source/Eigen/src/Eigen2Support/Geometry/Transform.h \
		source/Eigen/src/Eigen2Support/Geometry/Translation.h \
		source/Eigen/src/Eigen2Support/Geometry/Scaling.h \
		source/Eigen/src/Eigen2Support/Geometry/AlignedBox.h \
		source/Eigen/src/Eigen2Support/Geometry/Hyperplane.h \
		source/Eigen/src/Eigen2Support/Geometry/ParametrizedLine.h \
		source/Eigen/src/Eigenvalues/Tridiagonalization.h \
		source/Eigen/src/Eigenvalues/RealSchur.h \
		source/Eigen/src/Eigenvalues/HessenbergDecomposition.h \
		source/Eigen/src/Eigenvalues/EigenSolver.h \
		source/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h \
		source/Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h \
		source/Eigen/src/Eigenvalues/ComplexSchur.h \
		source/Eigen/src/Eigenvalues/ComplexEigenSolver.h \
		source/Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h \
		source/Eigen/src/Eigenvalues/RealSchur_MKL.h \
		source/Eigen/src/Eigenvalues/ComplexSchur_MKL.h \
		source/Eigen/src/Eigenvalues/SelfAdjointEigenSolver_MKL.h \
		source/Lib_Tri/Timer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/forman_simplify_mr.o source/Lib_Tri/forman_simplify_mr.cpp

build/forman_simplify.o: source/Lib_Tri/forman_simplify.cpp source/Lib_Tri/formangradientvector.h \
		source/Lib_Tri/Reader.h \
		source/Lib_Tri/Vertex2D.h \
		source/Lib_Tri/Vertex3D.h \
		source/Lib_Tri/Mesh.h \
		source/Lib_Tri/Matrix.h \
		source/Lib_Tri/Sorting.h \
		source/Lib_Tri/Edge.h \
		source/Dag/Dag.h \
		source/Ig/ig.h \
		source/Lib_Tri/Triangle.h \
		source/Lib_Tri/string_management.h \
		source/Lib_Tri/forman_arrow.h \
		source/Lib_Tri/aux_forman_gradient_vector.h \
		source/Lib_Tri/Timer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/forman_simplify.o source/Lib_Tri/forman_simplify.cpp

build/string_management.o: source/Lib_Tri/string_management.cpp source/Lib_Tri/string_management.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/string_management.o source/Lib_Tri/string_management.cpp

####### Install

install:  FORCE

uninstall:  FORCE

FORCE:

