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
     * @details Inherits from QMainWindow
     */
    class View : public QMainWindow {
        Q_OBJECT

        //! Storage of model
        Model& model_;

        //! Pointers to maze renderer
        MazeRenderer* mazeRenderer_;

        //! Pointers to cave renderer
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

        /**
         * @brief Create main layout
         * @return pointer to layout
         */
        QHBoxLayout* createLayout();

        /**
         * @brief Create layout for menu
         * @return pointer to layout
         */
        QVBoxLayout* createMenu();

        /**
         * @brief Create layout for drawing area
         * @return pointer to layout
         */
        QVBoxLayout* createDrawingAreaTab();

        /**
         * @brief Create tab for maze
         * @return pointer to tab
         */
        QWidget* createMazeTab();

        /**
         * @brief Create button for load maze
         * @return pointer to button
         */
        QPushButton* createMazeLoadButton();

        /**
         * @brief Create layout for maze generation
         * @return pointer to layout
         */
        QLayout* createMazeGenerateLayout();

        /**
         * @brief Create tab for find path
         * @return pointer to tab
         */
        QWidget* createFindPathTab();

        /**
         * @brief Create layout for find path
         * @return pointer to layout
         */
        QLayout* createFindPathLayout();

        /**
         * @brief Create tab for cave
         * @return pointer to tab
         */
        QWidget* createCaveTab();

        /**
         * @brief Create button for cave generation
         * @param Rows - text edit for rows
         * @param Columns - text edit for columns
         * @param initChance - text edit for initial chance
         * @return pointer to button
         */
        QPushButton* createGenCaveButton(QTextEdit* Rows, QTextEdit* Columns, QTextEdit* initChance);
        
        /**
         * @brief Create button for one step cave transformation
         * @param BirthLimit - text edit for birth limit
         * @param DeathLimit - text edit for death limit
         * @return pointer to button
         */
        QPushButton* createCaveOneStepButton(QTextEdit* BirthLimit, QTextEdit* DeathLimit);

        /**
         * @brief Create button for auto cave transformation
         * @param BirthLimit - text edit for birth limit
         * @param DeathLimit - text edit for death limit
         * @param timeEdit - text edit for time
         * @return pointer to button
         */
        QPushButton* createCaveAutoButton(QTextEdit* BirthLimit, QTextEdit* DeathLimit, QTextEdit* timeEdit);
        
        /**
         * @brief Create layout for work with cave
         * @return pointer to layout
         */
        QLayout* createCaveLayout();

        /**
         * @brief Handle key press events
         * @param event - key press event
         */
        void keyPressEvent(QKeyEvent* event);

        /**
         * @brief Create message box with error message
         * @param message - error message
         * @sa QMessageBox
         */
        void showErrorMessage(const char *message);
    };
}
#endif