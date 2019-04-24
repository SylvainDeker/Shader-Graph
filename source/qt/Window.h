#ifndef SHADERGRAPH_WINDOW_H
#define SHADERGRAPH_WINDOW_H

#include <QMap>
#include <QTimer>
#include <QMainWindow>
#include <QTreeWidgetItem>

#include <nodes/FlowScene>

#include <core/Core.h>

namespace Ui { class Window; }

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget * parent = nullptr);

    ~Window() override;

public slots:
    /// Compile the flow scene to GLSL code.
    void compile();

private:
    /// The user interface.
    Ui::Window * m_ui;

    /// The internal representation of the function tree/panel.
    QMap<QString, QTreeWidgetItem*> m_internalFunctionTree;
};

#endif // SHADERGRAPH_WINDOW_H