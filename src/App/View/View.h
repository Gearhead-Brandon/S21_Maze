/**
 * @file View.h
 * @brief Header file of View class
 */

#ifndef VIEW_H
#define VIEW_H

#include "MazeRenderer/MazeRenderer.h"
#include "CaveRenderer/CaveRenderer.h"
#include "../Model/Model.h"
#include <vector>

#include <QtWidgets>

namespace s21{

    /**
     * @brief View class for the application
     */
    class View : public QMainWindow {
        Q_OBJECT

        Model& model_;

        MazeRenderer* mazeRenderer_;
        CaveRenderer* caveRenderer_;

    public:

        /**
         * @brief View constructor
         */
        View(Model& model);

        /**
         * @brief View destructor
         */
        ~View();

    private:

        QHBoxLayout* createLayout();
        QVBoxLayout* createMenu();

        QVBoxLayout* createDrawingAreaTab();

        QWidget* createMazeTab();
        QPushButton* createMazeLoadButton();
        QLayout* createMazeGenerateLayout();

        QWidget* createFindPathTab();
        QLayout* createFindPathLayout();

        QWidget* createCaveTab();
        QPushButton* createGenCaveButton(QTextEdit* Rows, QTextEdit* Columns, QTextEdit* initChance);
        QPushButton* createCaveOneStepButton(QTextEdit* BirthLimit, QTextEdit* DeathLimit);
        QPushButton* createCaveAutoButton(QTextEdit* BirthLimit, QTextEdit* DeathLimit, QTextEdit* timeEdit);
        QLayout* createCaveLayout();

        void keyPressEvent(QKeyEvent* event);

        void showErrorMessage(const char *message);
    };
}
#endif