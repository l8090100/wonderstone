
#ifndef SYSTEMPAGE_H
#define SYSTEMPAGE_H

#include <QStackedWidget>
#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QtSerialPort/QSerialPort>
#include <QtWidgets>
#include <QItemDelegate>
#include <QSpinBox>
#include "database.h"
#include <modesettingdata.h>
#include <systemsettingdata.h>
#include <modesettingmodel.h>
#include <systemsettingmodel.h>



namespace Ui {
class SystemPage;
}
class Console;
class SettingsDialog;


class SystemPage : public QWidget, public DataBase
{
    Q_OBJECT

public:
    explicit SystemPage(QWidget *parent = 0);
    ~SystemPage();
public:
    static SystemSettingModel *system_table_model;
    QList<SystemSettingData*> *system_Data_List;
    QSqlTableModel *system_sql_Model;

    static ModeSettingModel *mode_table_model;
    QList<SystemSettingData*> *mode_Data_List;
    QSqlTableModel *mode_sql_Model;

    static SystemSettingModel *get_system_model(){return system_table_model;}
    static ModeSettingModel *get_mode_model(){return mode_table_model;}
public slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data,int motor);
    void readData();
    void handleError(QSerialPort::SerialPortError error);
    void on_System_OpenSerial_button_clicked();
    void on_System_CloseSerial_button_clicked();
    void on_System_SettingDialog_button_clicked();
    void on_System_ClearConsole_button_clicked();
signals:
    void sendData(const QString data,int motor);
private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();

public:
    Ui::SystemPage *ui;
    SettingsDialog *settings;
    static QSerialPort *serial;
    Console *console;
    QLabel *status;
    QSqlTableModel *modeSetting_Model;
    QSqlTableModel *systemSetting_Model;
    void showStatusMessage(const QString &message);

    static QByteArray *response_data_temp;
    static int write_all_motor;

};

class ReadOnlyDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ReadOnlyDelegate(QObject *parent = 0): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget*parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const
    {
        return NULL;
    }
};

//ID列，只能输入1－12个数字
//利用QLineEdit委托和正则表达式对输入进行限制
class UserIDDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    UserIDDelegate(QObject *parent = 0): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const
    {
        QLineEdit *editor = new QLineEdit(parent);
        QRegExp regExp("[0-9]{0,10}");
        editor->setValidator(new QRegExpValidator(regExp, parent));
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QString text = index.model()->data(index, Qt::EditRole).toString();
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        lineEdit->setText(text);
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const
    {
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        QString text = lineEdit->text();
        model->setData(index, text, Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
};

//年龄列，利用QSpinBox委托进行输入限制，只能输入1－100之间的数字
class AgeDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    AgeDelegate(QObject *parent = 0): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const
    {
        QSpinBox *editor = new QSpinBox(parent);
        editor->setMinimum(1);
        editor->setMaximum(100);
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        int value = index.model()->data(index, Qt::EditRole).toInt();
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->setValue(value);
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const
    {
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->interpretText();
        int value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
};

//性别列，利用QComboBox委托对输入进行限制
//这一列的单元格只能输入Male或Female
class SexDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    SexDelegate(QObject *parent = 0): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const
    {
        QComboBox *editor = new QComboBox(parent);
        editor->addItem("Female");
        editor->addItem("Male");
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QString text = index.model()->data(index, Qt::EditRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        int tindex = comboBox->findText(text);
        comboBox->setCurrentIndex(tindex);
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString text = comboBox->currentText();
        model->setData(index, text, Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
};

//头像列，只是在单元格中央放一张小图而已
class IconDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    IconDelegate(QObject *parent = 0): QItemDelegate(parent) { }
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
        const QModelIndex & index ) const
    {
        //show.bmp是在工程目录中的一张图片（其实就是QQ的图标啦，呵呵）
//        QPixmap pixmap = QPixmap("show.bmp").scaled(24, 24);
//        qApp->style()->drawItemPixmap(painter, option.rect,  Qt::AlignCenter, QPixmap(pixmap));
    }
};

//代理类，把所有单元格中的字符居中显示
class VIPModel : public QStandardItemModel
{
    Q_OBJECT
public:
    VIPModel(QObject *parent=NULL) : QStandardItemModel(parent) { }
    VIPModel(int row, int column, QObject *parent=NULL)
        : QStandardItemModel(row, column, parent) { }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        if( Qt::TextAlignmentRole == role )
            return Qt::AlignCenter;
        return QStandardItemModel::data(index, role);
    }

};


#endif // SYSTEMPAGE_H
