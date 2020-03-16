#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "Store/MainStore.h"
#include "Middleware/FileManager.h"

#include "Dispatcher/ActionProvider.h"
#include "Dispatcher/Dispatcher.h"


void registerSingletons()
{
    qmlRegisterSingletonType< ActionProvider >( "Flux", 1, 0, "ActionProvider",
                                             []( QQmlEngine* engine, QJSEngine* scriptEngine ) -> QObject*
    {
        Q_UNUSED( engine )
        Q_UNUSED( scriptEngine )

        QQmlEngine::setObjectOwnership( &ActionProvider::instance(), QQmlEngine::CppOwnership );
        return &ActionProvider::instance();
    });

    qmlRegisterSingletonType( QUrl( "qrc:/Qml/Styles.qml" ), "Style", 1, 0, "Style" );
}

int main( int argc, char* argv[] )
{
    QCoreApplication::setAttribute( Qt::AA_EnableHighDpiScaling );

    QCoreApplication::setOrganizationName( QStringLiteral( "Dominik Wojtaszek" ) );
    QCoreApplication::setOrganizationDomain( QStringLiteral( "Dominik.Wojtaszek" ) );

    QGuiApplication application( argc, argv );

    QQuickStyle::setStyle( QStringLiteral( "Material") );

    registerSingletons();

    QSharedPointer< MainStore > store { new MainStore {} };
    QSharedPointer< FileManager > fileManager { new FileManager {} };

    Dispatcher::instance().registerStore( store );
    Dispatcher::instance().registerMiddleware( fileManager );

    QQmlApplicationEngine engine;

    QQmlContext* context = engine.rootContext();
    context->setContextProperty( "applicationModel", store.get() );

    engine.load( QStringLiteral( "qrc:/Qml/Main.qml" ) );

    return application.exec();
}
