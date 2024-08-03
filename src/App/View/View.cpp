/**
 * @file View.cpp
 * @brief Implementation of View class
 */

#include "View.h"

namespace s21 {

/**
 * @brief View constructor
 */
View::View(Model& model) 
    : QMainWindow()
    , model_(model)
    , mazeRenderer_(new MazeRenderer(model))
    , caveRenderer_(new CaveRenderer(model)){

    QWidget* centralWidget = new QWidget();
    setCentralWidget(centralWidget);
    centralWidget->setLayout(createLayout());

    setStyleSheet("font-family: Arial; font-weight: bold; ");

    model_.addObserver(mazeRenderer_, AreaType::Maze);
    model_.addObserver(caveRenderer_, AreaType::Cave);
}

/**
 * @brief View destructor
 */
View::~View(){
    delete mazeRenderer_;
}

/**
 * @brief Create main layout
 * @return pointer to layout
 */
QHBoxLayout* View::createLayout(){
    QHBoxLayout* layout = new QHBoxLayout();

    layout->addLayout(createDrawingAreaTab());
    layout->addLayout(createMenu());

    return layout;
}

/**
 * @brief Create layout for drawing area
 * @return pointer to layout
 */
QVBoxLayout* View::createDrawingAreaTab(){
    QTabWidget* tabs = new QTabWidget;
    tabs->addTab(caveRenderer_, "Cave");
    tabs->addTab(mazeRenderer_, "Maze");
    tabs->setStyleSheet("font-weight: bold; font-size: 20px;");
    tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    tabs->setTabPosition(QTabWidget::West);
    tabs->setWhatsThis("Drawing area tab");
    tabs->setCurrentIndex(1);

    QObject::connect(tabs, &QTabWidget::currentChanged, [this](int index) {
        if(index <= 1){
            QList<QTabWidget*> tabs = findChildren<QTabWidget *>();
            (*std::find_if(tabs.begin(), tabs.end(), [](QTabWidget* tab) {
                return tab->whatsThis() == "Menu tab";
            }))->setCurrentIndex(index);
        }
    });

    QVBoxLayout* vBox = new QVBoxLayout();
    vBox->addWidget(tabs);

    return vBox;
}

/**
 * @brief Create layout for menu
 * @return pointer to layout
 */
QVBoxLayout* View::createMenu(){
    QTabWidget* tabs = new QTabWidget;
    tabs->addTab(createCaveTab(), "Cave");
    tabs->addTab(createMazeTab(), "Maze");
    tabs->addTab(createFindPathTab(), "Path");
    tabs->setStyleSheet("font-weight: bold; font-size: 20px;");
    tabs->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    tabs->setWhatsThis("Menu tab");
    tabs->setCurrentIndex(1);
    tabs->setTabBarAutoHide(true);

    QObject::connect(tabs, &QTabWidget::currentChanged, [this](int index) {
        if(index <= 1){
            QList<QTabWidget*> tabs = findChildren<QTabWidget *>();
            (*std::find_if(tabs.begin(), tabs.end(), [](QTabWidget* tab) {
                return tab->whatsThis() == "Drawing area tab";
            }))->setCurrentIndex(index);
        }
    });

    QVBoxLayout* vBox = new QVBoxLayout();
    vBox->addWidget(tabs);

    return vBox;
}

/**
 * @brief Create tab for maze
 * @return pointer to tab
 */
QWidget* View::createMazeTab(){
    QVBoxLayout* box = new QVBoxLayout;
    box->setContentsMargins(20, 10, 20, 0);
    box->addLayout(createMazeGenerateLayout());
    box->addStretch();

    QWidget* mazeTab = new QWidget;
    mazeTab->setLayout(box);
    mazeTab->setStyleSheet("border: none;");

    return mazeTab;
}

/**
 * @brief Create layout for maze generation
 * @return pointer to layout
 */
QLayout* View::createMazeGenerateLayout(){
    QLabel* generateLabel = new QLabel("MAZE GENERATION SETTINGS"); 
    generateLabel->setStyleSheet("font-size: 18px;");
    generateLabel->setAlignment(Qt::AlignCenter);
    generateLabel->setFixedSize(320, 35);

    QPushButton* generateBtn = new QPushButton("GENERATE");
    generateBtn->setStyleSheet("QPushButton { background-color:  #1c1a1a; color: #fcfcfc; font-size: 35px;} \
                            QPushButton::hover { background-color: #2e2b2b; border: 2px solid #fafcfb; }");
    generateBtn->setMinimumSize(300, 45);

    // Создание заголовка
    QLabel* mazeRows = new QLabel("MAZE ROWS:");
    mazeRows->setStyleSheet("font-size: 16px;");

    // Создание QTextEdit
    QTextEdit* mazeRowsTextEdit = new QTextEdit("5");
    mazeRowsTextEdit->setFixedSize(120, 35);
    mazeRowsTextEdit->setAlignment(Qt::AlignCenter);
    mazeRowsTextEdit->setStyleSheet("border: 2px solid black; font-size: 17px;");

    // Создание заголовка
    QLabel* mazeCols = new QLabel("MAZE COLS:");
    mazeCols->setStyleSheet("font-size: 16px;");

    // Создание QTextEdit
    QTextEdit* mazeColsTextEdit = new QTextEdit("5");
    mazeColsTextEdit->setFixedSize(120, 35);
    mazeColsTextEdit->setAlignment(Qt::AlignCenter);
    mazeColsTextEdit->setStyleSheet("border: 2px solid black; font-size: 17px;");

    // Создание горизонтального компоновщика для QTextEdit и кнопок
    QHBoxLayout* textEditRowsLayout = new QHBoxLayout;
    textEditRowsLayout->setContentsMargins(12, 0, 12, 0);
    textEditRowsLayout->addWidget(mazeRows);
    textEditRowsLayout->addWidget(mazeRowsTextEdit);
    textEditRowsLayout->setSpacing(0);

    QHBoxLayout* textEditColsLayout = new QHBoxLayout;
    textEditColsLayout->setContentsMargins(12, 0, 12, 0);
    textEditColsLayout->addWidget(mazeCols);
    textEditColsLayout->addWidget(mazeColsTextEdit);
    textEditColsLayout->setSpacing(0);

    QObject::connect(generateBtn, &QPushButton::pressed, this, [this, mazeRowsTextEdit, mazeColsTextEdit](){
        int rows = mazeRowsTextEdit->toPlainText().toInt();
        int cols = mazeColsTextEdit->toPlainText().toInt();
        OpResult result = model_.generateMaze(rows, cols);

        if (!result.IsSuccess())
            showErrorMessage(result.getErrorMessage().c_str());
    });

    QVBoxLayout* vBox = new QVBoxLayout;
    vBox->addWidget(createMazeLoadButton());
    vBox->addWidget(generateLabel);
    vBox->addLayout(textEditRowsLayout);
    vBox->addLayout(textEditColsLayout);
    vBox->addWidget(generateBtn);

    return vBox;
}

/**
 * @brief Create button for load maze
 * @return pointer to button
 */
QPushButton* View::createMazeLoadButton(){
    QPushButton* loadBtn = new QPushButton("LOAD");
    loadBtn->setStyleSheet("QPushButton { background-color:  #1c1a1a; color: #fcfcfc; font-size: 35px;} \
                            QPushButton::hover { background-color: #2e2b2b; border: 2px solid #fafcfb; }");
    loadBtn->setMinimumSize(300, 35);

    QObject::connect(loadBtn, &QPushButton::pressed, this, [this](){
        std::string path = QFileDialog::getOpenFileName(this, tr("Open File")).toStdString();

        if (path.empty())
            return;

        OpResult result = model_.loadMaze(path);

        if (!result.IsSuccess())
            showErrorMessage(result.getErrorMessage().c_str());
    });

    return loadBtn;
}

/**
 * @brief Create tab for cave
 * @return pointer to tab
 */
QWidget* View::createCaveTab(){
    QVBoxLayout* box = new QVBoxLayout;
    box->setContentsMargins(20, 10, 20, 0);
    box->addLayout(createCaveLayout());
    box->addStretch();

    QWidget* mazeTab = new QWidget;
    mazeTab->setLayout(box);
    mazeTab->setStyleSheet("border: none;");

    return mazeTab;
}

/**
 * @brief Create button for cave generation
 * @param Rows - text edit for rows
 * @param Columns - text edit for columns
 * @param initChance - text edit for initial chance
 * @return pointer to button
 */
QPushButton* View::createGenCaveButton(QTextEdit* Rows, QTextEdit* Columns,
                                             QTextEdit* initChance){
    QPushButton* genCaveBtn = new QPushButton("GENERATE");
    genCaveBtn->setStyleSheet("QPushButton { background-color: #1c1a1a; color: #fcfcfc; font-size: 35px;} \
                            QPushButton::hover { background-color: #2e2b2b; border: 2px solid #fafcfb; }");
    genCaveBtn->setMinimumSize(320, 35);

    QObject::connect(genCaveBtn, &QPushButton::pressed, this, [this, Rows, Columns, initChance](){
        int rows = Rows->toPlainText().toInt();
        int cols = Columns->toPlainText().toInt();
        int chance = initChance->toPlainText().toInt();
        
        OpResult res = model_.generateCave(rows, cols, chance);

        if(!res.IsSuccess())
            showErrorMessage(res.getErrorMessage().c_str());
    });

    return genCaveBtn;
}

/**
 * @brief Create layout for work with cave
 * @return pointer to layout
 */
QLayout* View::createCaveLayout(){
    QLabel* generateLabel = new QLabel("CAVE GENERATION SETTINGS"); 
    generateLabel->setStyleSheet("font-size: 18px;");
    generateLabel->setAlignment(Qt::AlignCenter);
    generateLabel->setMinimumSize(320, 35);

    QTextEdit* caveRowsTextEdit = new QTextEdit();
    caveRowsTextEdit->setFixedSize(120, 35);
    caveRowsTextEdit->setAlignment(Qt::AlignCenter);
    caveRowsTextEdit->setStyleSheet("border: 2px solid black; font-size: 17px;");
    caveRowsTextEdit->setPlaceholderText("Rows");

    QTextEdit* caveColsTextEdit = new QTextEdit();
    caveColsTextEdit->setFixedSize(120, 35);
    caveColsTextEdit->setAlignment(Qt::AlignCenter);
    caveColsTextEdit->setStyleSheet("border: 2px solid black; font-size: 17px;");
    caveColsTextEdit->setPlaceholderText("Columns");

    QLabel* initChance = new QLabel("     CHANCE:");
    initChance->setStyleSheet("font-size: 16px;");
    initChance->setToolTip("Chance of generating an cell");

    QTextEdit* initChanceTextEdit = new QTextEdit("50");
    initChanceTextEdit->setFixedSize(120, 35);
    initChanceTextEdit->setAlignment(Qt::AlignCenter);
    initChanceTextEdit->setStyleSheet("border: 2px solid black; font-size: 17px;");

    QHBoxLayout* textEditSizeLayout = new QHBoxLayout;
    textEditSizeLayout->setContentsMargins(12, 0, 12, 0);
    textEditSizeLayout->addWidget(caveRowsTextEdit);
    textEditSizeLayout->addWidget(caveColsTextEdit);
    textEditSizeLayout->setSpacing(0);

    QHBoxLayout* textEditInitLayout = new QHBoxLayout;
    textEditInitLayout->setContentsMargins(32, 0, 32, 0);
    textEditInitLayout->addWidget(initChance);
    textEditInitLayout->addWidget(initChanceTextEdit);
    textEditInitLayout->setSpacing(0);

    QPushButton* genCaveBtn = createGenCaveButton(caveRowsTextEdit, caveColsTextEdit, initChanceTextEdit);

    QPushButton* loadCaveBtn = new QPushButton("LOAD");
    loadCaveBtn->setStyleSheet("QPushButton { background-color: #1c1a1a; color: #fcfcfc; font-size: 35px;} \
                            QPushButton::hover { background-color: #2e2b2b; border: 2px solid #fafcfb; }");
    loadCaveBtn->setMinimumSize(320, 35);

    QObject::connect(loadCaveBtn, &QPushButton::pressed, this, [this](){
        std::string path = QFileDialog::getOpenFileName(this, tr("Open File")).toStdString();

        if (path.empty())
            return;

        OpResult res = model_.loadCave(path);

        if(!res.IsSuccess())
            showErrorMessage(res.getErrorMessage().c_str());
    });

    QLabel* transformationLabel = new QLabel("CAVE TRANSFORMATION SETTINGS"); 
    transformationLabel->setStyleSheet("font-size: 18px;");
    transformationLabel->setAlignment(Qt::AlignCenter);
    transformationLabel->setMinimumSize(320, 35);
//#########################################################################3
    QTextEdit* birthLimitTextEdit = new QTextEdit();
    birthLimitTextEdit->setFixedSize(120, 35);
    birthLimitTextEdit->setAlignment(Qt::AlignCenter);
    birthLimitTextEdit->setStyleSheet("border: 2px solid black; font-size: 17px;");
    birthLimitTextEdit->setPlaceholderText("Birth Limit");

    QTextEdit* deathLimitTextEdit = new QTextEdit();
    deathLimitTextEdit->setFixedSize(120, 35);
    deathLimitTextEdit->setAlignment(Qt::AlignCenter);
    deathLimitTextEdit->setStyleSheet("border: 2px solid black; font-size: 17px;");
    deathLimitTextEdit->setPlaceholderText("Death Limit");

    QHBoxLayout* textEditBirthDeathLimitLayout = new QHBoxLayout;
    textEditBirthDeathLimitLayout->setContentsMargins(12, 0, 12, 0);
    textEditBirthDeathLimitLayout->addWidget(birthLimitTextEdit);
    textEditBirthDeathLimitLayout->addWidget(deathLimitTextEdit);
    textEditBirthDeathLimitLayout->setSpacing(0);

    QPushButton* transOneStepCaveBtn = createCaveOneStepButton(birthLimitTextEdit, deathLimitTextEdit);

    QLabel* timeLabel = new QLabel("        TIME:");
    timeLabel->setStyleSheet("font-size: 16px;");

    QTextEdit* timeTextEdit = new QTextEdit();
    timeTextEdit->setFixedSize(120, 35);
    timeTextEdit->setAlignment(Qt::AlignCenter);
    timeTextEdit->setStyleSheet("border: 2px solid black; font-size: 17px;");
    timeTextEdit->setPlaceholderText("Milliseconds");

    QHBoxLayout* textEditTimeLayout = new QHBoxLayout;
    textEditTimeLayout->setContentsMargins(32, 0, 32, 0);
    textEditTimeLayout->addWidget(timeLabel);
    textEditTimeLayout->addWidget(timeTextEdit);
    textEditTimeLayout->setSpacing(0);

    QPushButton* transCaveAutoBtn = createCaveAutoButton(birthLimitTextEdit, deathLimitTextEdit, timeTextEdit);
//##########################################################################3
    QVBoxLayout* vBox = new QVBoxLayout;
    vBox->addWidget(loadCaveBtn);
    vBox->addWidget(genCaveBtn);
    vBox->addWidget(generateLabel);
    vBox->addLayout(textEditSizeLayout);
    vBox->addLayout(textEditInitLayout);
    vBox->setSpacing(10);
    vBox->addWidget(transformationLabel);
    vBox->addLayout(textEditBirthDeathLimitLayout);
    vBox->addLayout(textEditTimeLayout);
    vBox->addWidget(transOneStepCaveBtn);
    vBox->addWidget(transCaveAutoBtn);
    vBox->addStretch();

    return vBox;
}

/**
 * @brief Create button for one step cave transformation
 * @param BirthLimit - text edit for birth limit
 * @param DeathLimit - text edit for death limit
 * @return pointer to button
 */
QPushButton* View::createCaveOneStepButton(QTextEdit* BirthLimit, QTextEdit* DeathLimit){
    QPushButton* oneStepCaveBtn = new QPushButton("ONE STEP");
    oneStepCaveBtn->setStyleSheet("QPushButton { background-color: #1c1a1a; color: #fcfcfc; font-size: 35px;} \
                            QPushButton::hover { background-color: #2e2b2b; border: 2px solid #fafcfb; }");
    oneStepCaveBtn->setMinimumSize(320, 35);

    QObject::connect(oneStepCaveBtn, &QPushButton::pressed, this, [this, BirthLimit, DeathLimit](){
        int birthLimit = BirthLimit->toPlainText().toInt();
        int deathLimit = DeathLimit->toPlainText().toInt();

        OpResult res = model_.transformCave(false, birthLimit, deathLimit, 0);

        if(!res.IsSuccess())
            showErrorMessage(res.getErrorMessage().c_str());
    });

    return oneStepCaveBtn;
}

/**
 * @brief Create button for auto cave transformation
 * @param BirthLimit - text edit for birth limit
 * @param DeathLimit - text edit for death limit
 * @param timeEdit - text edit for time
 * @return pointer to button
 */
QPushButton* View::createCaveAutoButton(QTextEdit* BirthLimit, QTextEdit* DeathLimit, QTextEdit* timeEdit){
    QPushButton* oneStepCaveBtn = new QPushButton("AUTO");
    oneStepCaveBtn->setStyleSheet("QPushButton { background-color: #1c1a1a; color: #fcfcfc; font-size: 35px;} \
                            QPushButton::hover { background-color: #2e2b2b; border: 2px solid #fafcfb; }");
    oneStepCaveBtn->setMinimumSize(320, 35);

    QObject::connect(oneStepCaveBtn, &QPushButton::pressed, this, [this, BirthLimit, DeathLimit, timeEdit](){
        int birthLimit = BirthLimit->toPlainText().toInt();
        int deathLimit = DeathLimit->toPlainText().toInt();
        int time = timeEdit->toPlainText().toInt();

        OpResult res = model_.transformCave(true, birthLimit, deathLimit, time);

        if(!res.IsSuccess())
            showErrorMessage(res.getErrorMessage().c_str());
    });

    return oneStepCaveBtn;
}

/**
 * @brief Create tab for find path
 * @return pointer to tab
 */
QWidget* View::createFindPathTab(){
    QVBoxLayout* box = new QVBoxLayout;
    box->setContentsMargins(20, 10, 20, 0);
    box->addLayout(createFindPathLayout());
    box->addStretch();

    QWidget* findPathTab = new QWidget;
    findPathTab->setLayout(box);
    findPathTab->setStyleSheet("border: none;");

    return findPathTab;
}

/**
 * @brief Create layout for find path
 * @return pointer to layout
 */
QLayout* View::createFindPathLayout(){
    QPushButton* clearBtn = new QPushButton("CLEAR");
    clearBtn->setStyleSheet("QPushButton { background-color: #1c1a1a; color: #fcfcfc; font-size: 35px;} \
                            QPushButton::hover { background-color: #2e2b2b; border: 2px solid #fafcfb; }");
    clearBtn->setMinimumSize(300, 35);

    QObject::connect(clearBtn, &QPushButton::pressed, this, [this](){
        model_.clearPath();
    });

    QLabel* findPathLabel = new QLabel("PATH FINDING SETTINGS"); 
    findPathLabel->setStyleSheet("font-size: 18px;");
    findPathLabel->setAlignment(Qt::AlignCenter);
    findPathLabel->setFixedSize(320, 25);

    QLabel* startPointLabel = new QLabel("START POINT"); 
    startPointLabel->setStyleSheet("font-size: 18px;");
    startPointLabel->setAlignment(Qt::AlignCenter);
    startPointLabel->setFixedSize(320, 25);

    QTextEdit* startRowEdit = new QTextEdit("0");
    startRowEdit->setFixedSize(120, 35);
    startRowEdit->setAlignment(Qt::AlignCenter);
    startRowEdit->setStyleSheet("border: 2px solid black; font-size: 17px;");

    QTextEdit* startColEdit = new QTextEdit("0");
    startColEdit->setFixedSize(120, 35);
    startColEdit->setAlignment(Qt::AlignCenter);
    startColEdit->setStyleSheet("border: 2px solid black; font-size: 17px;");

    // Создание горизонтального компоновщика для QTextEdit и кнопок
    QHBoxLayout* textEditStartLayout = new QHBoxLayout;
    textEditStartLayout->setContentsMargins(12, 0, 12, 0);
    textEditStartLayout->addWidget(startRowEdit);
    textEditStartLayout->addWidget(startColEdit);
    textEditStartLayout->setSpacing(0);

    QLabel* endPointLabel = new QLabel("END POINT"); 
    endPointLabel->setStyleSheet("font-size: 18px;");
    endPointLabel->setAlignment(Qt::AlignCenter);
    endPointLabel->setFixedSize(320, 25);

    QTextEdit* endRowEdit = new QTextEdit("0");
    endRowEdit->setFixedSize(120, 35);
    endRowEdit->setAlignment(Qt::AlignCenter);
    endRowEdit->setStyleSheet("border: 2px solid black; font-size: 17px;");

    QTextEdit* endColEdit = new QTextEdit("0");
    endColEdit->setFixedSize(120, 35);
    endColEdit->setAlignment(Qt::AlignCenter);
    endColEdit->setStyleSheet("border: 2px solid black; font-size: 17px;");

    // Создание горизонтального компоновщика для QTextEdit и кнопок
    QHBoxLayout* textEditEndLayout = new QHBoxLayout;
    textEditEndLayout->setContentsMargins(12, 0, 12, 0);
    textEditEndLayout->addWidget(endRowEdit);
    textEditEndLayout->addWidget(endColEdit);
    textEditEndLayout->setSpacing(0);
    textEditEndLayout->setContentsMargins(0, 0, 0, 10);

    QPushButton* findPathBtn = new QPushButton("FIND PATH");
    findPathBtn->setStyleSheet("QPushButton { background-color: #1c1a1a; color: #fcfcfc; font-size: 35px;} \
                            QPushButton::hover { background-color: #2e2b2b; border: 2px solid #fafcfb; }");
    findPathBtn->setMinimumSize(320, 35);

    QObject::connect(findPathBtn, &QPushButton::pressed, this, [ this, startRowEdit, startColEdit, endRowEdit, endColEdit](){
        int startRow = startRowEdit->toPlainText().toInt();
        int startCol = startColEdit->toPlainText().toInt();

        int endRow = endRowEdit->toPlainText().toInt();
        int endCol = endColEdit->toPlainText().toInt();

        OpResult res = model_.QPathFinding({startCol, startRow}, {endCol, endRow});

        if (!res.IsSuccess())
            showErrorMessage(res.getErrorMessage().c_str());
    });

    QLabel* infoLabel = new QLabel(
        "<font color='red'>Red</font> - start point<br> "
        "<font color='blue'>Blue</font> - end point<br>"
        "<span style='color: white; background-color: black;'>CLEAR</span> - clear the path<br>"
        "To find a path through <span style='color: white; background-color: #1077de;'>Machine Learning</span>,<br>"
        "you need to <font color='red'>enter the coordinates of<br>"
        "the points</font> and click the <span style='color: white; background-color: black;'>FIND PATH</span><br><br>"
        "To use <span style='color: white; background-color: #1077de;'>conventional pathfinding tools</span>,<br>"
        "simply <font color='red'>left-click</font> to select a <font color='red'>starting</font> point<br>"
        "and <font color='blue'>right-click</font> to select a <font color='blue'>destination</font>"
    );

    infoLabel->setTextFormat(Qt::RichText); 
    infoLabel->setStyleSheet("font-size: 15px;");
    infoLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout* vBox = new QVBoxLayout;
    vBox->setSpacing(10);
    vBox->addWidget(clearBtn);
    vBox->addWidget(findPathLabel);
    vBox->addWidget(startPointLabel);
    vBox->addLayout(textEditStartLayout);
    vBox->addWidget(endPointLabel);
    vBox->addLayout(textEditEndLayout);
    vBox->addWidget(findPathBtn);
    vBox->addWidget(infoLabel);
    vBox->addStretch();

    return vBox;
}

/**
 * @brief Handle key press events
 * @param event - key press event
 */
void View::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_Escape)
        QApplication::quit();
}

/**
 * @brief Create message box with error message
 * @param message - error message
 * @sa QMessageBox
 */
void View::showErrorMessage(const char *message) {
    QMessageBox msgBox;
    msgBox.setStyleSheet("background-color: #171923; color: #FCFEF1;");
    msgBox.setInformativeText(tr(message));
    msgBox.setFont(QFont("Arial", 24));
    msgBox.setFixedSize(500, 200);
    msgBox.setIcon(QMessageBox::Critical);

    QPushButton *btn = msgBox.addButton("Ok, sorry!", QMessageBox::ActionRole);

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
        "}"
    );

    msgBox.exec();
}
}