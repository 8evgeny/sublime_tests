#include "AnimalModel.h"

AnimalModel::AnimalModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void AnimalModel::addAnimal(const Animal &animal)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_animals << animal;
    endInsertRows();
}

int AnimalModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_animals.count();
}

QVariant AnimalModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_animals.count())
        return QVariant();

    const Animal &animal = m_animals[index.row()];
    if (role == TypeRole)
        return animal.type();
    else if (role == SizeRole)
        return animal.size();
    return QVariant();
}

bool AnimalModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= m_animals.count())
        return false;
    Animal &animal = m_animals[index.row()];
    if (role == TypeRole)
    {
        animal.setType(value.toString());
        emit dataChanged(index, index, {role});
        return true;
    }
    else if (role == SizeRole)
    {
         animal.setSize(value.toString());
         emit dataChanged(index, index, {role});
         return true;
    }
    return false;
}

QHash<int, QByteArray> AnimalModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[SizeRole] = "size";
    return roles;
}

