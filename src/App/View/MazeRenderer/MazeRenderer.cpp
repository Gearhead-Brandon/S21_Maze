/**
 * @file MazeRenderer.cpp
 * @brief Implementation of the class MazeRenderer
 */

#include "MazeRenderer.h"

namespace s21 {

/**
 * @brief Parametrized constructor
 * @param model - storage of model
 */
MazeRenderer::MazeRenderer(Model& model)
    : QWidget(nullptr), model_(model), maze_(nullptr), path_(nullptr) {
  setMinimumSize(500, 500);
}

/**
 * @brief Destructor
 */
MazeRenderer::~MazeRenderer() { delete maze_; }

/**
 * @brief Paint the widget
 * @param event - event
 */
void MazeRenderer::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  painter.drawImage(0, 0, *maze_);
  painter.drawImage(0, 0, *path_);
}

/**
 * @brief Repaint the widget
 */
void MazeRenderer::update() {
  updateMaze();
  updatePath();
  repaint();
}

/**
 * @brief Update the image of the maze
 */
void MazeRenderer::updateMaze() {
  maze_->fill(QColor(255, 255, 255, 0));

  int w = width();
  int h = height();

  std::vector<Line> lines = std::move(model_.getMaze(w, h));

  QPainter painter(maze_);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(QPen(Qt::black, 3));

  for (const Line& line : lines)
    painter.drawLine(QPointF{line.begin.col, line.begin.row},
                     QPointF{line.end.col, line.end.row});
}

/**
 * @brief Get the next color of the path
 * @param segmentIndex - index of the segment
 * @return - next color
 */
QColor MazeRenderer::getNextColor(int segmentIndex) {
  switch (segmentIndex) {
    case 0:
      return Qt::blue;
    case 1:
      return Qt::cyan;
    case 2:
      return Qt::green;
    case 3:
      return Qt::magenta;
    case 4:
      return Qt::darkMagenta;
    case 5:
      return Qt::red;
  }

  return Qt::darkMagenta;
}

/**
 * @brief Update the image of the path
 */
void MazeRenderer::updatePath() {
  path_->fill(QColor(255, 255, 255, 0));

  int w = width();
  int h = height();

  PathRenderConfig config = std::move(model_.getPath(w, h));

  QPainter painter(path_);
  painter.setRenderHint(QPainter::Antialiasing);

  QColor blue{35, 87, 232};
  painter.setPen(QPen(blue, 2));

  std::vector<Rect> points = std::move(config.points_);
  std::vector<Line> lines = std::move(config.path_);

  int i = 0;
  for (const Rect& point : points) {
    painter.fillRect(QRectF{point.x, point.y, point.width, point.height},
                     !i ? Qt::red : blue);
    i++;
  }

  i = 0;
  int size = lines.size();

  QColor currentColor = blue;

  int segmentIndex = 0;
  int segmentSize = size / 6;

  for (const Line& line : lines) {
    if (i < size - 2 && i++ == segmentSize) {
      segmentIndex++;
      currentColor = getNextColor(segmentIndex);  // Get color for new segment
      painter.setPen(QPen(currentColor, 2));
      i = 0;
    }

    if (i >= size - 2) painter.setPen(QPen(Qt::red, 2));

    painter.drawLine(QPointF{line.begin.col, line.begin.row},
                     QPointF{line.end.col, line.end.row});
  }
}

/**
 * @brief Resize the widget
 * @param event - event
 */
void MazeRenderer::resizeEvent(QResizeEvent*) {
  float w = width();
  float h = height();

  delete maze_;
  maze_ = new QImage(w, h, QImage::Format_ARGB32);

  delete path_;
  path_ = new QImage(w, h, QImage::Format_ARGB32);

  update();
}

/**
 * @brief Mouse press event
 * @param event - event
 */
void MazeRenderer::mousePressEvent(QMouseEvent* event) {
  try {
    if (event->button() == Qt::LeftButton) {
      model_.setStartPosition({static_cast<float>(event->pos().x()),
                               static_cast<float>(event->pos().y())},
                              width(), height());

      updatePath();
      repaint();
    } else if (event->button() == Qt::RightButton) {
      model_.setEndPosition({static_cast<float>(event->pos().x()),
                             static_cast<float>(event->pos().y())},
                            width(), height());

      updatePath();
      repaint();
    }
  } catch (const OpResult& e) {
    QMessageBox msgBox;
    msgBox.setStyleSheet("background-color: #171923; color: #FCFEF1;");
    msgBox.setInformativeText(tr(e.getErrorMessage().c_str()));
    msgBox.setFont(QFont("Arial", 24));
    msgBox.setFixedSize(500, 200);
    msgBox.setIcon(QMessageBox::Critical);

    QPushButton* btn = msgBox.addButton("Ok, sorry!", QMessageBox::ActionRole);
    btn->setStyleSheet(
        "QPushButton {"
        "text-transform: uppercase;"
        "letter-spacing: 2.5px;"
        "color: #FFFFFF;"
        "background-color: #AF2B36;"
        "border: none;"
        "padding: 5px 10px;"
        "}"

        "QPushButton:hover {"
        "background: #171923;"
        "color: #AF2B36;"
        "}"

        "QPushButton:pressed {"
        "background: #171923;"
        "color: #FCFEF1;"
        "}");

    msgBox.exec();
  }
}
}  // namespace s21