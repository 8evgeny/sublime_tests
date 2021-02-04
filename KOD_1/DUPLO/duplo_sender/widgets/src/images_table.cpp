#include "images_table.h"

ImagesTable::ImagesTable(QWidget* parent) : QTableView(parent) {}

void ImagesTable::ResetImages() {}

void ImagesTable::RecievedImages(const QString& name, const QString& file,
                                 const QString& mime,
                                 const QString& extra_type) {}
