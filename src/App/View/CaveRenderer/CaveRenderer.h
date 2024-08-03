/**
 * @file CaveArea.h
 * @brief Header file describing the class CaveArea
 */

#ifndef CAVEAREA_H
#define CAVEAREA_H

#include <QDebug>
#include <QMessageBox>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QWidget>

#include "../../Model/Model.h"

namespace s21 {

/**
 * @brief Class describing the cave area widget
 * @details View implements the interface IObserver
 */
class CaveRenderer : public QWidget, public IObserver {
  Q_OBJECT

  //! Storage of model
  const Model& model_;

  //! Image of cave
  QImage* cave_;

 public:
  /**
   * @brief Parametrized constructor
   * @param model - storage of model
   */
  CaveRenderer(Model& model);

  /**
   * @brief Destructor
   */
  ~CaveRenderer();

 private:
  /**
   * @brief Repaint the widget
   */
  void update() override;

  /**
   * @brief Paint the widget
   * @param event - event
   */
  void paintEvent(QPaintEvent* event) override;

  /**
   * @brief Update the image of the cave
   */
  void updateCave();

  /**
   * @brief Resize the widget
   * @param event - event
   */
  void resizeEvent(QResizeEvent* event);
};
}  // namespace s21

#endif