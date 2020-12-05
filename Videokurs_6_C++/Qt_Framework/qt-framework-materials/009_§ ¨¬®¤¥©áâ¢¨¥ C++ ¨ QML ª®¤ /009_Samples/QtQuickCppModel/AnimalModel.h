#include <QAbstractListModel>
#include <QStringList>

#include "Animal.h"

class AnimalModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AnimalRoles {
        TypeRole = Qt::UserRole + 1,
        SizeRole
    };

    AnimalModel(QObject *parent = nullptr);

    void addAnimal(const Animal &animal);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Animal> m_animals;
};


