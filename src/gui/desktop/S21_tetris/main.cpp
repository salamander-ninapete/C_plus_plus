#include <QApplication>

#include "TetrisView.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  TetrisView view;
  view.show();
  return app.exec();
}
