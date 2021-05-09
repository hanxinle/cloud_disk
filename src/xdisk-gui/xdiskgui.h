#pragma once

#include <QtWidgets/QWidget>
#include "ui_xdiskgui.h"

class xdiskgui : public QWidget {
    Q_OBJECT

public:
    xdiskgui (QWidget *parent = Q_NULLPTR);
    void UpdateServerInfo ();
public slots:

    void UpdateDir (std::string dirs);
    void Refresh ();
    void Upload ();
    void Download ();
    void DownloadComplete ();

private:
    Ui::xdiskguiClass ui;
};
