#include "iashape.h"

iaShape::iaShape()
{


}

void iaShape::initializeMatrix(int nx, int ny)
{
    nRow = nx;
    nCol = ny;

    for(int i = 0; i < nRow; i++)
    {
        myShapeMatrix.push_back(QVector<double>());
        for(int j = 0; j < nCol; j++)
        {
            myShapeMatrix[i].push_back(0.0);
        }
    }

}

int iaShape::getSizeRow(){
    return myShapeMatrix.size();
}

int iaShape::getSizeCol(){
    return myShapeMatrix[0].size();
}

double iaShape::getValueAt(int i, int j){
    return myShapeMatrix[i][j];
}

void iaShape::changeValueAt(int i, int j,double val){
    if((i<0)||(i>nRow)){
        qDebug() << "i= " << i << " nRow:" << nRow ;
    }
    if((j<0)||(j>nCol)){
        qDebug() << "j= " << j << " nCol:" << nCol ;
    }

    myShapeMatrix[i][j] = val;
}

void iaShape::getMyShapeMatrixCopy(QVector<QVector<double>> &MyShapeMatrixCopy){
    for(int i = 0; i < nRow; i++)
    {
        MyShapeMatrixCopy.push_back(QVector<double>());
        for(int j = 0; j < nCol; j++)
        {
            MyShapeMatrixCopy[i].push_back(myShapeMatrix[i][j]);
            if(MyShapeMatrixCopy[i][j] != myShapeMatrix[i][j]){
                qDebug() << i << " " << j << " " << MyShapeMatrixCopy[i][j] << " " << myShapeMatrix[i][j];
            }
        }
    }
}


