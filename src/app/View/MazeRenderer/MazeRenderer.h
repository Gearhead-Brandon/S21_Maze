#ifndef MAZEAREA_H
#define MAZEAREA_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QPaintEvent>
#include <QMessageBox>
#include <QPushButton>
#include "../../Model/Model.h"

namespace s21{

    class MazeRenderer : public QWidget, public IObserver{
        Q_OBJECT

        Model& model_;
        QImage* maze_;
        QImage* path_;
        // QImage* cave_;
        // bool isMazeOrCave_;

    public:
        MazeRenderer(Model& model);
        ~MazeRenderer();

        //void changeArea();

    private:
        void update() override;

        void paintEvent(QPaintEvent *event) override;

        void updateMaze();
        void updatePath();

        QColor getNextColor(int segmentIndex);

        void resizeEvent(QResizeEvent *event);
        void mousePressEvent(QMouseEvent* event);
    };
}

#endif