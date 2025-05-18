#undef scroll
#undef border

#include <QApplication>

#include "SnakeView.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  s21::SnakeModel model;

  s21::SnakeController controller(model);

  SnakeView view(controller);

  view.show();

  return app.exec();
}
