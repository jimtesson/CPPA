#ifndef IASHAPE_H
#define IASHAPE_H

#include <QVector>
#include <QDebug>
#include "iostream"

class iaShape
{
public:
    iaShape();

    void initializeMatrix(int nx, int ny);
    int getSizeRow();
    int getSizeCol();
    double getValueAt(int i, int j);
    void changeValueAt(int i, int j, double val);
    void getMyShapeMatrixCopy(QVector<QVector<double>> &myShapeMatrixCopy);

private:
    QVector<QVector<double>> myShapeMatrix;
    int nRow;
    int nCol;

};

#endif // IASHAPE_H
