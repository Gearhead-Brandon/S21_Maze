#include "App/View/View.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    srand(time(0));
    
    s21::Model model;

    s21::View view(model);
    
    view.show();

    return app.exec();
}