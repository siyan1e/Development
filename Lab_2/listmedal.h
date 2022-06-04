#ifndef RECORDMODAL_H
#define RECORDMODAL_H
#include <QVariant>
#include <QObject>
#include <QList>
#include <QModelIndex>
#include <QAbstractListModel>
#include <QUrl>


class list
{
public:
   list(  const QString &g_picture,
          const QString &g_url,
          const QString &g_login,
          const QString &g_password);

   QString getPicture() const;
   QString getUrl() const;
   QString getLogin() const;
   QString getPassword() const;

private:
   QString p_picture;
   QString p_url;
   QString p_login;
   QString p_password;
};


class listModal : public QAbstractListModel{
    //  класс QAbstractListModel обеспечивает
    // 1 по мимо хранения элементов модели в Qlist также
    // 2 Трансляцию строковых запросов QML в адреса (свойств и методов) С++
    // 3 Интерактивность и обновление QML-связанных view в qml посредстровам спец сигнальной системы
    Q_OBJECT
public:
    //должно быть столько индетефикаторов сколько свойсвта модели обьекта
    //нельзя начинать с 0 только с UserRole 256
    //
    enum enmRoles {
        Picture = Qt::UserRole + 1,
        URL,//258
        Login,//259
        Password//260
    };
    listModal(QObject *parent = nullptr);

    void addItem(const list & newItem);// добавление айтема

    int rowCount(const QModelIndex & parent = QModelIndex()) const; // необходим чтобы автоматом определляли кол во жлементов и строили разметку

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;//необходим для получения данных обьекта index соотв заданному с помощью role свойству элемента
    QVariantMap get(int idx) const;//для выгрузки i-элемента списка целиком со всеми свойствами

    void clear();// очистка всего списка


 protected:
    QHash<int, QByteArray> roleNames() const;

 private:
   QList<list> p_items;

};

#endif // LISTMEDAL_H
