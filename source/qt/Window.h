#ifndef SHADERGRAPH_WINDOW_H
#define SHADERGRAPH_WINDOW_H

#include <QTimer>
#include <QMainWindow>

#include "../core/Core.h"

#define QSlot slot

namespace Ui { class Window; }

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget * parent = nullptr);
    ~Window() override;

private:
    Ui::Window * ui;

    QTimer * timer;
};

#endif // SHADERGRAPH_WINDOW_H