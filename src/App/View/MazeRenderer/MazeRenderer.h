/**
 * @file MazeArea.h
 * @brief Header file describing the class MazeArea
 */

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

    /**
     * @brief Class describing the maze area widget
     * @details View implements the interface IObserver
     */
    class MazeRenderer : public QWidget, public IObserver{
        Q_OBJECT

        //! Storage of model
        Model& model_;

        //! Image of the maze
        QImage* maze_;

        //! Image of the path
        QImage* path_;

    public:

        /**
         * @brief Parametrized constructor
         * @param model - storage of model
         */
        MazeRenderer(Model& model);

        /**
         * @brief Destructor
         */
        ~MazeRenderer();

    private:

        /**
         * @brief Repaint the widget
         */
        void update() override;

        /**
         * @brief Paint the widget
         * @param event - event
         */
        void paintEvent(QPaintEvent *event) override;

        /**
         * @brief Update the image of the maze
         */
        void updateMaze();

        /**
         * @brief Update the image of the path
         */
        void updatePath();

        /**
         * @brief Get the next color of the path
         * @param segmentIndex - index of the segment
         * @return - next color
         */
        QColor getNextColor(int segmentIndex);

        /**
         * @brief Resize the widget
         * @param event - event
         */
        void resizeEvent(QResizeEvent *event);

        /**
         * @brief Mouse press event
         * @param event - event
         */
        void mousePressEvent(QMouseEvent* event);
    };
}

#endif