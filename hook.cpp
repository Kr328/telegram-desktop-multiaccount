#include <dlfcn.h>
#include <cstdlib>
#include <QString>

#define APP_NAME "telegramdesktopfork"
#define DESKTOP_FILE_NAME (APP_NAME ".desktop")

typedef void (*FunctionSetDesktopFileName)(const QString &file);
typedef void (*FunctionSetApplicationName)(const QString &name);

FunctionSetApplicationName originalSetApplicationName;
FunctionSetDesktopFileName originalSetDesktopFileName;

class QGuiApplication
{
public:
    static void setDesktopFileName(const QString &file);
};

class QCoreApplication
{
public:
    static void setApplicationName(const QString &name);
};

void QGuiApplication::setDesktopFileName(const QString &file)
{
    if (!originalSetDesktopFileName)
    {
        originalSetDesktopFileName = reinterpret_cast<FunctionSetDesktopFileName>(dlsym(RTLD_NEXT, "_ZN15QGuiApplication18setDesktopFileNameERK7QString"));
        if ( originalSetDesktopFileName == nullptr ) {
            abort();
        }
    }

    originalSetDesktopFileName(DESKTOP_FILE_NAME);
}

void QCoreApplication::setApplicationName(const QString &name)
{
    if (!originalSetApplicationName)
    {
        originalSetApplicationName = reinterpret_cast<FunctionSetApplicationName>(dlsym(RTLD_NEXT, "_ZN16QCoreApplication18setApplicationNameERK7QString"));
        if ( originalSetApplicationName == nullptr ) {
            abort();
        }
    }

    originalSetApplicationName(APP_NAME);
}