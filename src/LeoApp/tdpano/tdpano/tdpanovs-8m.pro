######################################################################
# Automatically generated by qmake (3.0) ?? 3? 3 06:13:15 2017
######################################################################

QT += gui widgets opengl serialport opencv

CONFIG += C++11

TEMPLATE = app
TARGET = tdp
INCLUDEPATH +=  .\
                ..


LIBS += -pthread -lopencv_core -lopencv_videoio -lopencv_imgcodecs -lopencv_imgproc -lopencv_features2d -lopencv_calib3d

# Input

DEFINES += USELIBSA

##if(contains(DEFINES , USELIBSA)){
message("USELIBSA")
SourceDir = ./widget \
        ./rendererex

LIBS += \
        $$PWD/libs/renderer/librenderer.a \
        $$PWD/libs/autocalib/libautocalib.a \
        $$PWD/libs/leobase/libleobase.a \
        -lopencv_calib3d

message("$$LIBS")

INCLUDEPATH += ./libs \
                ./libs/leobase \
               ./libs/renderer \
               ./libs/autocalib

##}
##else{
#message("DONT_USELIBSA")
#SourceDir = ./widget \
#        ./rendererex \
#        ../leobase \
#        ../renderer \
#        ../rdrrcam \
#        ../autocalib/autocalib
##}



for(var, SourceDir){
#message("var= $$var")
    SOURCES += $$files($$join(var,,,/*.cpp), false)
    HEADERS += $$files($$join(var,,,/*.h), false)
    HEADERS += $$files($$join(var,,,/*.hpp), false)
}

message("$$SOURCES")

FORMS +=

DISTFILES += tdp

SOURCES +=

