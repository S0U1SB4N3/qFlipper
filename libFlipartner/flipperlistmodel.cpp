#include "flipperlistmodel.h"

FlipperListModel::FlipperListModel(QObject *parent):
    QAbstractListModel(parent)
{}

bool FlipperListModel::isEmpty() const
{
    return m_data.isEmpty();
}

int FlipperListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.size();
}

QVariant FlipperListModel::data(const QModelIndex &index, int role) const
{
    const auto &item = m_data.at(index.row());

    switch (role) {
        case ModelRole: return item.model;
        case NameRole: return item.name;
        case VersionRole: return item.version;
        case SerialRole: return item.params.serialNumber;
        default: return QVariant();
    }
}

QHash<int, QByteArray> FlipperListModel::roleNames() const
{
    static QHash<int, QByteArray> roles {
        {ModelRole, "model"},
        {NameRole, "name"},
        {VersionRole, "version"},
        {SerialRole, "serial"}
    };

    return roles;
}

void FlipperListModel::insertDevice(const FlipperInfo &info)
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(info);
    endInsertRows();

    emit contentChanged(isEmpty());
}

void FlipperListModel::removeDevice(const FlipperInfo &info)
{
    const auto index = m_data.indexOf(info);

    if(index < 0) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    m_data.remove(index);
    endRemoveRows();

    emit contentChanged(isEmpty());
}

void FlipperListModel::requestDevice(const QString &serialNumber) const
{
    for(const auto &info : m_data) {
        if(info.params.serialNumber == serialNumber) {
            emit deviceFound(info);
            break;
        }
    }
}