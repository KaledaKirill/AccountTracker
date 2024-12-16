QT       += core gui widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DAO/accountsdaosqlite.cpp \
    Parser/logparser.cpp \
    Utils/database.cpp \
    Utils/logger.cpp \
    Entities/account.cpp \
    Views/Dialogs/addaccountdialog.cpp \
    Views/Dialogs/loginputdialog.cpp \
    main.cpp \
    Views/Forms/mainwindow.cpp

HEADERS += \
    DAO/accountsdaosqlite.h \
    Parser/logparser.h \
    Utils/database.h \
    Utils/logger.h \
    Views/Dialogs/addaccountdialog.h \
    Views/Forms/mainwindow.h \
    Entities/account.h \
    DAO/iaccountsdao.h \
    Views/Dialogs/loginputdialog.h \
    Parser/ilogparser.h

FORMS += \
    Views/Dialogs/addaccountdialog.ui \
    Views/Forms/mainwindow.ui \
    Views/Dialogs/loginputdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
