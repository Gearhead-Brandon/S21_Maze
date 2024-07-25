#include "CaveRenderer.h"

namespace s21{

    CaveRenderer::CaveRenderer(Model& model) 
        : QWidget(nullptr)
        , model_(model)
        , cave_(nullptr){
        setMinimumSize(500, 500);
    }

    CaveRenderer::~CaveRenderer(){
        delete cave_;
    }

    void CaveRenderer::paintEvent(QPaintEvent *event){
        QPainter painter(this);
        painter.drawImage(0, 0, *cave_);
    }

    void CaveRenderer::update(){
        updateCave();
        repaint();
    }

    void CaveRenderer::updateCave(){
        cave_->fill(QColor(255, 255, 255, 0));

        int w = width();
        int h = height();

        std::vector<Rect> cells = std::move(model_.getCave(w, h));

        QPainter painter(cave_);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(1));
        
        for(const Rect& cell : cells)
            painter.fillRect(QRectF{cell.x, cell.y, cell.width, cell.height}, Qt::black);
    }

    void CaveRenderer::resizeEvent(QResizeEvent *event){
        float w = width();
        float h = height();

        delete cave_;
        cave_ = new QImage(w, h, QImage::Format_ARGB32);
        updateCave();

        repaint();
    }
}