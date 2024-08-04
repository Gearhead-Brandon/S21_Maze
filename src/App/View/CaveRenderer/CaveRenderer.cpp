/**
 * @file CaveRenderer.cpp
 * @brief Implementation of the class CaveRenderer
 */

#include "CaveRenderer.h"

namespace s21 {

/**
 * @brief Parametrized constructor
 * @param model - storage of model
 */
CaveRenderer::CaveRenderer(Model& model)
    : QWidget(nullptr), model_(model), cave_(nullptr) {
  setMinimumSize(500, 500);
}

/**
 * @brief Destructor
 */
CaveRenderer::~CaveRenderer() { delete cave_; }

/**
 * @brief Paint the widget
 * @param event - event
 */
void CaveRenderer::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  painter.drawImage(0, 0, *cave_);
}

/**
 * @brief Repaint the widget
 */
void CaveRenderer::update() {
  updateCave();
  repaint();
}

/**
 * @brief Update the image of the cave
 */
void CaveRenderer::updateCave() {
  cave_->fill(QColor(255, 255, 255, 0));

  int w = width();
  int h = height();

  std::vector<Rect> cells = std::move(model_.getCave(w, h));

  QPainter painter(cave_);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(QPen(1));

  for (const Rect& cell : cells)
    painter.fillRect(QRectF{cell.x, cell.y, cell.width, cell.height},
                     Qt::black);
}

/**
 * @brief Resize the widget
 * @param event - event
 */
void CaveRenderer::resizeEvent(QResizeEvent*) {
  float w = width();
  float h = height();

  delete cave_;
  cave_ = new QImage(w, h, QImage::Format_ARGB32);
  updateCave();

  repaint();
}
}  // namespace s21