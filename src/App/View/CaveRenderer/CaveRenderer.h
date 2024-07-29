#ifndef CAVEAREA_H
#define CAVEAREA_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QPaintEvent>
#include <QMessageBox>
#include <QPushButton>
#include "../../Model/Model.h"

namespace s21{

    class CaveRenderer : public QWidget, public IObserver{
        Q_OBJECT

        Model& model_;
        QImage* cave_;

    public:
        CaveRenderer(Model& model);
        ~CaveRenderer();

    private:
        void update() override;

        void paintEvent(QPaintEvent *event) override;

        void updateCave();

        void resizeEvent(QResizeEvent *event);
    };
}

#endif