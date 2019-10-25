#include "cuedatamodel.h"
#include <QDebug>

CueDataModel::CueDataModel(QObject *parent):
QAbstractTableModel(parent)
{
}
CueDataModel::~CueDataModel()
{
}

//void CueDataModel::setCueList(QList<CueData> list)
//{
//    beginResetModel();
//    CueList = list;
//    endResetModel();
//}

//void CueDataModel::setCurrencyMap(const QMap<QString, double> &map)
//{
//    beginResetModel();
//    currencyMap = map;
//    endResetModel();
//}

//返回行數目
int CueDataModel::rowCount(const QModelIndex &parent) const
{
    return currencyMap.count();
}
//返回列數目
int CueDataModel::columnCount(const QModelIndex &parent) const
{
    return 6;
}
//返回列名
//QVariant類將大部分類型(int,string)的數據封裝起來，調用時使用to函數取出,例如：int類型包裝成QVariant，用QVariant::toInt()取出
QVariant CueDataModel::headerData(int section, Qt::Orientation, int role) const
{
    if(role !=Qt::DisplayRole){
        return QVariant();
    }
    return currencyAt(section);
}
//QString CueDataModel::cueListAt(int offset) const
//{
//   // return (CueList.begin()+offset).key();
//}

//(可編輯模型)
QVariant CueDataModel::data(const QModelIndex &index,int role) const
{
    if (!index.isValid())
          return QVariant();

      //读取的数据应该在有效范围内，而listOfPairs代表所储存的数据
      if (index.row() >= CueList.size() || index.row() < 0)
          return QVariant();

      if (role == Qt::DisplayRole) {

          if (index.column() == 0)
                {qDebug()<< "c0";}
          else if (index.column() == 1)
              return CueList[index.row()]->get_cueName();
          else if (index.column() == 2)
              return CueList[index.row()]->get_cueDelay();
          else if (index.column() == 3)
              return CueList[index.row()]->get_cueDmxChannel();
          else if (index.column() == 4)
              return CueList[index.row()]->get_cueContinue();
      }
      return QVariant();

//      if (!index.isValid()) return QVariant();

//      if (role == Qt::TextAlignmentRole) {
//          return int(Qt::AlignRight | Qt::AlignVCenter);
//      } else if (role == Qt::DisplayRole) {
//          QString rowCurrency = currencyAt(index.row());
//          QString columnCurrency = currencyAt(index.column());

//          if (index.column() == 1) return (currencyMap.begin() + index.row()).value(); //第二列表用来显示QComboBox选择的内容
//          if (currencyMap.value(rowCurrency) == 0.0) return "####";

//          double amount = currencyMap.value(columnCurrency) / currencyMap.value(rowCurrency);

//          return QString("%1").arg(amount, 0, 'f', 4);
//      }

//      return QVariant();
}


//可編輯模型函數實現
Qt::ItemFlags CueDataModel::flags(const QModelIndex &index) const
{
   return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

//更新數據
bool CueDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
            int row = index.row();
            if (index.column() == 0)
                CueList.at(row)->set_cueUsed(value.toBool());
            else if (index.column() == 1)
                CueList.at(row)->set_cueName(value.toString());
            else if (index.column() == 2)
                CueList.at(row)->set_cueDelay(value.toInt());
            else if (index.column() == 3)
                CueList.at(row)->set_cueDmxChannel(value.toInt());
            else if (index.column() == 4)
                CueList.at(row)->set_cueContinue(value.toInt());
            //引发信号：数据已经被修改
            emit(dataChanged(index, index));
            return true;
        }
        return false;

//        if (role == Qt::EditRole) {
//            int row = index.row();
//            int  col = index.column();

//            currencyMap[(currencyMap.begin() + row).key()] = value.toDouble();
//            return true;
//        }

//        return false;
}

bool CueDataModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);
    for(int row=0;row<rows;row++){
    CueData* cue = new CueData();
    cue->set_cueUsed(true);
    cue->set_cueName("Q");
    cue->set_cueDelay(row+100);
    cue->set_cueDmxChannel(0);
    cue->set_cueContinue(0);
    CueList.append(cue);
    qDebug() << CueList.at(row)->get_cueDelay();
    }
    endInsertRows();
    return true;

}

bool CueDataModel::removeRows(int position, int rows, const QModelIndex &parent)
 {
     beginRemoveRows(QModelIndex(), position, position+rows-1);
     for (int row = 0; row < rows; ++row) {
         CueList.removeAt(position);
     }
     endRemoveRows();
     return true;
 }



QString CueDataModel::currencyAt(int offset) const
{
    return (currencyMap.begin() + offset).key();
}
