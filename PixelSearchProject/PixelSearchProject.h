#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PixelSearchProject.h"

class PixelSearchProject : public QMainWindow
{
    Q_OBJECT

public:
    PixelSearchProject(QWidget *parent = nullptr);
    ~PixelSearchProject();

private:
    Ui::PixelSearchProjectClass ui;
};

